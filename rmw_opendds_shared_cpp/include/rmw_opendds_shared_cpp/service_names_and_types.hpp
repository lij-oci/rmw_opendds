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

#ifndef RMW_OPENDDS_SHARED_CPP__SERVICE_NAMES_AND_TYPES_HPP_
#define RMW_OPENDDS_SHARED_CPP__SERVICE_NAMES_AND_TYPES_HPP_

#include "rcutils/allocator.h"

#include "rmw_opendds_shared_cpp/visibility_control.h"

#include "rmw/get_service_names_and_types.h"

RMW_OPENDDS_SHARED_CPP_PUBLIC
rmw_ret_t
get_service_names_and_types(
  const char * implementation_identifier,
  const rmw_node_t * node,
  rcutils_allocator_t * allocator,
  rmw_names_and_types_t * service_names_and_types);

#endif  // RMW_OPENDDS_SHARED_CPP__SERVICE_NAMES_AND_TYPES_HPP_
