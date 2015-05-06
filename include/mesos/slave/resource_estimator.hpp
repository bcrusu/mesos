/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __MESOS_SLAVE_RESOURCE_ESTIMATOR_HPP__
#define __MESOS_SLAVE_RESOURCE_ESTIMATOR_HPP__

#include <mesos/resources.hpp>

#include <process/future.hpp>

#include <stout/nothing.hpp>
#include <stout/try.hpp>

namespace mesos {
namespace slave {

// A slave component used for oversubscription. It estimates and
// predicts the total resources used on the slave and informs the
// master about resources that can be oversubscribed.
class ResourceEstimator
{
public:
  virtual ~ResourceEstimator() {}

  // Initializes this resource estimator. This method needs to be
  // called before any other member method is called.
  // TODO(jieyu): Pass ResourceMonitor* once it's exposed.
  virtual Try<Nothing> initialize() = 0;

  // Returns the current estimation about the *maximum* amount of
  // resources that can be oversubscribed on the slave. A new
  // estimation will invalidate all the previously returned
  // estimations. The slave will be calling this method continuously
  // to get the most up-to-date estimation and forward them to the
  // master. As a result, it is up to the resource estimator to
  // control the speed of sending estimations to the master. To avoid
  // overwhelming the master, it is recommended that the resource
  // estimator should return an estimation only if the current
  // estimation is significantly different from the previous one.
  virtual process::Future<Resources> oversubscribed() = 0;
};

} // namespace slave {
} // namespace mesos {

#endif // __MESOS_SLAVE_RESOURCE_ESTIMATOR_HPP__
