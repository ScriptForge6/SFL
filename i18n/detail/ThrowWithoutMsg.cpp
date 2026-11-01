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
 * @file ThrowWithoutMsg.cpp
 * @brief 声明了 i18n 模块不得不使用的普通错误抛出的实现
 * @author Scriptforge
 * @date 2026/11/1
 */
#include "ThrowWithoutMsg.hpp"

#include <cerrno>

#if defined(SFL_WIN)
#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#endif

[[noreturn]] auto SFL_I18N failSystem(
    const std::string& what,
    std::error_code ec,
    std::source_location loc/* = std::source_location::current()*/) -> void {
    throw std::system_error(
        ec,
        "[" + std::string(loc.file_name()) + ": " + std::to_string(loc.line()) + "]" + what);
}

SFL_NODISCARD auto SFL_I18N lastError() -> std::error_code {
#if defined(SFL_WIN)
    return { static_cast<int>(GetLastError()), std::system_category() };
#else
    return { errno, std::generic_category() };
#endif
}

SFL_NODISCARD auto SFL_I18N tooLong() -> std::error_code {
    return std::make_error_code(std::errc::filename_too_long);
}
