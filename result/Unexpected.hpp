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
 * @file Unexpected.hpp
 * @brief 定义了一个 Unexpected 类(类似于 Rust 的 Unexpected)
 * @author Scriptforge
 * @date 2026/11/14
 */

#pragma once
#ifndef SFL_UNEXPECTED_HPP
#define SFL_UNEXPECTED_HPP
#include "ResultApi.hpp"

#include "detail/Concept.hpp"

SFL_RESULT_START

template<ResultErrorType E>
class Unexpected {
public:
    explicit Unexpected(const E& error);
    explicit Unexpected(E&& error);

    auto error() const& noexcept -> const E&;
    auto error() && noexcept -> E&&;

private:
    E m_error;
};

SFL_RESULT_END

#endif