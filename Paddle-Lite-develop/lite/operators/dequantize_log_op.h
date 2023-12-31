// Copyright (c) 2022 PaddlePaddle Authors. All Rights Reserved.
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

#include <string>
#include <vector>
#include "lite/core/kernel.h"
#include "lite/core/op_lite.h"
#include "lite/core/scope.h"
#include "lite/core/tensor.h"
#include "lite/operators/op_params.h"
#include "lite/utils/all.h"

namespace paddle {
namespace lite {
namespace operators {

class DequantizeLogOpLite : public OpLite {
 public:
  DequantizeLogOpLite() {}

  explicit DequantizeLogOpLite(const std::string &type) : OpLite(type) {}

  bool CheckShape() const override;

  bool InferShape() override;
  bool AttachImpl(const cpp::OpDesc &op_desc, lite::Scope *scope) override {
    auto x = op_desc.Input("X").front();
    auto dict = op_desc.Input("Dict").front();
    auto out = op_desc.Output("Out").front();

    param_.X = scope->FindVar(x)->GetMutable<lite::Tensor>();
    param_.Dict = scope->FindVar(dict)->GetMutable<lite::Tensor>();
    param_.Out = scope->FindVar(out)->GetMutable<lite::Tensor>();
    return true;
  }

  void AttachKernel(KernelBase *kernel) override { kernel->SetParam(param_); }

  std::string DebugString() const override { return "dequantize_log"; }

 private:
  mutable QuantizeLogParam param_;
};

}  // namespace operators
}  // namespace lite
}  // namespace paddle
