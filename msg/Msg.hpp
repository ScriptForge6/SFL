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
 * @file Msg.hpp
 * @brief 定义了一个信息类
 * @author Scriptforge
 * @date 2026/10/30
 */

#pragma once
#ifndef SFL_MSG_HPP
#define SFL_MSG_HPP
#include "MsgApi.hpp"

#include <exception>
#include <string>
#include <string_view>
#include <vector>

#include <Lang.hpp>

SFL_MSG_START
/**
 * @brief 信息类
 * @note 非线程安全
 */
class SFL_API_MSG Msg{
public:
    Msg() = default;
    /**
     * @brief 信息类的构造函数
     * @param[in] key  所对应的 i18n 类的键
     * @param[in] args 所包含的参数
     */
    Msg(
        std::string_view key,
        std::vector<std::string_view> args = {}
    );

    /**
     * @brief 获取所对应的 i18n 类的键
     */
    auto key() const noexcept -> const std::string&;
    /**
     * @brief 获取所包含的参数
     */
    auto args() const noexcept -> const std::vector<std::string>&;

    /**
     * @brief 所输出内容
     * @param[in] lang i18n 类
     */
    auto format(const SFL_I18N Lang& lang) const -> std::string;

    /**
     * @brief 链式添加参数
     * @param[in] value 参数内容
     */
    auto arg(std::string_view value) -> Msg&;
private:
    std::exception_ptr m_lazyLoadExceptPtr = nullptr;
    std::string m_key = "";
    std::vector<std::string> m_args;
};

SFL_MSG_END

#endif