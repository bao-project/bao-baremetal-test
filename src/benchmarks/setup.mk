#  Copyright (c) Bao Project and Contributors. All rights reserved  
#  SPDX-License-Identifier: Apache-2.0

ROOT_DIR:=$(realpath .)
NAME?=baremetal.bin
BENCHMARK?=ctx-switch
GUEST?=guest_1
BUILD_DIR:=$(ROOT_DIR)/build/$(NAME)

PLAT_DIR:=$(ROOT_DIR)/src/benchmarks/platform/$(PLATFORM)
include $(PLAT_DIR)/sources.mk
include $(PLAT_DIR)/plat.mk
C_SRC+=$(addprefix $(PLAT_DIR)/, $(src_c_srcs))
ASM_SRC+=$(addprefix $(PLAT_DIR)/, $(src_s_srcs))
INC_DIRS+=$(PLAT_DIR)/inc $(PLAT_DIR)/bsp/inc

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
