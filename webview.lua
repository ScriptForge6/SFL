includes("./define.lua")

target("webview")
    set_kind("headeronly")

    local wv2_include = path.join(WEBVIEW2_DIR, "include")
    local wv2_header  = path.join(wv2_include, "WebView2.h")

    add_headerfiles(path.join(WEBVIEW_DIR, "core/include/(webview/**.h)"))
    add_includedirs(
        path.join(WEBVIEW_DIR, "core/include"),
        { public = true }
    )

    if is_plat("windows") then
        add_includedirs(wv2_include, { public = true })
    elseif is_plat("macosx") then
    add_frameworks("WebKit", { public = true })
    add_syslinks("dl", "objc", { public = true })
    end

    on_load(function (target)
        if is_plat("windows") then
            os.exec('powershell -NoProfile -ExecutionPolicy Bypass -File "%s"',
                path.join(os.projectdir(), "Download-Webview2.ps1"))

            assert(os.isfile(wv2_header), "WebView2 SDK setup failed: WebView2.h not found!")
        elseif is_plat("linux") then
            os.exec('bash "%s"', path.join(os.projectdir(), "Download-GTK.sh"))

            local cflags = os.iorunv("pkg-config", {"--cflags", "gtk+-3.0", "webkit2gtk-4.1"})
            local libs   = os.iorunv("pkg-config", {"--libs",   "gtk+-3.0", "webkit2gtk-4.1"})
            target:add("cxxflags", cflags:trim(), { public = true, force = true })
            target:add("ldflags",  libs:trim(),   { public = true, force = true })
            target:add("syslinks", "dl", { public = true })
        end
    end)
target_end()