// Copyright 2015 Open Source Robotics Foundation, Inc.
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

#ifndef RMW_OPENDDS_SHARED_CPP__TYPES_HPP_
#define RMW_OPENDDS_SHARED_CPP__TYPES_HPP_

#include <cassert>
#include <exception>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <mutex>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>

#include "rmw/rmw.h"
#include "topic_cache.hpp"
#include "rmw_opendds_shared_cpp/opendds_include.hpp"
#include "rmw_opendds_shared_cpp/visibility_control.h"
#include "dds/DCPS/WaitSet.h"

enum EntityType {Publisher, Subscriber};

class CustomDataReaderListener
  : public DDS::DataReaderListener
{
public:
  explicit
  CustomDataReaderListener(
    const char * implementation_identifier, rmw_guard_condition_t * graph_guard_condition)
  : implementation_identifier_(implementation_identifier),
    graph_guard_condition_(graph_guard_condition)
  {}

  virtual void add_information(
    const DDS::InstanceHandle_t & participant_instance_handle,
    const DDS::InstanceHandle_t & instance_handle,
    const std::string & topic_name,
    const std::string & type_name,
    EntityType entity_type);

  RMW_OPENDDS_SHARED_CPP_PUBLIC
  virtual void remove_information(
    const DDS::InstanceHandle_t & instance_handle,
    EntityType entity_type);

  RMW_OPENDDS_SHARED_CPP_PUBLIC
  virtual void trigger_graph_guard_condition();

  size_t count_topic(const char * topic_name);

  void fill_topic_names_and_types(
    bool no_demangle,
    std::map<std::string, std::set<std::string>> & topic_names_to_types);

  void fill_service_names_and_types(
    std::map<std::string, std::set<std::string>> & services);

  void fill_topic_names_and_types_by_guid(
    bool no_demangle,
    std::map<std::string, std::set<std::string>> & topic_names_to_types_by_guid,
    DDS::InstanceHandle_t & participant_guid);

  void fill_service_names_and_types_by_guid(
    std::map<std::string, std::set<std::string>> & services,
    DDS::InstanceHandle_t & participant_guid);

  virtual void on_requested_deadline_missed(
    ::DDS::DataReader_ptr, const ::DDS::RequestedDeadlineMissedStatus&) {}

  virtual void on_requested_incompatible_qos(
    ::DDS::DataReader_ptr, const ::DDS::RequestedIncompatibleQosStatus&) {}

  virtual void on_sample_rejected(
    ::DDS::DataReader_ptr, const ::DDS::SampleRejectedStatus&) {}

  virtual void on_liveliness_changed(
    ::DDS::DataReader_ptr, const ::DDS::LivelinessChangedStatus&) {}

  virtual void on_subscription_matched(
    ::DDS::DataReader_ptr, const ::DDS::SubscriptionMatchedStatus&) {}

  virtual void on_sample_lost(
    ::DDS::DataReader_ptr, const ::DDS::SampleLostStatus&) {}

protected:
  std::mutex mutex_;
  TopicCache<DDS::InstanceHandle_t> topic_cache;

private:
  const char * implementation_identifier_;
  rmw_guard_condition_t * graph_guard_condition_;
};

class CustomPublisherListener
  : public CustomDataReaderListener
{
public:
  CustomPublisherListener(
    const char * implementation_identifier, rmw_guard_condition_t * graph_guard_condition)
  : CustomDataReaderListener(implementation_identifier, graph_guard_condition)
  {}

  virtual void on_data_available(DDS::DataReader * reader);
};

class CustomSubscriberListener
  : public CustomDataReaderListener
{
public:
  CustomSubscriberListener(
    const char * implementation_identifier, rmw_guard_condition_t * graph_guard_condition)
  : CustomDataReaderListener(implementation_identifier, graph_guard_condition)
  {}

  virtual void on_data_available(DDS::DataReader * reader);
};

struct OpenDDSNodeInfo
{
  DDS::DomainParticipant_var participant;
  CustomPublisherListener * publisher_listener;
  CustomSubscriberListener * subscriber_listener;
  rmw_guard_condition_t * graph_guard_condition;
  OpenDDSNodeInfo() :
    participant(nullptr),
    publisher_listener(nullptr),
    subscriber_listener(nullptr),
    graph_guard_condition(nullptr) {}
};

struct OpenDDSPublisherGID
{
  DDS::InstanceHandle_t publication_handle;
};

struct OpenDDSWaitSetInfo
{
  DDS::WaitSet * wait_set;
  DDS::ConditionSeq * active_conditions;
  DDS::ConditionSeq * attached_conditions;
};

#endif  // RMW_OPENDDS_SHARED_CPP__TYPES_HPP_
