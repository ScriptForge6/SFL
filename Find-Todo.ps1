<#
   Copyright 2026 Scriptforge

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

#>

<#
.SYNOPSIS
    在项目中查找待办标记（注释里的 TODO/FIXME 等，以及 SFL_TODO(...) 这类宏调用）。

.EXAMPLE
    ./Find-Todo.ps1
    默认：注释里的 TODO + SFL_TODO(...) 调用。

.EXAMPLE
    ./Find-Todo.ps1 -Keyword TODO,FIXME,HACK -Macro SFL_TODO,SFL_UNIMPLEMENTED
    多个注释关键字、多个宏。

.EXAMPLE
    ./Find-Todo.ps1 -Pattern 'NotImplemented','\bXXX\b'
    额外的自定义正则（匹配整行，不限注释）。

.EXAMPLE
    ./Find-Todo.ps1 -OutFile todo.md
    同时写入文件；格式由扩展名决定：.md / .csv / .json / 其他为纯文本。
#>

[CmdletBinding()]
param(
    [string]$Path = ".",

    # 注释关键字：匹配 //、--、/*、行首 *、# 之后的关键字
    [string[]]$Keyword = @('TODO'),

    # 宏名：匹配 NAME( 形式的调用（宏定义行自动排除）
    [string[]]$Macro = @('SFL_TODO'),

    # 额外的自定义正则（匹配整行）
    [string[]]$Pattern = @(),

    [int]$Context = 2,                       # 匹配行上下各显示几行
    [string[]]$ExcludeDir = @('.git', '.vs', 'bin', 'obj', 'node_modules'),  # 仅在非 git 仓库时生效
    [string[]]$Extension = @(),              # 可选：只扫描这些扩展名，例如 -Extension .cpp,.hpp,.lua
    [switch]$CaseSensitive,                  # 区分大小写
    [string]$OutFile,                        # 结果写入文件（.md/.csv/.json/其他=纯文本）
    [switch]$NoConsole,                      # 只写文件，不在控制台显示
    [switch]$NoBat                           # 强制不使用 bat
)

# 避免 bat 输出的中文/符号在 Windows PowerShell 中乱码
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8

# ---------- 组装正则 ----------
$regexes = @()
foreach ($k in $Keyword) {
    if ($k) { $regexes += "(//|--|/\*|^\s*\*|#)\s*$([regex]::Escape($k))\b" }
}
foreach ($m in $Macro) {
    if ($m) { $regexes += "\b$([regex]::Escape($m))\s*\(" }
}
foreach ($p in $Pattern) {
    if ($p) { $regexes += $p }
}
if ($regexes.Count -eq 0) {
    Write-Host "没有任何搜索条件（-Keyword / -Macro / -Pattern 均为空）。" -ForegroundColor Red
    return
}

# 宏定义行本身不算待办，例如 #define SFL_TODO(msg) ...
$defineRx = $null
$macroNames = @($Macro | Where-Object { $_ })
if ($macroNames.Count -gt 0) {
    $names = ($macroNames | ForEach-Object { [regex]::Escape($_) }) -join '|'
    $defineRx = "^\s*#\s*define\s+($names)\b"
}

# ---------- 检测 bat ----------
$bat = $null
if (-not $NoBat -and -not $NoConsole) {
    $bat = Get-Command bat -ErrorAction SilentlyContinue
    if (-not $bat) {
        Write-Host "未检测到 bat，将使用普通表格输出。" -ForegroundColor Yellow
        Write-Host "安装方式（任选其一）：" -ForegroundColor Yellow
        Write-Host "  winget install sharkdp.bat"
        Write-Host "  scoop install bat"
        Write-Host "  或下载：https://github.com/sharkdp/bat/releases/latest"
        Write-Host ""
    }
}

# ---------- 收集文件 ----------
$root = (Resolve-Path -LiteralPath $Path).Path
$self = if ($PSCommandPath) { (Resolve-Path -LiteralPath $PSCommandPath).Path } else { $null }

# 输出文件自己不参与扫描
$outFull = $null
if ($OutFile) {
    $outFull = $ExecutionContext.SessionState.Path.GetUnresolvedProviderPathFromPSPath($OutFile)
}

# 判断是否在 git 仓库内
$inGit = $false
if (Get-Command git -ErrorAction SilentlyContinue) {
    git -C $root rev-parse --is-inside-work-tree 2>$null | Out-Null
    $inGit = ($LASTEXITCODE -eq 0)
}

