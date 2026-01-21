CFLAGS += -fno-pic -fno-plt -fno-stack-protector -fno-stack-check -ffreestanding
CROSS_COMPILE_LINUX ?= arm-none-linux-gnueabihf-

CC      := $(CROSS_COMPILE_LINUX)gcc
OBJCOPY := $(CROSS_COMPILE_LINUX)objcopy
SIZE    := $(CROSS_COMPILE_LINUX)size
ASM     := $(CC)

SRC_DIR := src
BUILD_DIR := build
OUTPUT_DIR := ../payloads
INCLUDE_DIR := include
LIBSEJ_DIR := ../libsej
LIBSEJ_SRC := $(wildcard $(LIBSEJ_DIR)/src/*.c)
LIBSEJ_INC := $(LIBSEJ_DIR)/include

C_SOURCES := $(shell find $(SRC_DIR) -name '*.c') main/da_x.c $(LIBSEJ_SRC)
ASM_SOURCES := $(shell find $(SRC_DIR) -name '*.S') main/start.S

# Output
TARGET_ELF := $(BUILD_DIR)/da_x.elf
TARGET_BIN := $(OUTPUT_DIR)/da_x.bin

# Flags
CFLAGS := -fno-pic -fno-plt -fno-stack-protector -static  -fno-plt  -fno-stack-protector -fno-stack-check -U_FORTIFY_SOURCE  -std=gnu99 -Os -mthumb -mcpu=cortex-a9 -fno-builtin-printf \
          -fno-strict-aliasing -fno-builtin-memcpy -fno-stack-protector \
          -fPIE -Wall -Wextra -z noexecstack -DV5 \
          -I$(INCLUDE_DIR) \
          -fno-stack-protector -U_FORTIFY_SOURCE

CFLAGS += -I../libsej/include

ASMFLAGS := $(CFLAGS)
LDFLAGS := -nodefaultlibs -nostdlib -Wl,--build-id=none -Tmain/generic.ld -L$(BUILD_DIR)

OBJECTS := $(patsubst %.c,$(BUILD_DIR)/%.o,$(C_SOURCES)) \
           $(patsubst %.S,$(BUILD_DIR)/%.o,$(ASM_SOURCES))

all: $(TARGET_BIN)

$(TARGET_ELF): $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)
	$(SIZE) $@

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.S
	@mkdir -p $(dir $@)
	$(ASM) $(ASMFLAGS) -c $< -o $@

$(TARGET_BIN): $(TARGET_ELF)
	@mkdir -p $(dir $@)
	$(OBJCOPY) -O binary $< $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET_BIN)
	rm -rf libsej
	find . -name '*.o' -delete

.PHONY: all clean
