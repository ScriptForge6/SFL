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
#include "I18nApi.hpp"

#include <exception>
#include <filesystem>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

#include <Json.hpp>

#include <nlohmann/json.hpp>

SFL_I18N_START
#if 0
//实验性设计 / 未定稿

/**
 * @brief i18n 类
 * @details 继承自 Json 类，提供了语言文件的加载和管理功能
 * @note 线程安全
 */
class SFL_API_LANG Lang : public SFL_JSONCONTAINER Json {
};
#else
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
     * @param[in] dir      文件夹位置
     */
    Lang(
        std::string_view langCode,
        const std::optional<path_t>& dir
            = std::nullopt/* = getExeDir() / LANG*/
    ) noexcept;
    
    /**
     * @brief 设置变量
     * @param[in] langCode 文件名称（使用 ISO-639-1 ）
     * @param[in] dir      文件夹位置
     */
    auto set(
        std::string_view langCode,
        const std::optional<path_t>& dir
            = std::nullopt/* = getExeDir() / LANG*/
    ) -> void;

    /**
     * @brief 加载
     */
    auto load(
        std::string_view langCode,
        const std::optional<path_t>& dir = std::nullopt
    ) -> void;

    /**
     * @brief 重加载
     */
    auto reload() -> void;


    /** 
     * @brief 检查文件是否存在
     */
    SFL_NODISCARD auto checkFileExists() const -> bool;

    /** 
     * @brief 获取文件夹
     */
    SFL_NODISCARD auto getDir() const -> const path_t&;

    /** 
     * @brief 获取字母代码
     */
    SFL_NODISCARD auto getLangCode() const -> const std::string&;

    /** 
     * @brief 获取 json
     */
    SFL_NODISCARD auto getJson() const -> const nlohmann::json&;

    /**
     * @brief 获取语言名称
     */
    SFL_NODISCARD auto getLangName() const -> std::string;

    
    /**
     * @brief 验证函数（验证是否有包含的异常）
     */
    SFL_NODISCARD auto hasDeferredException() const -> bool;

    /**
     * @brief 验证函数（在 Guard 类使用）
     * @note 回调函数,按项目约定使用大驼峰命名
     */
    auto GuardConstructor() -> void;

    /**
     * @brief 验证函数（在 Guard 类使用）
     * @note 回调函数,按项目约定使用大驼峰命名
     */
    auto GuardDestructor() -> void;

    /**
     * @brief 获取可用的语言列表
     * @param[in] dir 语言文件夹位置
     * @return 可用的语言列表
     */
    SFL_NODISCARD
    static auto getAvailableLanguages(
        const std::optional<path_t>& dir
        = std::nullopt/* = getExeDir() / LANG*/
    ) -> std::vector<std::string>;
private:
    /**
     * @brief 检查 path 是否存在（接受参数）
     */
    SFL_NODISCARD
    static auto checkPathExistsWithPath(const path_t& filePath) -> bool;

    /**
     * @brief 检查文件是否为常规文件（接受参数）
     */
    SFL_NODISCARD
    static auto checkFileIsRegular(const path_t& filePath) -> bool;

    /**
     * @brief 检查文件是否为常规路径（接受参数）
     */
    SFL_NODISCARD
    static auto checkPathIsRegular(const path_t& path) -> bool;


    std::exception_ptr m_lazyLoadExceptPtr = nullptr;
    std::string m_langCode;
    path_t m_dir;
    nlohmann::json m_json;
};
SFL_I18N_END
#endif

#endif