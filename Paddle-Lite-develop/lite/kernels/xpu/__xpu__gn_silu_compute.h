// Copyright (c) 2023 PaddlePaddle Authors. All Rights Reserved.
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

#include <vector>
#include "lite/backends/xpu/xpu_header_sitter.h"
#include "lite/core/kernel.h"
#include "lite/core/op_registry.h"

namespace paddle {
namespace lite {
namespace kernels {
namespace xpu {

template <typename InType, PrecisionType PType>
class XPUGnSiluCompute : public KernelLite<TARGET(kXPU), PType> {
 public:
  using param_t = operators::XPUGnSiluParam;

  virtual void PrepareForRun();

  virtual void Run();

  virtual ~XPUGnSiluCompute() = default;

 private:
  std::vector<const float *> arg_gn_scale_;
  std::vector<const float *> arg_gn_bias_;
};

}  // namespace xpu
}  // namespace kernels
}  // namespace lite
}  // namespace paddle
