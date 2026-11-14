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
 * @file Json.cpp
 * @brief JSON 类的实现
 * @author Scriptforge
 * @date 2026/11/13
 */

#include "Json.hpp"

#include <scoped_allocator>
#include <utility>


// 构造函数
SFL_JSONCONTAINER Json::Json(const Json& other) {
    std::shared_lock lock(other.m_mutex);
    m_json = other.m_json;
}

SFL_JSONCONTAINER Json::Json(Json&& other) {
    std::unique_lock lock(other.m_mutex);
    m_json = std::move(other.m_json);
}

SFL_JSONCONTAINER Json::Json(const json_t& other)
    : m_json(other) {
}

SFL_JSONCONTAINER Json::Json(json_t&& other)
    : m_json(std::move(other)) {
}


// 赋值运算符
auto SFL_JSONCONTAINER Json::operator=(const Json& other) -> Json& {
    if (this == &other) {
        return *this;
    }

    std::scoped_lock lock(m_mutex, other.m_mutex);
    m_json = other.m_json;

    return *this;
}

auto SFL_JSONCONTAINER Json::operator=(Json&& other) -> Json& {
    if (this == &other) {
        return *this;
    }

    std::scoped_lock lock(m_mutex, other.m_mutex);
    m_json = std::move(other.m_json);

    return *this;
}

auto SFL_JSONCONTAINER Json::operator=(const json_t& other) -> Json& {
    std::unique_lock lock(m_mutex);
    m_json = other;

    return *this;
}

auto SFL_JSONCONTAINER Json::operator=(json_t&& other) -> Json& {
    std::unique_lock lock(m_mutex);
    m_json = std::move(other);

    return *this;
}


// 比较
auto SFL_JSONCONTAINER Json::operator==(const Json& other) const -> bool {
    if (this == &other) {
        return true;
    }

    std::scoped_lock lock(m_mutex, other.m_mutex);
    return m_json == other.m_json;
}

auto SFL_JSONCONTAINER Json::operator!=(const Json& other) const -> bool {
    return !(*this == other);
}


// 流运算符
auto SFL_JSONCONTAINER operator>>(std::istream& is, Json& json)
    -> std::istream& {
    Json::json_t temp;
    is >> temp;
    json = std::move(temp);
    return is;
}

auto SFL_JSONCONTAINER operator<<(std::ostream& os, const Json& json)
    -> std::ostream& {
    os << json.getJson();
    return os;
}


// 基础信息
SFL_NODISCARD auto SFL_JSONCONTAINER Json::type() const -> value_t {
    std::shared_lock lock(m_mutex);
    return m_json.type();
}

SFL_NODISCARD auto SFL_JSONCONTAINER Json::size() const -> size_type {
    std::shared_lock lock(m_mutex);
    return m_json.size();
}

SFL_NODISCARD auto SFL_JSONCONTAINER Json::empty() const -> bool {
    std::shared_lock lock(m_mutex);
    return m_json.empty();
}

SFL_NODISCARD auto SFL_JSONCONTAINER Json::max_size() const -> size_type {
    std::shared_lock lock(m_mutex);
    return m_json.max_size();
}


// 类型判断
SFL_NODISCARD auto SFL_JSONCONTAINER Json::is_null() const -> bool {
    std::shared_lock lock(m_mutex);
    return m_json.is_null();
}

SFL_NODISCARD auto SFL_JSONCONTAINER Json::is_object() const -> bool {
    std::shared_lock lock(m_mutex);
    return m_json.is_object();
}

SFL_NODISCARD auto SFL_JSONCONTAINER Json::is_array() const -> bool {
    std::shared_lock lock(m_mutex);
    return m_json.is_array();
}

SFL_NODISCARD auto SFL_JSONCONTAINER Json::is_string() const -> bool {
    std::shared_lock lock(m_mutex);
    return m_json.is_string();
}

SFL_NODISCARD auto SFL_JSONCONTAINER Json::is_boolean() const -> bool {
    std::shared_lock lock(m_mutex);
    return m_json.is_boolean();
}

SFL_NODISCARD auto SFL_JSONCONTAINER Json::is_number() const -> bool {
    std::shared_lock lock(m_mutex);
    return m_json.is_number();
}

SFL_NODISCARD auto SFL_JSONCONTAINER Json::is_number_integer() const -> bool {
    std::shared_lock lock(m_mutex);
    return m_json.is_number_integer();
}

SFL_NODISCARD auto SFL_JSONCONTAINER Json::is_number_unsigned() const -> bool {
    std::shared_lock lock(m_mutex);
    return m_json.is_number_unsigned();
}

