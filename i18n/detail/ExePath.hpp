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
 * @file ExePath.hpp
 * @brief 获取可执行文件位置或地址
 * @brief 获取可执行文件位置或地址
 * @author Scriptforge
 * @date 2026/10/23
 */

#pragma once
#ifndef SFL_EXEPATH_HPP
#define SFL_EXEPATH_HPP
#include "I18nApi.hpp"

#include <filesystem>
#include <optional>

SFL_I18N_START
/**
 * @brief 获取可执行文件地址
 * @return 返回可执行文件地址
 * @retval std::nullopt 出现错误
*/
std::filesystem::path getExePath();

/**
 * @brief 获取可执行文件位置
 * @return 返回可执行文件位置
 * @retval std::nullopt 出现错误
*/
std::filesystem::path getExeDir();
SFL_I18N_END

#endif