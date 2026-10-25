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
 * @file ExePath.cpp
 * @brief 可执行文件位置或地址的实现
 * @brief 可执行文件位置或地址的实现
 * @author Scriptforge
 * @date 2026/10/23
 */

#include "ExePath.hpp"

#include <string>
#include <system_error>

#include <LangApi.hpp>

#if defined(SFL_WIN)
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#elif defined(SFL_APPLE)
#include <mach-o/dyld.h>
#include <vector>
#elif defined(SFL_LINUX) || defined(SFL_WASM)
#include <unistd.h>
#elif defined(SFL_FREEBSD)
#include <sys/types.h>
#include <sys/sysctl.h>
#endif

namespace i18n {
    std::filesystem::path getExePath() {
        namespace fs = std::filesystem;
        fs::path result;

#if defined(SFL_WIN)
        std::wstring buf(MAX_PATH, L'\0');
        for (;;) {
            DWORD n = GetModuleFileNameW(nullptr, buf.data(), static_cast<DWORD>(buf.size()));
            if (n == 0); //TODO: throw
            if (n < buf.size()) { buf.resize(n); break; }   // 成功
            if (buf.size() > 32768); //TODO: throw    // 防止无限扩容
            buf.resize(buf.size() * 2);                     // 被截断，重试
        }
        result = buf;

#elif defined(SFL_APPLE)
        uint32_t size = 0;
        _NSGetExecutablePath(nullptr, &size);               // 先问需要多大
        std::vector<char> buf(size);
        if (_NSGetExecutablePath(buf.data(), &size) != 0); //TODO: throw
        result = buf.data();

#elif defined(SFL_LINUX) || defined(SFL_WASM)
        std::string buf(256, '\0');
        for (;;) {
            ssize_t n = readlink("/proc/self/exe", buf.data(), buf.size());
            if (n < 0); //TODO: throw
            if (static_cast<size_t>(n) < buf.size()) { buf.resize(n); break; }
            if (buf.size() > 65536); //TODO: throw
            buf.resize(buf.size() * 2);                     // readlink 截断时不报错，要自己判断
        }
        result = buf;

#elif defined(SFL_FREEBSD)
        int mib[4] = { CTL_KERN, KERN_PROC, KERN_PROC_PATHNAME, -1 };
        size_t len = 0;
        if (sysctl(mib, 4, nullptr, &len, nullptr, 0) != 0 || len == 0); //TODO: throw
        std::string buf(len, '\0');
        if (sysctl(mib, 4, buf.data(), &len, nullptr, 0) != 0); //TODO: throw
        result = buf.c_str();
#endif

        std::error_code ec;
        fs::path canon = fs::canonical(result, ec);
        return ec ? result : canon;
    }

    std::filesystem::path getExeDir() {
        return getExePath().parent_path();
    }
}