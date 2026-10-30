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
 * @file Msg.cpp
 * @brief 实现了信息类
 * @author Scriptforge
 * @date 2026/10/30
 */

#include "Msg.hpp"

SFL_MSG Msg::Msg(
    std::string_view key,
    std::vector<std::string_view> args/* = {}*/
) {
    try {
        m_key = key;
        m_args.reserve(args.size()); // 提前预留空间

        for (auto arg : args) {
            m_args.emplace_back(arg);// 显式逐个构造
        }
    }
    catch (...) {
        m_lazyLoadExceptPtr = std::current_exception();
    }
}