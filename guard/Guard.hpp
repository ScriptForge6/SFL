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
 * @file Guard.hpp
 * @brief 定义了一个 RAII 类
 * @author Scriptforge
 * @date 2026/10/30
 */

#pragma once
#ifndef SFL_GUARD_HPP
#define SFL_GUARD_HPP
#include "GuardApi.hpp"

#include <concepts>
#include <utility>

SFL_GUARD_START
template <typename T>
concept GuardTConcept = 
    requires(T t) {
        t.GuardConstructor();
        t.GuardDestructor();
    };

/**
 * @brief 自动检测 RAII
 */
template <GuardTConcept T>
class Guard {
public:
    Guard() = delete;
    Guard(const Guard&) = delete;
    Guard(Guard&&) = delete;
    /**
     * @brief Guard 的构造函数
     * @param[in] owner 父类的引用
     */
    explicit Guard(T& owner);
    /**
     * @brief Guard 的析构函数
     */
    ~Guard();
private:
    T& m_owner;
};
SFL_GUARD_END

//实现部分

template <SFL_GUARD GuardTConcept T>
SFL_GUARD Guard<T>::Guard(T& owner)
: m_owner(owner) {
    m_owner.GuardConstructor();
}

template <SFL_GUARD GuardTConcept T>
SFL_GUARD Guard<T>::~Guard() {
    m_owner.GuardDestructor();
}

#endif