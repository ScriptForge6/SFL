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

SFL_I18N Lang::Lang(
    std::string_view langCode,
    const std::optional<path_t>& dir/* = std::nullopt*/
) noexcept {
    try {
        m_langCode = langCode;
        m_dir = dir ? *dir : SFL_I18N getExeDir() / "lang";//TODO: LANG
        reload();
    }
    catch (...) {
        m_lazyLoadExceptPtr = std::current_exception();
    }
}

auto SFL_I18N Lang::reload() -> void {

}

auto SFL_I18N Lang::validate() -> bool {
    return static_cast<bool>(m_lazyLoadExceptPtr);
}

#if 0
SFL_I18N Lang::Guard::Guard(SFL_I18N Lang& owner) {
    owner.validateForGuard();
}
#endif

auto SFL_I18N Lang::GuardConstructor() -> void {
    if (validate()) {
        std::rethrow_exception(m_lazyLoadExceptPtr);
    }
}

auto SFL_I18N Lang::GuardDestructor() -> void {
    return;
}