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
 * @file Lang.hpp
 * @brief 定义了一个 i18n 类
 * @author Scriptforge
 * @date 2026/10/23
 */

#pragma once
#ifndef KIRA_COMPILER_LANG_HPP
#define KIRA_COMPILER_LANG_HPP
#include "LangApi.hpp"

#include <exception>
#include <filesystem>
#include <memory>
#include <optional>
#include <string>
#include <string_view>

#include <nlohmann/json.hpp>

/**
 * @brief i18n 类
 * @note 非线程安全
 */
class KIRA_API_LANG Lang {
private:
    using path_t = std::filesystem::path;
public:
    Lang() = delete;
    /**
     * @brief Lang 的构造函数
     * @param[in] langCode 文件名称（使用 ISO-639-1 ）
     * @param[in] path     文件夹位置
     */
    Lang(
        std::string_view langCode,
        const std::optional<path_t>& dir
            = std::nullopt/* = getExeDir() / LANG*/
    ) noexcept;

    /**
     * @brief 重加载
     */
    void reload();
private:
    std::exception_ptr m_lazyLoadExceptPtr = nullptr;
    std::string m_langCode;
    path_t m_dir;
    nlohmann::json m_json;
};

#endif