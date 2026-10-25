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

[CmdletBinding()]
param(
    [string]$ThirdPartyDir = "thirdParty",
    [string]$Version = "1.0.4191.47",
    [string]$Url = "https://www.nuget.org/api/v2/package/Microsoft.Web.WebView2/",
    [switch]$Force
)

$ErrorActionPreference = 'Stop'
$ProgressPreference = 'SilentlyContinue'
[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12

$downloadUrl = $Url.TrimEnd('/') + "/$Version"

$destDir = Join-Path $ThirdPartyDir "webview2"
$marker  = Join-Path $destDir ".version"

if (-not $Force -and (Test-Path $marker) -and ((Get-Content $marker -Raw).Trim() -eq $Version)) {
    Write-Host "[webview2] $Version already present, skip (use -Force to reinstall)"
    return
}

$zip     = Join-Path $env:TEMP "Microsoft.Web.WebView2.$Version.zip"
$extract = Join-Path $env:TEMP "webview2-$Version"

try {
    Write-Host "[webview2] downloading $Version ..."
    Invoke-WebRequest -Uri $downloadUrl -OutFile $zip -UseBasicParsing

    if (Test-Path $extract) { Remove-Item $extract -Recurse -Force }
    Expand-Archive -Path $zip -DestinationPath $extract -Force

    $srcInclude = Join-Path $extract "build/native/include"
    if (-not (Test-Path (Join-Path $srcInclude "WebView2.h"))) {
        throw "[webview2] WebView2.h not found in package (expected build/native/include)"
    }

    if (Test-Path $destDir) { Remove-Item $destDir -Recurse -Force }
    New-Item -ItemType Directory -Force $destDir | Out-Null

    # 只保留头文件和许可证，不要任何架构相关的二进制
    Copy-Item $srcInclude (Join-Path $destDir "include") -Recurse -Force
    foreach ($f in "LICENSE.txt", "NOTICE.txt") {
        $p = Join-Path $extract $f
        if (Test-Path $p) { Copy-Item $p $destDir -Force }
    }

    Set-Content -Path $marker -Value $Version -NoNewline
    Write-Host "[webview2] done, headers in $(Join-Path $destDir 'include')"
}
finally {
    if (Test-Path $zip)     { Remove-Item $zip -Force }
    if (Test-Path $extract) { Remove-Item $extract -Recurse -Force }
}