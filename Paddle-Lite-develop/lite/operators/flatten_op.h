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
#include <string>
#include <vector>
#include "lite/core/op_lite.h"
#include "lite/core/scope.h"
#include "lite/utils/all.h"

namespace paddle {
namespace lite {
namespace operators {

class FlattenOp : public OpLite {
 public:
  FlattenOp() {}
  explicit FlattenOp(const std::string &op_type) : OpLite(op_type) {}

  bool CheckShape() const override;

  bool InferType() override {
    param_.output->set_precision(param_.x->precision());
    return true;
  }

  bool InferShapeImpl() const override;

  bool AttachImpl(const cpp::OpDesc &opdesc, lite::Scope *scope) override;

  void AttachKernel(KernelBase *kernel) override { kernel->SetParam(param_); }
  std::string DebugString() const override { return "flatten"; }

 protected:
  mutable ReshapeParam param_;
  int axis_;
};

class Flatten2Op : public FlattenOp {
 public:
  Flatten2Op() : FlattenOp() {}
  explicit Flatten2Op(const std::string &op_type) : FlattenOp(op_type) {}

  bool CheckShape() const override;

  bool InferType() override {
    param_.output->set_precision(param_.x->precision());
    if (param_.xshape) param_.xshape->set_precision(PRECISION(kInt64));
    return true;
  }

  bool InferShapeImpl() const override;

  bool AttachImpl(const cpp::OpDesc &opdesc, lite::Scope *scope) override;

  void AttachKernel(KernelBase *kernel) override { kernel->SetParam(param_); }
  std::string DebugString() const override { return "flatten2"; }
};

class FlattenContiguousRangeOp : public OpLite {
 public:
  FlattenContiguousRangeOp() {}
  explicit FlattenContiguousRangeOp(const std::string &op_type)
      : OpLite(op_type) {}

  bool CheckShape() const override;
#ifndef LITE_ON_TINY_PUBLISH
  bool InferType() override {
    param_.out->set_precision(param_.x->precision());
    if (param_.xshape) param_.xshape->set_precision(PRECISION(kInt64));
    return true;
  }
#endif
  bool InferShapeImpl() const override;

  bool AttachImpl(const cpp::OpDesc &opdesc, lite::Scope *scope) override;

  void AttachKernel(KernelBase *kernel) override { kernel->SetParam(param_); }

  std::string DebugString() const override {
    return "flatten contiguous range";
  }

 protected:
  mutable FlattenContiguousRangeParam param_;
};

}  // namespace operators
}  // namespace lite
}  // namespace paddle
