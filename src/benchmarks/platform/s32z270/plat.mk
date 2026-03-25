PLAT_FREQ:= 40000000

CPPFLAGS += -DPLAT_GENERIC_TIMER_FIXED_FREQ=$(PLAT_FREQ)
SINGLE_CORE=y

C_SRC+=$(addprefix $(PLAT_DIR)/, $(src_c_srcs))
ASM_SRC+=$(addprefix $(PLAT_DIR)/, $(src_s_srcs))
INC_DIRS+=$(PLAT_DIR)/inc $(PLAT_DIR)/bsp/inc