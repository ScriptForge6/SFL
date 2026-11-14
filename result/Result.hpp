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
 * @file Result.hpp
 * @brief 定义了一个 Result 类(类似于 Rust 的 Result)
 * @author Scriptforge
 * @date 2026/11/14
 */

#pragma once
#ifndef SFL_RESULT_HPP
#define SFL_RESULT_HPP
#include "ResultApi.hpp"

#include <optional>
#include <utility>
#include <variant>

#include "Unexpected.hpp"

#include "detail/Concept.hpp"


SFL_RESULT_START

/**
 * @brief 类似 Rust 的 Result 类
 */
template <ResultValueType T, ResultErrorType E>
class Result {
public:
    Result(const T& value);
    Result(T&& value);
    Result(const Unexpected<E>& error);
    Result(Unexpected<E>&& error);
    Result(const Result<T, E>&) = default;
    Result(Result<T, E>&&) = default;

    auto operator=(const Result&) -> Result& = default;
    auto operator=(Result&&) -> Result& = default;
    SFL_NODISCARD
    explicit operator bool() const noexcept;
    /**
     * @warning 无安全检查，异常来自stl库
     */
    auto operator*() & noexcept -> T&;
    auto operator*() const& noexcept -> const T&;

    /**
     * @warning 无安全检查，异常来自stl库
     */
    auto operator->() noexcept -> T*;
    auto operator->() const noexcept -> const T*;

    SFL_NODISCARD
    auto has_value() const noexcept -> bool;

    auto value() & -> T&;
    auto value() const& -> const T&;
    auto value() && -> T&&;
    auto value() const&& -> const T&&;

    auto error() & -> E&;
    auto error() const& -> const E&;
    auto error() && -> E&&;
    auto error() const&& -> const E&&;

    template <typename U = std::remove_cv_t<T>>
        requires std::is_convertible_v<U&&, T>
    auto value_or(U&& default_value) const& -> T;
private:
    std::variant<T, Unexpected<E>> m_valueOrError;
};
SFL_RESULT_END

// 模板实现

template <ResultValueType T, ResultErrorType E>
SFL_NODISCARD
explicit SFL_RESULT Result<T, E>::operator bool() const noexcept {
    return has_value();
}


template <ResultValueType T, ResultErrorType E>
auto SFL_RESULT Result<T, E>::operator*() & noexcept -> T& {
    return std::get<T>(m_valueOrError);
}

template <ResultValueType T, ResultErrorType E>
auto SFL_RESULT Result<T, E>::operator*() const& noexcept -> const T& {
    return std::get<T>(m_valueOrError);
}


template <ResultValueType T, ResultErrorType E>
auto SFL_RESULT Result<T, E>::operator->() noexcept -> T* {
    return &std::get<T>(m_valueOrError);
}

template <ResultValueType T, ResultErrorType E>
auto SFL_RESULT Result<T, E>::operator->() const noexcept -> const T* {
    return &std::get<T>(m_valueOrError);
}

template <ResultValueType T, ResultErrorType E>
SFL_NODISCARD
auto SFL_RESULT Result<T, E>::has_value() const noexcept -> bool {
    return std::holds_alternative<T>(m_valueOrError);
}


// value() 方法的实现

template <ResultValueType T, ResultErrorType E>
auto SFL_RESULT Result<T, E>::value() & -> T& {
     if(has_value()) {
        return std::get<T>(m_valueOrError);
    } else {
        throw BadResultAccess<E>(
            std::get<Unexpected<E>>(
                m_valueOrError
            ).error(),
            BadResultAccessReason::AccessingValue
        );
    }
}

template <ResultValueType T, ResultErrorType E>
auto SFL_RESULT Result<T, E>::value() const& -> const T& {
    if(has_value()) {
        return std::get<T>(m_valueOrError);
    } else {
        throw BadResultAccess<E>(
            std::get<Unexpected<E>>(
                m_valueOrError
            ).error(),
            BadResultAccessReason::AccessingValue
        );
    }
}

template <ResultValueType T, ResultErrorType E>
auto SFL_RESULT Result<T, E>::value() && -> T&& {
    if(has_value()) {
        return std::get<T>(std::move(m_valueOrError));
    } else {
        throw BadResultAccess<E>(
            std::get<Unexpected<E>>(
                m_valueOrError
            ).error(),
            BadResultAccessReason::AccessingValue
        );
    }
}

template <ResultValueType T, ResultErrorType E>
auto SFL_RESULT Result<T, E>::value() const&& -> const T&& {
    if(has_value()) {
        return std::get<T>(std::move(m_valueOrError));
    } else {
        throw BadResultAccess<E>(
            std::get<Unexpected<E>>(
                m_valueOrError
            ).error(),
            BadResultAccessReason::AccessingValue
        );
    }
}


// error()实现

template <ResultValueType T, ResultErrorType E>
auto SFL_RESULT Result<T, E>::error() & -> E& {
    if(!has_value()) {
        return std::get<Unexpected<E>>(m_valueOrError).error();
    } else {
        throw BadResultAccess<E>(
            std::nullopt,
            BadResultAccessReason::AccessingError
        );
    }
}

template <ResultValueType T, ResultErrorType E>
auto SFL_RESULT Result<T, E>::error() const& -> const E& {
    if(!has_value()) {
        return std::get<Unexpected<E>>(m_valueOrError).error();
    } else {
        throw BadResultAccess<E>(
            std::nullopt,
            BadResultAccessReason::AccessingError
        );
    }
}

template <ResultValueType T, ResultErrorType E>
auto SFL_RESULT Result<T, E>::error() && -> E&& {
    if(!has_value()) {
        return std::get<Unexpected<E>>(m_valueOrError).error();
    } else {
        throw BadResultAccess<E>(
            std::nullopt,
            BadResultAccessReason::AccessingError
        );
    }
}

template <ResultValueType T, ResultErrorType E>
auto SFL_RESULT Result<T, E>::error() const&& -> const E&& {
    if(!has_value()) {
        return std::get<Unexpected<E>>(m_valueOrError).error();
    } else {
        throw BadResultAccess<E>(
            std::nullopt,
            BadResultAccessReason::AccessingError
        );
    }
}

template <ResultValueType T, ResultErrorType E>
template <typename U>
    requires std::is_convertible_v<U&&, T>
auto SFL_RESULT Result<T, E>::value_or<U>(U&& default_value) const& -> T {
    if(!has_value()) {
        return std::forward<U>(default_value);
    } else {
        return std::get<T>(m_valueOrError);
    }
}

#endif