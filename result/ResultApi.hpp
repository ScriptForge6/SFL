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
 * @file ResultApi.hpp
 * @brief 定义了一些宏
 * @author Scriptforge
 * @date 2026/11/14
 */

#pragma once
#include <SFLApi.hpp>

#ifndef SFL_RESULTAPI_HPP
#define SFL_RESULTAPI_HPP

#define SFL_RESULT_START \
	SFL_START           \
	namespace Result {
#define SFL_RESULT_END \
	}                 \
	SFL_END
#define SFL_RESULT SFL Result::

#endif
