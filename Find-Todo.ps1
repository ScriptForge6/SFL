param(
    [string]$Path = ".",
    [string]$Pattern = "[T]ODO:",   # 用 [T] 写法，避免脚本源码里的默认值匹配到自己
    [int]$Context = 2,              # 匹配行上下各显示几行
    [string[]]$ExcludeDir = @('.git', '.vs', 'bin', 'obj', 'node_modules'),  # 仅在非 git 仓库时生效
    [string[]]$Extension = @(),     # 可选：只扫描这些扩展名，例如 -Extension .cpp,.h,.js
    [switch]$NoBat                  # 强制不使用 bat
)

# 避免 bat 输出的中文/符号在 Windows PowerShell 中乱码
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8

# ---------- 检测 bat ----------
$bat = $null
if (-not $NoBat) {
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
    # 回退：不在 git 仓库里，使用 -ExcludeDir 的手动排除
    $dirNames  = ($ExcludeDir | ForEach-Object { [regex]::Escape($_) }) -join '|'
    $excludeRx = "[\\/]($dirNames)[\\/]"
    $files = Get-ChildItem -LiteralPath $root -Recurse -File -ErrorAction SilentlyContinue |
        Where-Object { $_.FullName -notmatch $excludeRx }
}

# 可选：按扩展名过滤
if ($Extension.Count -gt 0) {
    $files = $files | Where-Object { $_.Extension -in $Extension }
}

# ---------- 搜索 ----------
Write-Host "正在搜索包含 '$Pattern' 的注释..." -ForegroundColor Cyan

$results = $files |
    Where-Object { $_.FullName -ne $self -and $_.Name -ne 'find-todo.ps1' } |
    Select-String -Pattern $Pattern

if (-not $results) {
    Write-Host "太棒了！没有找到任何待办项。" -ForegroundColor Green
    return
}

# ---------- 输出 ----------
if ($bat) {
    # 使用 bat 语法高亮
    foreach ($r in $results) {
        $start = [Math]::Max(1, $r.LineNumber - $Context)
        $end   = $r.LineNumber + $Context

        & $bat.Source `
            --paging=never `
            --color=always `
            --style=header,numbers,grid `
            --highlight-line $r.LineNumber `
            --line-range "${start}:${end}" `
            $r.Path
    }
}
else {
    # 回退：表格输出
    $cwd = $root + [IO.Path]::DirectorySeparatorChar
    $results | ForEach-Object {
        [PSCustomObject]@{
            "文件路径" = $_.Path.Replace($cwd, "")
            "行号"     = $_.LineNumber
            "待办内容" = $_.Line.Trim()
        }
    } | Format-Table -AutoSize
}

Write-Host "共找到 $($results.Count) 个待办项。" -ForegroundColor Green