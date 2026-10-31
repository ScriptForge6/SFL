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
 * @file GuardApi.hpp
 * @brief 定义了一些宏
 * @author Scriptforge
 * @date 2026/10/30
 */

#pragma once
#include <SFLApi.hpp>

#ifndef SFL_GUARDAPI_HPP
#define SFL_GUARDAPI_HPP

#if defined(SFL_GUARD_IMPORT) && defined(SFL_GUARD_EXPORT)
	#error "Error: Only one of SFL_LANG_IMPORT and SFL_LANG_EXPORT may be defined"
#endif
#if defined(SFL_GUARD_IMPORT)
	#define SFL_API_GUARD SFL_IMPORT_API
#elif defined(SFL_GUARD_EXPORT)
	#define SFL_API_GUARD SFL_EXPORT_API
#else
	#error "Error: Must define SFL_LANG_IMPORT or SFL_LANG_EXPORT"
#endif

#define SFL_GUARD_START \
	SFL_START           \
	namespace Guard {
#define SFL_GUARD_END \
	}                 \
	SFL_END
#define SFL_GUARD SFL Guard::

#endif
