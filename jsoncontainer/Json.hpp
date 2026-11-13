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
 * @file Json.hpp
 * @brief 定义了一个 JSON 类
 * @author Scriptforge
 * @date 2026/11/13
 */

#pragma once
#ifndef SFL_JSON_HPP
#define SFL_JSON_HPP
#include "JsoncontainerApi.hpp"

#include <shared_mutex>

#include <nlohmann/json.hpp>

SFL_JSONCONTAINER_START

/**
 * @brief 线程安全的 JSON 容器
 *
 * @details
 * 使用 shared_mutex 保护内部 JSON 数据。
 * 读取操作允许并发，修改操作独占访问。
 *
 * 不直接返回内部引用、指针或迭代器。
 */
class SFL_API_JSONCONTAINER Json {
public:
    using json_t = nlohmann::json;

    using value_type = json_t;
    using size_type = json_t::size_type;
    using difference_type = json_t::difference_type;
    using value_t = json_t::value_t;

    using string_t = json_t::string_t;
    using object_t = json_t::object_t;
    using array_t = json_t::array_t;

    using exception = json_t::exception;
    using parse_error = json_t::parse_error;
    using type_error = json_t::type_error;
    using out_of_range = json_t::out_of_range;

public:
    // 构造与析构
    Json() = default;
    Json(const Json& other);
    Json(Json&& other);

    Json(const json_t& other);
    Json(json_t&& other);

    ~Json() = default;

    // 赋值
    auto operator=(const Json& other) -> Json&;
    auto operator=(Json&& other) -> Json&;

    auto operator=(const json_t& other) -> Json&;
    auto operator=(json_t&& other) -> Json&;

    // 比较
    auto operator==(const Json& other) const -> bool;
    auto operator!=(const Json& other) const -> bool;

    // 基础信息
    SFL_NODISCARD auto type() const -> value_t;
    SFL_NODISCARD auto size() const -> size_type;
    SFL_NODISCARD auto empty() const -> bool;
    SFL_NODISCARD auto max_size() const -> size_type;

    // 类型判断
    SFL_NODISCARD auto is_null() const -> bool;
    SFL_NODISCARD auto is_object() const -> bool;
    SFL_NODISCARD auto is_array() const -> bool;
    SFL_NODISCARD auto is_string() const -> bool;
    SFL_NODISCARD auto is_boolean() const -> bool;
    SFL_NODISCARD auto is_number() const -> bool;
    SFL_NODISCARD auto is_number_integer() const -> bool;
    SFL_NODISCARD auto is_number_unsigned() const -> bool;
    SFL_NODISCARD auto is_number_float() const -> bool;
    SFL_NODISCARD auto is_primitive() const -> bool;
    SFL_NODISCARD auto is_structured() const -> bool;
    SFL_NODISCARD auto is_discarded() const -> bool;

    // 元素查询
    SFL_NODISCARD
    auto contains(const std::string& key) const -> bool;

    SFL_NODISCARD
    auto at(const std::string& key) const -> json_t;

    SFL_NODISCARD
    auto at(size_type index) const -> json_t;

    // 获取默认值
    template <typename ValueType>
    SFL_NODISCARD
    auto value(
        const std::string& key,
        ValueType&& default_value
    ) const -> std::decay_t<ValueType>;

    // 类型转换
    template <typename ValueType>
    SFL_NODISCARD
    auto get() const -> ValueType;

    template <typename ValueType>
    auto get_to(ValueType& value) const -> void;

    // 获取底层 JSON 副本
    SFL_NODISCARD
    auto getJson() const -> json_t;

    // 修改 Object
    auto set(
        const std::string& key,
        const json_t& value
    ) -> void;

    auto set(
        const std::string& key,
        json_t&& value
    ) -> void;

    template <typename ValueType>
    auto set(
        const std::string& key,
        ValueType&& value
    ) -> void;

    SFL_NODISCARD
    auto erase(const std::string& key) -> bool;

    // 修改 Array
    auto push_back(const json_t& value) -> Json&;
    auto push_back(json_t&& value) -> Json&;

    template <typename ValueType>
    auto push_back(ValueType&& value) -> Json&;

    template <typename... Args>
    auto emplace_back(Args&&... args) -> Json&;

    auto erase(size_type index) -> Json&;

    // 通用修改
    auto clear() -> void;

    auto update(const json_t& value) -> void;
    auto update(const Json& value) -> void;

    auto merge_patch(const json_t& value) -> void;
    auto merge_patch(const Json& value) -> void;

    auto swap(Json& other) -> void;

    // 序列化
    SFL_NODISCARD
    auto dump(
        int indent = -1,
        char indent_char = ' ',
        bool ensure_ascii = false
    ) const -> std::string;

    // 解析
    static auto parse(const std::string& text) -> Json;

private:
    mutable std::shared_mutex m_mutex;
    json_t m_json;
};


// ============================================================
// 模板实现
// ============================================================

template <typename ValueType>
auto Json::value(
    const std::string& key,
    ValueType&& default_value
) const -> std::decay_t<ValueType> {
    std::shared_lock lock(m_mutex);

    return m_json.value(
        key,
        std::forward<ValueType>(default_value)
    );
}

template <typename ValueType>
auto Json::get() const -> ValueType {
    std::shared_lock lock(m_mutex);
    return m_json.template get<ValueType>();
}

template <typename ValueType>
auto Json::get_to(ValueType& value) const -> void {
    std::shared_lock lock(m_mutex);
    m_json.get_to(value);
}

template <typename ValueType>
auto Json::set(
    const std::string& key,
    ValueType&& value
) -> void {
    json_t converted(std::forward<ValueType>(value));

    std::unique_lock lock(m_mutex);
    m_json[key] = std::move(converted);
}

template <typename ValueType>
auto Json::push_back(ValueType&& value) -> void {
    json_t converted(std::forward<ValueType>(value));

    std::unique_lock lock(m_mutex);
    m_json.push_back(std::move(converted));
}

template <typename... Args>
auto Json::emplace_back(Args&&... args) -> void {
    std::unique_lock lock(m_mutex);
    m_json.emplace_back(std::forward<Args>(args)...);
}

SFL_JSONCONTAINER_END

#endif