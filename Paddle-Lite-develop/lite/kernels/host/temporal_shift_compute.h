// Copyright (c) 2019 PaddlePaddle Authors. All Rights Reserved.
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

#pragma once
#include "lite/core/kernel.h"
#include "lite/operators/temporal_shift_op.h"
#ifdef LITE_WITH_PROFILE
#include <string>
#include "lite/core/profile/profiler.h"
#endif

namespace paddle {
namespace lite {
namespace kernels {
namespace host {

template <PrecisionType PType, PrecisionType OutType>
class TemporalShiftCompute : public KernelLite<TARGET(kHost), PType> {
 public:
  using param_t = operators::TemporalShiftParam;

  void Run() override;

  virtual ~TemporalShiftCompute() = default;

#ifdef LITE_WITH_PROFILE
  virtual void SetProfileRuntimeKernelInfo(
      paddle::lite::profile::OpCharacter* ch) {
    ch->kernel_func_name = kernel_func_name_;
  }
  std::string kernel_func_name_{"Temporal Shift"};
#endif
};

}  // namespace host
}  // namespace kernels
}  // namespace lite
}  // namespace paddle
