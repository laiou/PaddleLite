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

#include "operation/unary_logical_op.h"
#include "driver/kunlunxin_xtcl/converter/converter.h"
#include "utility/debug.h"
#include "utility/logging.h"

namespace nnadapter {
namespace kunlunxin_xtcl {

int ConvertUnaryLogicalOp(Converter* converter, core::Operation* operation) {
  UNARY_LOGICAL_OPERATION_EXTRACT_INPUTS_OUTPUTS

  // Convert to XTCL exprs
  auto input_expr = converter->GetMappedExpr(input_operand);
  if (!input_expr.defined()) {
    input_expr = converter->ConvertOperand(input_operand);
  }
  xtcl::xExpr unary_logical_expr;
  switch (operation->type) {
#define CONVERT_UNARY_LOGICAL_OP(type, func)                      \
  case NNADAPTER_##type: {                                        \
    unary_logical_expr = converter->builder()->func;              \
    converter->UpdateExprMap(output_operand, unary_logical_expr); \
  } break;
    CONVERT_UNARY_LOGICAL_OP(NOT, CreateUnaryOp("logical_not", input_expr));
#undef CONVERT_UNARY_LOGICAL_OP
    default:
      NNADAPTER_LOG(FATAL) << "Unsupported unary logical operation type "
                           << OperationTypeToString(operation->type)
                           << " is found.";
      break;
  }
  return NNADAPTER_NO_ERROR;
}

}  // namespace kunlunxin_xtcl
}  // namespace nnadapter
