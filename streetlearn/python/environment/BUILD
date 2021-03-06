# Streetlearn BUILD file.
#
# Copyright 2018 Google LLC.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

package(default_visibility = ["//visibility:public"])

licenses(["notice"])  # Apache v2

exports_files(["LICENSE"])

py_library(
    name = "environment_py",
    srcs = [
        "batched_streetlearn.py",
        "coin_game.py",
        "courier_game.py",
        "curriculum_courier_game.py",
        "default_config.py",
        "exploration_game.py",
        "game.py",
        "goal_instruction_game.py",
        "incremental_instruction_game.py",
        "instructions_base.py",
        "instructions_curriculum.py",
        "instructions_densification.py",
        "observations.py",
        "step_by_step_instruction_game.py",
        "streetlearn.py",
        "thumbnail_helper.py",
    ],
    srcs_version = "PY2AND3",
    deps = [
        "//streetlearn/engine/python:color",
        "//streetlearn/engine/python:streetlearn_engine",
        "//streetlearn/proto:streetlearn_py_pb2",
    ],
)
