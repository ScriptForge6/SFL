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
统计项目代码行数（忽略空行和单行注释）。
在 git 仓库内遵循 .gitignore；不在仓库内则遍历磁盘并使用 -ExcludeDir。

.EXAMPLE
./Count-Code.ps1
.EXAMPLE
./Count-Code.ps1 -Extension .cpp,.hpp -Detail
.EXAMPLE
./Count-Code.ps1 -IncludeSubmodules
#>

[CmdletBinding()]
param(
    [string]$Path = ".",
    [string[]]$Extension = @(".ixx", ".cpp", ".h", ".hpp", ".lua", ".ps1", ".sh", ".json", ".yml"),
    [string[]]$ExcludeDir = @('.git', '.vs', 'bin', 'obj', 'build', '.xmake', 'node_modules', 'thirdParty'),  # 仅在非 git 仓库时生效
    [string[]]$ExcludePath = @(),      # git 模式下额外排除的路径片段，例如 -ExcludePath thirdParty/webview2
    [switch]$IncludeSubmodules,        # 统计子模块内的文件
    [switch]$Detail                    # 列出每个文件的行数
)

[Console]::OutputEncoding = [System.Text.Encoding]::UTF8

# ---------- 收集文件 ----------
$root = (Resolve-Path -LiteralPath $Path).Path

# 判断是否在 git 仓库内
$inGit = $false
if (Get-Command git -ErrorAction SilentlyContinue) {
    git -C $root rev-parse --is-inside-work-tree 2>$null | Out-Null
    $inGit = ($LASTEXITCODE -eq 0)
}

if ($inGit) {
    Write-Host "已检测到 git 仓库，将遵循 .gitignore。" -ForegroundColor DarkGray
    $lsArgs = @("--cached", "--others", "--exclude-standard")
    if ($IncludeSubmodules) { $lsArgs = @("--cached", "--recurse-submodules") }  # --others 与 --recurse-submodules 不能同用

    $files = git -C $root -c core.quotepath=off ls-files @lsArgs |
        Sort-Object -Unique |
        ForEach-Object { Join-Path $root $_ } |
        Where-Object { Test-Path -LiteralPath $_ -PathType Leaf } |   # 过滤已删除但仍在索引里的文件
        ForEach-Object { Get-Item -LiteralPath $_ }
}
else {
    $dirNames  = ($ExcludeDir | ForEach-Object { [regex]::Escape($_) }) -join '|'
    $excludeRx = "[\\/]($dirNames|vsxmake\d+)[\\/]"
    $files = Get-ChildItem -LiteralPath $root -Recurse -File -ErrorAction SilentlyContinue |
        Where-Object { $_.FullName -notmatch $excludeRx }
}

# 按扩展名过滤
$files = $files | Where-Object { $_.Extension -in $Extension }

# git 模式下的额外路径排除
foreach ($p in $ExcludePath) {
    $needle = $p -replace '/', [IO.Path]::DirectorySeparatorChar
    $files  = $files | Where-Object { $_.FullName -notlike "*$needle*" }
}

# ---------- 统计 ----------
$commentPrefix = @{ ".lua" = "--"; ".ps1" = "#"; ".sh" = "#" }
$defaultPrefix = "//"
$stats = @{}
$cwd   = $root + [IO.Path]::DirectorySeparatorChar

foreach ($f in $files) {
    $ext    = $f.Extension
    $prefix = if ($commentPrefix.ContainsKey($ext)) { $commentPrefix[$ext] } else { $defaultPrefix }

    $count = 0
    foreach ($line in (Get-Content -LiteralPath $f.FullName -Encoding UTF8 -ReadCount 0)) {
        $t = $line.Trim()
        if ($t -ne "" -and -not $t.StartsWith($prefix)) { $count++ }
    }

    if (-not $stats.ContainsKey($ext)) { $stats[$ext] = @{ Files = 0; Lines = 0 } }
    $stats[$ext].Files++
    $stats[$ext].Lines += $count

    if ($Detail) {
        Write-Host ("{0,6}  {1}" -f $count, $f.FullName.Replace($cwd, ""))
    }
}

# ---------- 汇总 ----------
if (-not $stats.Count) {
    Write-Host "没有找到符合条件的文件。" -ForegroundColor Yellow
    return
}

$rows = $stats.GetEnumerator() | Sort-Object { $_.Value.Lines } -Descending | ForEach-Object {
    [PSCustomObject]@{
        "类型"   = $_.Key
        "文件数" = $_.Value.Files
        "行数"   = $_.Value.Lines
    }
}

Write-Host ""
$rows | Format-Table -AutoSize

$totalFiles = ($rows | Measure-Object "文件数" -Sum).Sum
$totalLines = ($rows | Measure-Object "行数" -Sum).Sum
Write-Host "共 $totalFiles 个文件，$totalLines 行有效代码。" -ForegroundColor Green