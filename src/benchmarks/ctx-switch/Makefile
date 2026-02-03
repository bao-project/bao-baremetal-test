
all:
	make -C ctx-switch-guest1 bmrt_dir=$(bmrt_dir) PLATFORM=$(PLATFORM) \
		FLASH_BASE=0x10000 FLASH_SIZE=0x6000 \
		RAM_BASE=0xfe100000 RAM_SIZE=0x8000
	make -C ctx-switch-guest2 bmrt_dir=$(bmrt_dir) PLATFORM=$(PLATFORM) \
		FLASH_BASE=0x20000 FLASH_SIZE=0x6000 \
		RAM_BASE=0xfe108000 RAM_SIZE=0x8000

clean:
	make -C ctx-switch-guest1 bmrt_dir=$(bmrt_dir) PLATFORM=$(PLATFORM) \
		FLASH_BASE=0x10000 FLASH_SIZE=0x6000 \
		RAM_BASE=0xfe100000 RAM_SIZE=0x8000 \
		clean
	make -C ctx-switch-guest2 bmrt_dir=$(bmrt_dir) PLATFORM=$(PLATFORM) \
		FLASH_BASE=0x20000 FLASH_SIZE=0x6000 \
		RAM_BASE=0xfe108000 RAM_SIZE=0x8000 \
		clean