SFL_NODISCARD auto SFL_JSONCONTAINER Json::is_number_float() const -> bool {
    std::shared_lock lock(m_mutex);
    return m_json.is_number_float();
}

SFL_NODISCARD auto SFL_JSONCONTAINER Json::is_primitive() const -> bool {
    std::shared_lock lock(m_mutex);
    return m_json.is_primitive();
}

SFL_NODISCARD auto SFL_JSONCONTAINER Json::is_structured() const -> bool {
    std::shared_lock lock(m_mutex);
    return m_json.is_structured();
}

SFL_NODISCARD auto SFL_JSONCONTAINER Json::is_discarded() const -> bool {
    std::shared_lock lock(m_mutex);
    return m_json.is_discarded();
}


// 元素查询
SFL_NODISCARD auto SFL_JSONCONTAINER Json::contains(const std::string& key) const -> bool {
    std::shared_lock lock(m_mutex);
    return m_json.contains(key);
}

SFL_NODISCARD auto SFL_JSONCONTAINER Json::at(const std::string& key) const -> json_t {
    std::shared_lock lock(m_mutex);
    return m_json.at(key);
}

SFL_NODISCARD auto SFL_JSONCONTAINER Json::at(size_type index) const -> json_t {
    std::shared_lock lock(m_mutex);
    return m_json.at(index);
}


// 获取底层 JSON 副本
SFL_NODISCARD auto SFL_JSONCONTAINER Json::getJson() const -> json_t {
    std::shared_lock lock(m_mutex);
    return m_json;
}


// 修改 Object
auto SFL_JSONCONTAINER Json::set(
    const std::string& key,
    const json_t& value
) -> Json& {
    std::unique_lock lock(m_mutex);
    m_json[key] = value;
    return *this;
}

auto SFL_JSONCONTAINER Json::set(
    const std::string& key,
    json_t&& value
) -> Json& {
    std::unique_lock lock(m_mutex);
    m_json[key] = std::move(value);
    return *this;
}

auto SFL_JSONCONTAINER Json::erase(const std::string& key) -> bool {
    std::unique_lock lock(m_mutex);

    if (!m_json.is_object()) {
        return false;
    }

    return m_json.erase(key) > 0;
}


// 修改 Array
auto SFL_JSONCONTAINER Json::push_back(const json_t& value) -> Json& {
    std::unique_lock lock(m_mutex);
    m_json.push_back(value);
    return *this;
}

auto SFL_JSONCONTAINER Json::push_back(json_t&& value) -> Json& {
    std::unique_lock lock(m_mutex);
    m_json.push_back(std::move(value));
    return *this;
}

auto SFL_JSONCONTAINER Json::erase(size_type index) -> Json& {
    std::unique_lock lock(m_mutex);
    m_json.erase(index);
    return *this;
}


// 通用修改
auto SFL_JSONCONTAINER Json::clear() -> void {
    std::unique_lock lock(m_mutex);
    m_json.clear();
}

auto SFL_JSONCONTAINER Json::update(const json_t& value) -> void {
    std::unique_lock lock(m_mutex);
    m_json.update(value);
}

auto SFL_JSONCONTAINER Json::update(const Json& value) -> void {
    // 先取得另一个对象的快照，避免同时锁定两个对象
    auto snapshot = value.getJson();

    std::unique_lock lock(m_mutex);
    m_json.update(snapshot);
}

auto SFL_JSONCONTAINER Json::merge_patch(const json_t& value) -> void {
    std::unique_lock lock(m_mutex);
    m_json.merge_patch(value);
}

auto SFL_JSONCONTAINER Json::merge_patch(const Json& value) -> void {
    auto snapshot = value.getJson();

    std::unique_lock lock(m_mutex);
    m_json.merge_patch(snapshot);
}

auto SFL_JSONCONTAINER Json::swap(Json& other) -> void {
    if (this == &other) {
        return;
    }

    std::scoped_lock lock(m_mutex, other.m_mutex);
    m_json.swap(other.m_json);
}


// 序列化
auto SFL_JSONCONTAINER Json::dump(
    int indent,
    char indent_char,
    bool ensure_ascii
) const -> std::string {
    // 获取快照后，在锁外进行序列化
    auto snapshot = getJson();

    return snapshot.dump(
        indent,
        indent_char,
        ensure_ascii
    );
}


// 解析
auto SFL_JSONCONTAINER Json::parse(const std::string& text) -> Json {
    return Json(json_t::parse(text));
}
