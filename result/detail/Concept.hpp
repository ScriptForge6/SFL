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
 * @file Concept.hpp
 * @brief 定义了 Result 相关的概念
 * @author Scriptforge
 * @date 2026/11/14
 */

#pragma once
#ifndef SFL_RESULT_CONCEPT_HPP
#define SFL_RESULT_CONCEPT_HPP
#include "ResultApi.hpp"

#include <concepts>
#include <type_traits>

SFL_RESULT_START

template <typename T>
concept ResultValueType =
    (
        std::is_object_v<T> &&
        std::is_destructible_v<T> &&
        !std::is_array_v<T>) ||
    std::same_as<T, void>;

template <typename E>
concept ResultErrorType =
    std::is_object_v<E> &&
    std::is_destructible_v<E> &&
    !std::is_array_v<E>;

SFL_RESULT_END

#endif