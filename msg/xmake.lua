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

includes("../define.lua")

target(MSG_NAME)
	set_kind(LIBRARY_KIND)

    add_deps(I18N_NAME)

    add_defines("SFL_I18N_IMPORT")
    add_defines("SFL_MSG_EXPORT")
    add_defines(LIBRARY_DEFINE)

    add_includedirs(MSG_DIR, {public = true})
    
    add_files(path.join(MSG_DIR, "*.cpp"))
    add_headerfiles(path.join(MSG_DIR, "*.hpp"))
target_end()