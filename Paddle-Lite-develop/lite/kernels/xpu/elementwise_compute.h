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

namespace paddle {
namespace lite {
namespace kernels {
namespace xpu {

template <class T, class Functor, PrecisionType PType>
class ElementwiseCompute : public KernelLite<TARGET(kXPU), PType> {
 public:
  using param_t = operators::ElementwiseParam;

  virtual void Run();
  void PrepareForRun() override;

  virtual ~ElementwiseCompute() = default;

 private:
  XPUScratchPadGuard quant_x_max_value_guard_;
  XPUScratchPadGuard quant_y_max_value_guard_;
  XPUScratchPadGuard quant_z_max_value_guard_;
  XPUScratchPadGuard broadcast_y_guard_;
};

}  // namespace xpu
}  // namespace kernels
}  // namespace lite
}  // namespace paddle