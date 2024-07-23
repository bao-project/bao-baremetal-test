# SPDX-License-Identifier: GPL-2.0
# Copyright (c) Bao Project and Contributors. All rights reserved.

# Prepare enviroment for baremetal-runtime
NAME:=baremetal
ROOT_DIR:=$(realpath .)
BUILD_DIR:=$(ROOT_DIR)/build/$(PLATFORM)

bmrt_dir:=$(ROOT_DIR)/src/baremetal-runtime
include $(bmrt_dir)/setup.mk


bmg_dir:=$(ROOT_DIR)/src/baremetal-app
app_src_dir:=$(bmg_dir)
include $(app_src_dir)/sources.mk
C_SRC+=$(addprefix $(app_src_dir)/, $(src_c_srcs))
include $(bmg_dir)/setup.mk

# Include the final baremetal-runtime build
include $(bmrt_dir)/build.mk