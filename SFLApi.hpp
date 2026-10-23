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
 * @file KiracApi.hpp
 * @brief 定义了一些宏
 * @author Scriptforge
 * @date 2026/10/16
 */

#pragma once
#ifndef SFL_SFLAPI_HPP
#define SFL_SFLAPI_HPP

#if defined(_WIN32) || defined(_WIN64)
	#define SFL_WIN 1
#elif defined(__APPLE__)
	#include <TargetConditionals.h>
	#define SFL_APPLE 1
	#if TARGET_OS_IPHONE
		#define SFL_IOS 1
	#else
		#define SFL_MAC 1
	#endif
#elif defined(__linux__)
	#define SFL_LINUX 1
#elif defined(__FreeBSD__)
	#define SFL_FREEBSD 1
#elif defined(__EMSCRIPTEN__)
	#define SFL_WASM 1
#else
	#error "Unsupported platform"
#endif

#if defined(_MSVC_LANG)
	#define SFL_CPLUSPLUS _MSVC_LANG
#elif defined(__cplusplus)
	#define SFL_CPLUSPLUS __cplusplus
#else
	#define SFL_CPLUSPLUS 0L
#endif

#if defined(_MSC_VER)
	#define SFL_MSVC 1
	#define SFL_MSVC_VER _MSC_VER
#elif defined(__clang__)
	#define SFL_CLANG 1
	#define SFL_CLANG_MAJOR __clang_major__
	#define SFL_CLANG_MINOR __clang_minor__
	#define SFL_CLANG_PATCH __clang_patchlevel__
#elif defined(__GNUC__)
	#define SFL_GNU 1
	#define SFL_GNU_MAJOR __GNUC__
	#define SFL_GNU_MINOR __GNUC_MINOR__
	#define SFL_GNU_PATCH __GNUC_PATCHLEVEL__
#endif


#ifndef SFL_IMPORT_API
	#if defined(SFL_STATIC)
		#define SFL_IMPORT_API
	#else
		#if defined(SFL_WIN)
			#define SFL_IMPORT_API __declspec(dllimport)
		#else
			#define SFL_IMPORT_API
		#endif
	#endif
#endif

#ifndef SFL_EXPORT_API
	#if defined(SFL_STATIC)
		#define SFL_EXPORT_API
	#else
		#if defined(SFL_WIN)
			#define SFL_EXPORT_API __declspec(dllexport)
		#else
			#define SFL_EXPORT_API __attribute__((visibility("default")))
		#endif
	#endif
#endif

// ---- SFL_DEPRECATED(msg):标记废弃 ----
#if SFL_CPLUSPLUS >= 201402L
	#define SFL_DEPRECATED(msg) [[deprecated(msg)]]
#elif defined(SFL_MSVC)
	#define SFL_DEPRECATED(msg) __declspec(deprecated(msg))
#elif defined(SFL_GNU) || defined(SFL_CLANG)
	#define SFL_DEPRECATED(msg) __attribute__((deprecated(msg)))
#else
	#define SFL_DEPRECATED(msg)
#endif

// ---- SFL_NODISCARD:忽略返回值时警告 ----
#if SFL_CPLUSPLUS >= 201703L
	#define SFL_NODISCARD [[nodiscard]]
#elif defined(SFL_GNU) || defined(SFL_CLANG)
	#define SFL_NODISCARD __attribute__((warn_unused_result))
#elif defined(SFL_MSVC) && SFL_MSVC_VER >= 1700
	#include <sal.h>
	#define SFL_NODISCARD _Check_return_
#else
	#define SFL_NODISCARD
#endif



#endif