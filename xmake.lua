--[[
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
]]--

includes("define.lua")
set_project(SCRIPT_NAME)
set_version(VERSION)

add_defines(string.format("SCRIPT_NAME=\"%s\"", SCRIPT_NAME))
add_defines(string.format("VERSION=\"%s\"", VERSION))
add_defines(string.format("LICENSE=\"%s\"", LICENSE))
add_defines(string.format("START_YEAR=%d", START_YEAR))
add_defines(string.format("AUTHOR=\"%s\"", AUTHOR))

add_rules("basename")

set_policy("package.install_locally", true)

set_defaultmode("debug")

add_defines(LIBRARY_DEFINE)

set_languages("c++20")
set_warnings("allextra")
set_symbols("debug", "hidden")

set_targetdir(TARGET_DIR)

add_cxxflags({
    "/permissive-",
    "/Zc:preprocessor",
    "/Zc:templateScope"
}, {tools = {"cl"}})

if is_plat("linux") then
    add_rpathdirs("$ORIGIN", {public = true})
end

add_includedirs(PROJECTDIR)
add_headerfiles(API_FILE)

includes(GUARD_LUA)
includes(I18N_LUA)
includes(MSG_LUA)
includes(WEBVIEW_LUA)
includes(MAIN_LUA)