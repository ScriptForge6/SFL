// Copyright 2026 Scriptforge
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//     http://www.apache.org/licenses/LICENSE-2.0
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/**
 * @file Lang.cpp
 * @brief i18n 类的实现
 * @author Scriptforge
 * @date 2026/10/23
 */

#include "Lang.hpp"

#include "ExePath.hpp"

Lang::Lang(
    std::string_view langCode,
    const std::optional<path_t>& dir/* = std::nullopt*/
) noexcept
    : m_langCode(langCode) {
    try {
        m_dir = dir ? *dir : getExeDir() / LANG;
        reload();
    }
    catch (...) {
        m_lazyLoadExceptPtr = std::current_exception();
    }
}

void Lang::reload() {

}