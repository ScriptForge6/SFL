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
#ifndef SFL_LANG_HPP
#define SFL_LANG_HPP
#include "LangApi.hpp"

#include <exception>
#include <filesystem>
#include <optional>
#include <string>
#include <string_view>

#include <nlohmann/json.hpp>

SFL_I18N_START
/**
 * @brief i18n 类
 * @note 非线程安全
 */
class SFL_API_LANG Lang {
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
     * @brief 
     */

    /**
     * @brief 重加载
     */
    auto reload() -> void;
private:
    /**
     * @brief 自动检测RAII
    */
    class Guard {
    public:
        Guard() = delete;
        Guard(const Guard&) = delete;
        Guard(Guard&&) = delete;
        /**
         * @brief Guard 的构造函数
         * @param[in] owner 父类的引用
        */
        explicit Guard(SFL_I18N Lang& owner);

    };
    /**
     * @brief 验证函数
    */
    auto validate() -> void;

    std::exception_ptr m_lazyLoadExceptPtr = nullptr;
    std::string m_langCode;
    path_t m_dir;
    nlohmann::json m_json;
};
SFL_I18N_END

#endif