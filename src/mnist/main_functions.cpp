/* Copyright 2020 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include "main_functions.h"
#include "core.h"

#include "../base/dataprovider/idataprovider.h"
#include "../base/dataprovider/dataproviderserial.h"
#include "../base/json/json.h"
#include "test_data/dataprovidertest.h"

#include <stdio.h>
#include <iostream>
#include <list>
#include "pico/stdlib.h"

#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/version.h"

#include "train/model.h"


// Globals, used for compatibility with Arduino-style sketches.
namespace {
tflite::ErrorReporter* error_reporter = nullptr;
const tflite::Model* model = nullptr;
tflite::MicroInterpreter* interpreter = nullptr;
TfLiteTensor* input = nullptr;
TfLiteTensor* output = nullptr;
int inference_count = 0;

constexpr int kTensorArenaSize = 120000;
uint8_t tensor_arena[kTensorArenaSize];
}  // namespace

static CoreStateMachine s_oSM;

// The name of this function is important for Arduino compatibility.
void setup() 
{
  static tflite::MicroErrorReporter micro_error_reporter;
  error_reporter = &micro_error_reporter;

  // Map the model into a usable data structure. This doesn't involve any
  // copying or parsing, it's a very lightweight operation.
  model = tflite::GetModel(g_model);
  if (model->version() != TFLITE_SCHEMA_VERSION) 
  {
    TF_LITE_REPORT_ERROR(error_reporter,
                         "Model provided is schema version %d not equal "
                         "to supported version %d.",
                         model->version(), TFLITE_SCHEMA_VERSION);
    return;
  }

  // This pulls in all the operation implementations we need.
  // NOLINTNEXTLINE(runtime-global-variables)
  static tflite::AllOpsResolver resolver;

  // Build an interpreter to run the model with.
  static tflite::MicroInterpreter static_interpreter(model, resolver, tensor_arena, kTensorArenaSize, error_reporter);
  interpreter = &static_interpreter;

  // Allocate memory from the tensor_arena for the model's tensors.
  TfLiteStatus allocate_status = interpreter->AllocateTensors();
  if (allocate_status != kTfLiteOk) 
  {
    TF_LITE_REPORT_ERROR(error_reporter, "AllocateTensors() failed");
    return;
  }

  // Obtain pointers to the model's input and output tensors.
  input = interpreter->input(0);
  output = interpreter->output(0);

  // Keep track of how many inferences we have performed.
  inference_count = 0;

  printf("Input type: %d\n", input->type);
  printf("Input dims size: %d\n", input->dims->size);
  printf("Input dims: (");
  for(int n = 0; n < input->dims->size; n++)
  {
    printf("%d ", input->dims->data[n]);
  }
  printf(")\n");

  printf("Output type: %d\n", output->type);
  printf("Output dims size: %d\n", output->dims->size);
  printf("Output dims: (");
  for(int n = 0; n < output->dims->size; n++)
  {
    printf("%d ", output->dims->data[n]);
  }
  printf(")\n");
}



void loop() 
{
  IDataProvider* pProvider = new DataProviderSerial();
  pProvider->fetchData(input->data.uint8, 3136);
  delete pProvider;

  nlohmann::json oJsonReport;

  const absolute_time_t coTimeStart = get_absolute_time();

  TfLiteStatus invoke_status = interpreter->Invoke();
  if (invoke_status != kTfLiteOk) 
  {
    TF_LITE_REPORT_ERROR(error_reporter, "Invoke failed!\n");
    return;
  }

  const absolute_time_t coTimeStop = get_absolute_time();
  const uint64_t cunDuration_us = absolute_time_diff_us(coTimeStart, coTimeStop);

  oJsonReport["timing"] = cunDuration_us;

  std::list<float> lstProbabilities;
  for(int n = 0; n < 10; n++)
  {
    lstProbabilities.push_back(output->data.f[n]);
  }

  oJsonReport["result"]["probabilities"] = lstProbabilities;

  std::cout << oJsonReport << std::endl;
}
