#  Copyright (c) Bao Project and Contributors. All rights reserved  
#  SPDX-License-Identifier: Apache-2.0

ROOT_DIR:=$(realpath .)
NAME?=baremetal.bin
BENCHMARK?=ctx-switch
GUEST?=guest_1
BUILD_DIR:=$(ROOT_DIR)/build/$(NAME)

ifeq ($(BENCHMARK),ctx-switch)
APP_SRC_DIR=$(ROOT_DIR)/src/benchmarks/ctx-switch/$(GUEST)
include $(APP_SRC_DIR)/sources.mk
C_SRC+=$(addprefix $(APP_SRC_DIR)/, $(src_c_srcs))
endif

ifeq ($(BENCHMARK),irq-lat)
APP_SRC_DIR=$(ROOT_DIR)/src/benchmarks/irq-lat/$(GUEST)
include $(APP_SRC_DIR)/sources.mk
C_SRC+=$(addprefix $(APP_SRC_DIR)/, $(src_c_srcs))
endif

ifeq ($(BENCHMARK),irq-lat-wce)
APP_SRC_DIR=$(ROOT_DIR)/src/benchmarks/irq-lat-wce/$(GUEST)
include $(APP_SRC_DIR)/sources.mk
C_SRC+=$(addprefix $(APP_SRC_DIR)/, $(src_c_srcs))
endif

include $(ROOT_DIR)/src/benchmarks/sources.mk
