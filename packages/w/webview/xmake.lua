package("webview")
    set_kind("library", {headeronly = true})
    set_homepage("https://github.com/webview/webview")
    set_description("Tiny cross-platform webview library")
    set_license("MIT")

    add_urls("https://github.com/webview/webview.git")
    add_versions("0.12.0", "3ab4b5d722438fc8a13e6ca830c5e2372d19a01d")

    if is_plat("macosx") then
        add_frameworks("WebKit")
    elseif is_plat("windows") then
        add_syslinks("advapi32", "ole32", "shell32", "shlwapi", "user32", "version")
    elseif is_plat("linux") then
        add_extsources("apt::libwebkit2gtk-4.1-dev", "pacman::webkit2gtk-4.1")
    end

    on_install("windows", "macosx", "linux", function (package)
        os.cp("core/include/webview", package:installdir("include"))
        os.cp("LICENSE", package:installdir("share/licenses/webview"))
    end)
package_end()