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

SCRIPT_NAME = "SFL"
VERSION = "0.0.0"
LICENSE = "Apache License 2.0"
START_YEAR = 2026
AUTHOR = "Scriptforge"
PROJECTDIR = os.projectdir()
local TARGET_MAIN_FILE = "xmake.lua"

---

option("static")
    set_default(false)
    set_showmenu(true)
    set_description("Build as static library")
option_end()

LIBRARY_KIND = has_config("static") and "static" or "shared"
LIBRARY_DEFINE = has_config("static") and "SFL_STATIC" or "SFL_SHARED"

rule("basename")
    on_load(function (target)
        -- 规则加载时的配置
        target:add("basename", target:name() .. "_$(plat)_$(mode)_$(arch)")
    end)
rule_end()

---

BUILD_DIR = path.join(
    PROJECTDIR,
    "build/output",
    "$(plat)",
    "$(arch)",
    LIBRARY_KIND,
    "$(mode)"
)

---

THIRDPARTY_DIR = path.join(PROJECTDIR, "thirdParty")
WEBVIEW_DIR = path.join(THIRDPARTY_DIR, "webview")
WEBVIEW2_DIR = path.join(THIRDPARTY_DIR, "webview2")

---

API_NAME = "SFLApi.hpp"
API_FILE = path.join(PROJECTDIR, API_NAME)

WEBVIEW_LUA = path.join(PROJECTDIR, "webview.lua")

GUARD_NAME = "guard"
GUARD_DIR = path.join(PROJECTDIR, GUARD_NAME)
GUARD_LUA = path.join(GUARD_DIR, TARGET_MAIN_FILE)

MSG_NAME = "msg"
MSG_DIR = path.join(PROJECTDIR, MSG_NAME)
MSG_LUA = path.join(MSG_DIR, TARGET_MAIN_FILE)

I18N_NAME = "i18n"
I18N_DIR = path.join(PROJECTDIR, I18N_NAME)
I18N_LUA = path.join(I18N_DIR, TARGET_MAIN_FILE)

MAIN_NAME = "SFL"
MAIN_DIR = path.join(PROJECTDIR, "main")
MAIN_LUA = path.join(MAIN_DIR, TARGET_MAIN_FILE)
