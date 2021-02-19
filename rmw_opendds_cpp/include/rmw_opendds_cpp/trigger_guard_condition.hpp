// Copyright 2015-2017 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef RMW_OPENDDS_CPP__TRIGGER_GUARD_CONDITION_HPP_
#define RMW_OPENDDS_CPP__TRIGGER_GUARD_CONDITION_HPP_

#include "rmw/types.h"

#include "rmw_opendds_cpp/visibility_control.h"

RMW_OPENDDS_CPP_PUBLIC
rmw_ret_t
trigger_guard_condition(const rmw_guard_condition_t * guard_condition_handle);

#endif  // RMW_OPENDDS_CPP__TRIGGER_GUARD_CONDITION_HPP_
