New-Item -ItemType Directory -Force thirdParty/webview2 | Out-Null

$version = "1.0.4191.47"
$url = "https://www.nuget.org/api/v2/package/Microsoft.Web.WebView2/$version"
$package = "$env:TEMP\Microsoft.Web.WebView2.$version.nupkg"
$zip = "$env:TEMP\webview2.zip"

Invoke-WebRequest -Uri $url -OutFile $package
Copy-Item $package $zip -Force

Expand-Archive `
    -Path $zip `
    -DestinationPath "thirdParty/webview2" `
    -Force