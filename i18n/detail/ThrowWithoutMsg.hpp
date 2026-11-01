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
 * @file ThrowWithoutMsg.hpp
 * @brief 声明了 i18n 模块不得不使用的普通错误抛出
 * @author Scriptforge
 * @date 2026/11/1
 */

#pragma once
#ifndef THROWWITHOUTMSG_HPP
#define THROWWITHOUTMSG_HPP
#include "../I18nApi.hpp"

#include <source_location>
#include <string>
#include <system_error>

SFL_I18N_START
[[noreturn]] auto failSystem(
    const std::string& what,
    std::error_code ec,
    std::source_location loc = std::source_location::current()) -> void;

SFL_NODISCARD auto lastError() -> std::error_code;
SFL_NODISCARD auto tooLong() -> std::error_code;
SFL_I18N_END

#endif