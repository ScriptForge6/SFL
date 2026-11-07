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
 * @file Lang.cpp
 * @brief i18n 类的实现
 * @author Scriptforge
 * @date 2026/10/23
 */

#include "Lang.hpp"

#include <fstream>

#include <Guard.hpp>

#include "detail/ExePath.hpp"
#include "detail/ThrowWithoutMsg.hpp"

#define SFL_LANG_INTERNAL_GUARD SFL_GUARD Guard r_guard(*this)


SFL_I18N Lang::Lang(
    std::string_view langCode,
    const std::optional<path_t>& dir/* = std::nullopt*/
) noexcept {
    try {
        set(langCode, dir);
    }
    catch (...) {
        m_lazyLoadExceptPtr = std::current_exception();
    }
}

auto SFL_I18N Lang::set(
    std::string_view langCode,
    const std::optional<path_t>& dir/* = std::nullopt*/
) -> void {
    m_langCode = langCode;
    m_dir = dir ? *dir : SFL_I18N getExeDir() / LANG;
}

auto SFL_I18N Lang::load(
    std::string_view langCode,
    const std::optional<path_t>& dir
) -> void {
    m_langCode = langCode;
    m_dir = dir ? *dir : SFL_I18N getExeDir() / LANG;
    reload();
}

auto SFL_I18N Lang::reload() -> void {
    path_t langFilePath = m_dir / (m_langCode + ".json");

    if (!checkFileExists()) {
        SFL_I18N failRuntime(
            "Language file not found: " + langFilePath.string()
        );
    }

    std::ifstream jsoninput(langFilePath);

    if (!jsoninput.is_open()) {
        SFL_I18N failRuntime(
            "Cannot open language file: " + langFilePath.string()
        );
    }

    nlohmann::json newJson;
    jsoninput >> newJson;

    m_json = std::move(newJson);
    m_lazyLoadExceptPtr = nullptr;
    jsoninput.close();
}


SFL_NODISCARD auto SFL_I18N Lang::checkFileExists() const -> bool {
    const path_t langFilePath = m_dir / (m_langCode + ".json");
    return checkPathExistsWithPath(langFilePath) &&
        checkFileIsRegular(langFilePath);
}


SFL_NODISCARD auto SFL_I18N Lang::getDir() const -> const path_t& {
    return m_dir;
}

SFL_NODISCARD auto SFL_I18N Lang::getLangCode() const -> const std::string& {
    return m_langCode;
}

SFL_NODISCARD auto SFL_I18N Lang::getJson() const -> const nlohmann::json& {
    return m_json;
}

SFL_NODISCARD auto SFL_I18N Lang::getLangName() const -> std::string {
    return m_json.value("language_name", "Unknown");
}

SFL_NODISCARD
auto SFL_I18N Lang::hasDeferredException() const -> bool {
    return static_cast<bool>(m_lazyLoadExceptPtr);
}

auto SFL_I18N Lang::GuardConstructor() -> void {
    if (hasDeferredException()) {
        std::rethrow_exception(m_lazyLoadExceptPtr);
    }
}

auto SFL_I18N Lang::GuardDestructor() -> void {
    return;
}



SFL_NODISCARD
auto SFL_I18N Lang::getAvailableLanguages(
    const std::optional<path_t>& dir/* = std::nullopt*/
) -> std::vector<std::string> {
    path_t langDir = dir ? *dir : SFL_I18N getExeDir() / LANG;
    std::vector<std::string> availableLanguages;

    if (!checkPathExistsWithPath(langDir) ||
        !checkPathIsRegular(langDir)) {
        return availableLanguages;
    }

    for (const auto& entry : std::filesystem::directory_iterator(langDir)) {
        if (entry.is_regular_file() && entry.path().extension() == ".json") {
            availableLanguages.push_back(entry.path().stem().string());
        }
    }

    return availableLanguages;
}

 
SFL_NODISCARD
auto SFL_I18N Lang::checkPathExistsWithPath(const path_t& filePath) -> bool {
    return std::filesystem::exists(filePath);
}

SFL_NODISCARD
auto SFL_I18N Lang::checkFileIsRegular(const path_t& filePath) -> bool {
    return std::filesystem::is_regular_file(filePath);
}

SFL_NODISCARD
auto SFL_I18N Lang::checkPathIsRegular(const path_t& path) -> bool {
    return std::filesystem::is_directory(path);
}