if ($inGit) {
    Write-Host "已检测到 git 仓库，将遵循 .gitignore。" -ForegroundColor DarkGray
    $files = git -C $root -c core.quotepath=off ls-files --cached --others --exclude-standard |
        Sort-Object -Unique |
        ForEach-Object { Join-Path $root $_ } |
        Where-Object { Test-Path -LiteralPath $_ -PathType Leaf } |   # 过滤已删除但仍在索引里的文件
        ForEach-Object { Get-Item -LiteralPath $_ }
}
else {
    $dirNames  = ($ExcludeDir | ForEach-Object { [regex]::Escape($_) }) -join '|'
    $excludeRx = "[\\/]($dirNames)[\\/]"
    $files = Get-ChildItem -LiteralPath $root -Recurse -File -ErrorAction SilentlyContinue |
        Where-Object { $_.FullName -notmatch $excludeRx }
}

if ($Extension.Count -gt 0) {
    $files = $files | Where-Object { $_.Extension -in $Extension }
}

# ---------- 搜索 ----------
$desc = @()
if ($Keyword)  { $desc += "注释关键字 [" + ($Keyword -join ', ') + "]" }
if ($Macro)    { $desc += "宏调用 [" + (($Macro | ForEach-Object { "$_()" }) -join ', ') + "]" }
if ($Pattern)  { $desc += "自定义正则 [" + ($Pattern -join ', ') + "]" }
Write-Host ("正在搜索：" + ($desc -join '；')) -ForegroundColor Cyan

$selectArgs = @{ Pattern = $regexes; Encoding = 'utf8' }
if ($CaseSensitive) { $selectArgs.CaseSensitive = $true }

$results = @(
    $files |
        Where-Object {
            $_.FullName -ne $self -and
            $_.Name -ne 'find-todo.ps1' -and
            (-not $outFull -or $_.FullName -ne $outFull)
        } |
        Select-String @selectArgs |
        Where-Object { -not $defineRx -or $_.Line -notmatch $defineRx }
)

if ($results.Count -eq 0) {
    Write-Host "太棒了！没有找到任何待办项。" -ForegroundColor Green
    return
}

$cwd = $root + [IO.Path]::DirectorySeparatorChar
$records = $results | ForEach-Object {
    [PSCustomObject]@{
        File = $_.Path.Replace($cwd, "")
        Line = $_.LineNumber
        Text = $_.Line.Trim()
    }
}

# ---------- 控制台输出 ----------
if (-not $NoConsole) {
    if ($bat) {
        foreach ($g in ($results | Group-Object Path)) {
            # 同一文件里相邻/重叠的匹配合并为一个区间，只输出一次
            $ranges = @()
            foreach ($r in ($g.Group | Sort-Object LineNumber)) {
                $s = [Math]::Max(1, $r.LineNumber - $Context)
                $e = $r.LineNumber + $Context
                if ($ranges.Count -gt 0 -and $s -le $ranges[-1].End + 1) {
                    $ranges[-1].End = [Math]::Max($ranges[-1].End, $e)
                    $ranges[-1].Lines += $r.LineNumber
                }
                else {
                    $ranges += [PSCustomObject]@{ Start = $s; End = $e; Lines = @($r.LineNumber) }
                }
            }

            foreach ($rg in $ranges) {
                $batArgs = @('--paging=never', '--color=always', '--style=header,numbers,grid',
                             '--line-range', "$($rg.Start):$($rg.End)")
                foreach ($ln in $rg.Lines) { $batArgs += @('--highlight-line', "$ln") }
                & $bat.Source @batArgs $g.Name
            }
        }
    }
    else {
        $records | ForEach-Object {
            [PSCustomObject]@{
                "文件路径" = $_.File
                "行号"     = $_.Line
                "待办内容" = $_.Text
            }
        } | Format-Table -AutoSize
    }
}

# ---------- 写入文件 ----------
if ($outFull) {
    $dir = Split-Path -Parent $outFull
    if ($dir -and -not (Test-Path -LiteralPath $dir)) {
        New-Item -ItemType Directory -Path $dir -Force | Out-Null
    }

    switch ([IO.Path]::GetExtension($outFull).ToLowerInvariant()) {
        '.csv' {
            $records | Export-Csv -LiteralPath $outFull -NoTypeInformation -Encoding UTF8
        }
        '.json' {
            ConvertTo-Json -InputObject @($records) -Depth 3 |
                Set-Content -LiteralPath $outFull -Encoding UTF8
        }
        '.md' {
            $lines = @("# 待办项（共 $($records.Count) 个）", "", "| 文件 | 行号 | 内容 |", "| --- | ---: | --- |")
            foreach ($r in $records) {
                $t = $r.Text.Replace('|', '\|')
                $lines += "| ``$($r.File)`` | $($r.Line) | ``$t`` |"
            }
            $lines | Set-Content -LiteralPath $outFull -Encoding UTF8
        }
        default {
            $records | ForEach-Object { "$($_.File):$($_.Line): $($_.Text)" } |
                Set-Content -LiteralPath $outFull -Encoding UTF8
        }
    }
    Write-Host "已写入：$outFull" -ForegroundColor DarkGray
}

Write-Host "共找到 $($records.Count) 个待办项。" -ForegroundColor Green