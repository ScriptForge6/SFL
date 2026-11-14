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
 * @file BadResultAccess.hpp
 * @brief 定义了一个 BadResultAccess 类(用于 Result 的错误访问)
 * @author Scriptforge
 * @date 2026/11/14
 */

#pragma once
#ifndef SFL_BADRESULTACCESS_HPP
#define SFL_BADRESULTACCESS_HPP
#include "ResultApi.hpp"

#include <exception>
#include <optional>

#include "detail/Concept.hpp"

SFL_RESULT_START

/**
 * @brief BadResultAccess 类的原因枚举
 */
enum class BadResultAccessReason {
    AccessingValue,  /**< 访问值时发生错误 */
    AccessingError   /**< 访问错误时发生错误 */
};

/**
 * @brief 用于 Result 的错误访问
 * @details 当访问 Result 的 value() 方法时，如果没有值，则会抛出 BadResultAccess 异常，并携带错误信息
 */
template <ResultErrorType E>
class BadResultAccess : public std::exception {
public:
    explicit BadResultAccess(
        std::optional<E> error,
        BadResultAccessReason reason
    );

    auto error() const noexcept -> std::optional<E>;

    auto what() const noexcept -> const char* override;

private:
    BadResultAccessReason m_reason;
    std::optional<E> m_error;
};

SFL_RESULT_END

// 模板实现

template <ResultErrorType E>
SFL_RESULT BadResultAccess<E>::BadResultAccess(
    const E& error,
    BadResultAccessReason reason
)
    : m_error(error), m_reason(reason) {}


template <ResultErrorType E>
auto SFL_RESULT BadResultAccess<E>::error() const noexcept -> std::optional<E> {
    return m_error;
}

template <ResultErrorType E>
auto SFL_RESULT BadResultAccess<E>::what() const noexcept -> const char* {
    switch (m_reason) {
        case BadResultAccessReason::AccessingValue:
            return "BadResultAccess: Accessing value when there is no value.";
            break;
        case BadResultAccessReason::AccessingError:
            return "BadResultAccess: Accessing error when there is no error.";
            break;
        default:
            return "BadResultAccess: Unknown reason.";
    }
}
#endif