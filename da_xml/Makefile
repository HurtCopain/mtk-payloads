ARCH ?= arm

ifeq ($(ARCH),aarch64)
    CROSS_COMPILE := aarch64-none-linux-gnu-
    ARCH_DIR      := arm64
    ARCH_DEFINE   := -DAARCH64
    TARGET_NAME   := da_xml_arm64
else
    CROSS_COMPILE := arm-none-eabi-
    ARCH_DIR      := arm
    ARCH_DEFINE   := -DARM
    TARGET_NAME   := da_xml_arm
endif

CC      := $(CROSS_COMPILE)gcc
OBJCOPY := $(CROSS_COMPILE)objcopy
SIZE    := $(CROSS_COMPILE)size

SRC_DIR     := src
INC_DIR     := include
LIB_DIR     := lib
LIBSEJ_DIR  := ../libsej
OUTPUT_DIR  := ../payloads
BUILD_DIR   := build/$(ARCH)

TARGET_ELF  := $(BUILD_DIR)/$(TARGET_NAME).elf
TARGET_BIN  := $(OUTPUT_DIR)/$(TARGET_NAME).bin
LINKER_SCR  := src/arch/$(ARCH_DIR)/generic.ld

C_SOURCES   := $(shell find main -name '*.c') \
               $(shell find src -name '*.c') \
               $(wildcard $(LIBSEJ_DIR)/src/*.c)

# Remove ../ from paths to keep objects inside build directory
OBJECTS     := $(C_SOURCES:../%=%)
OBJECTS     := $(OBJECTS:%.c=$(BUILD_DIR)/%.o)

CFLAGS      := -std=gnu99 -Os -Wall -Wextra
CFLAGS      += -fno-strict-aliasing -fno-builtin
CFLAGS      += -fno-omit-frame-pointer -fno-pic -fno-pie
CFLAGS      += -I$(INC_DIR) -I$(LIB_DIR) -I$(LIBSEJ_DIR)/include
CFLAGS      += $(ARCH_DEFINE)

LDFLAGS     := -nodefaultlibs -nostdlib -Wl,--build-id=none,--no-warn-rwx-segments
LDFLAGS     += -T$(LINKER_SCR) -L$(BUILD_DIR)

ifeq ($(ARCH),aarch64)
    CFLAGS  += -march=armv8-a -mgeneral-regs-only -mno-outline-atomics
else
    CFLAGS  += -marm -mcpu=cortex-a9 -mno-unaligned-access
endif

all: $(TARGET_BIN)

$(TARGET_BIN): $(TARGET_ELF)
	@mkdir -p $(dir $@)
	$(OBJCOPY) -O binary $< $@
	@echo "Built: $@"

$(TARGET_ELF): $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
	$(SIZE) $@

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/libsej/%.o: $(LIBSEJ_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build
	rm -f $(TARGET_BIN)

.PHONY: all clean
