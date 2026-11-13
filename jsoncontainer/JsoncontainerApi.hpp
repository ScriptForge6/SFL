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
 * @file JsoncontainerApi.hpp
 * @brief 定义了一些宏
 * @author Scriptforge
 * @date 2026/10/23
 */

#pragma once
#include <SFLApi.hpp>

#ifndef SFL_JSONCONTAINERAPI_HPP
#define SFL_JSONCONTAINERAPI_HPP

#if defined(SFL_JSONCONTAINER_IMPORT) && defined(SFL_JSONCONTAINER_EXPORT)
	#error "Error: Only one of SFL_JSONCONTAINER_IMPORT and SFL_JSONCONTAINER_EXPORT may be defined"
#endif
#if defined(SFL_JSONCONTAINER_IMPORT)
	#define SFL_API_JSONCONTAINER SFL_IMPORT_API
#elif defined(SFL_JSONCONTAINER_EXPORT)
	#define SFL_API_JSONCONTAINER SFL_EXPORT_API
#else
	#error "Error: Must define SFL_JSONCONTAINER_IMPORT or SFL_JSONCONTAINER_EXPORT"
#endif

#define SFL_JSONCONTAINER_START \
	SFL_START          \
	namespace Jsoncontainer {
#define SFL_JSONCONTAINER_END \
	}                \
	SFL_END
#define SFL_JSONCONTAINER SFL Jsoncontainer::

#endif
