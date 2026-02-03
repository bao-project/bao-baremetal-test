# SPDX-License-Identifier: GPL-2.0
# Copyright (c) Bao Project and Contributors. All rights reserved.

# Prepare enviroment for baremetal-runtime
NAME:=baremetal
ROOT_DIR:=$(realpath .)
BUILD_DIR:=$(ROOT_DIR)/build/$(PLATFORM)

bmrt_dir:=$(ROOT_DIR)/src/baremetal-runtime
include $(bmrt_dir)/setup.mk

bmt_dir:=$(ROOT_DIR)/src/tests
bmb_dir:=$(ROOT_DIR)/src/benchmarks

ifneq ($(BAREMETAL_TESTS),)
	app_src_dir:=$(bmt_dir)
	include $(app_src_dir)/sources.mk
	C_SRC+=$(addprefix $(app_src_dir)/, $(src_c_srcs))
include $(bmt_dir)/setup.mk

else ifneq ($(BAREMETAL_BENCHMARKS),)
	app_src_dir:=$(bmb_dir)
	include $(app_src_dir)/sources.mk
	C_SRC+=$(addprefix $(app_src_dir)/, $(src_c_srcs))
include $(bmb_dir)/setup.mk
endif

include $(bmrt_dir)/build.mk