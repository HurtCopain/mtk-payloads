/*
 * SPDX-License-Identifier: AGPL-3.0-or-later
 * SPDX-FileCopyrightText: 2025 Shomy
 */

#include <stdint.h>
#include <stddef.h>

#define STATUS_OK 0x00000000

typedef struct com_channel_struct com_channel_struct;

struct com_channel_struct {
    int (*read)(uint8_t* buffer, uint32_t* length);
    int (*write)(uint8_t* buffer, uint32_t length);
    int (*log_to_pc)(const uint8_t* buffer, uint32_t length);
    int (*log_to_uart)(const uint8_t* buffer, uint32_t length);
};

int (*download)(struct com_channel_struct*, const char*, char**, uint32_t*, const char*) = (void*)0x40027720;

__attribute__((section(".text.start"))) int cmd_boot_to(struct com_channel_struct* channel, const char* xml) {
    int status = STATUS_OK;

    const char *source_file = "ext";
    uintptr_t ext_addr = 0x68000000;
    char *exts_buf = (char*)ext_addr;
    uint32_t len = 0x1000000;

    status = download(channel, source_file, &exts_buf, &len, "ext");
    if (status != STATUS_OK) {
        return status;
    }

    ((void(*)(void*))ext_addr)(&status);

    return status;
}
