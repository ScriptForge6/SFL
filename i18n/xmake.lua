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

target(I18N_NAME)
	set_kind(LIBRARY_KIND)

    add_defines("SFL_LANG_EXPORT")

    add_includedirs(I18N_DIR, {public = true})
    
    add_files(path.join(I18N_DIR, "*.cpp"))
    add_headerfiles(path.join(I18N_DIR, "*.hpp"))
target_end()