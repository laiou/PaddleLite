// Copyright (c) 2021 PaddlePaddle Authors. All Rights Reserved.
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

#include "lite/kernels/nnadapter/converter/converter.h"

namespace paddle {
namespace lite {
namespace kernels {
namespace nnadapter {

int ConvertCast(Converter* converter, OpInfo* op, Scope* scope) {
  // Extract op attributes
  // Input
  auto x_name = op->Input("X").front();
  auto x_scale_name = "X0_scale";
  std::vector<float> x_scales;
  if (op->HasInputScale(x_scale_name, true)) {
    x_scales = op->GetInputScale(x_scale_name, true);
  }
  // Out dtype
  auto out_dtype = op->GetAttr<int>("out_dtype");
  // Output
  auto output_name = op->Output("Out").front();
  auto output_scale_name = "Out0_scale";
  std::vector<float> output_scales;
  if (op->HasOutputScale(output_scale_name, true)) {
    output_scales = op->GetOutputScale(output_scale_name, true);
    out_dtype = 21;  //  INT8 = 21
  }

  // Convert to NNAdapter operands and operation
  // Input operand
  auto input_operand = converter->AddInputOperand(scope, x_name, {}, x_scales);
  // Dtype operand
  int32_t dtype = 0;
  if (op->HasOutputScale(output_scale_name, true)) {
    dtype = ConvertFluidDataTypeToNNPrecisionCode(
        out_dtype, output_scales.data(), 1, 1);
  } else {
    dtype = ConvertFluidDataTypeToNNPrecisionCode(out_dtype);
  }
  auto dtype_operand = converter->AddConstantOperand(dtype);
  // Output operand
  auto output_operand = converter->AddOutputOperand(output_name, output_scales);
  // Clip operation
  converter->AddOperation(
      NNADAPTER_CAST, {input_operand, dtype_operand}, {output_operand});
  return NO_ERROR;
}

}  // namespace nnadapter
}  // namespace kernels
}  // namespace lite
}  // namespace paddle
