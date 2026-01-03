/*
 * SPDX-License-Identifier: AGPL-3.0-or-later
 * SPDX-FileCopyrightText: 2026 Shomy
 */

#include <stdint.h>
#include <stddef.h>
#include <sej.h>
#include <protocol_functions.h>
#include <commands.h>

void register_commands(void) {
    const char *ver1 = "1";

    register_major_command(CMD_ACK, ver1, (HHANDLE)cmd_ack);
    register_major_command(CMD_READMEM, ver1, (HHANDLE)cmd_readmem);
    register_major_command(CMD_WRITEMEM, ver1, (HHANDLE)cmd_writemem);
    register_major_command(CMD_SEJ, ver1, (HHANDLE)cmd_sej_aes);
    register_major_command(CMD_SEJ_BASE, ver1, (HHANDLE)cmd_set_sej_base);
}

__attribute__ ((section(".text.main"))) int main(void) {
    uintptr_t start = 0x40000000;
    uintptr_t end = start + 0x80000; // 512 KB range
    if (find_functions(start, end)) {
        // We could not find the functions we need, so we quit.
        return 0;
    }

    // BANNER TIME!!!
    printf("\n");
    printf("*********************");
    printf("XML DA Extensions\n");
    printf("Copyright (c) 2026 Shomy\n");
    printf("SPDX-License-Identifier: AGPL-3.0-or-later\n\n");
    printf("!!! WARNING !!!\n");
    printf("THIS IS A FREE TOOL. IF YOU PAID FOR IT, YOU HAVE BEEN SCAMMED.\n");
    printf("THIS TOOL IS PROVIDED AS-IS WITHOUT WARRANTY OF ANY KIND.\n");
    printf("USE AT YOUR OWN RISK.\n");
    printf("*********************\n\n");

    printf("Initializing SEJ context...\n");
    init_sej_ctx();
    printf("SEJ context initialized.\n");

    printf("Registering commands...\n");
    register_commands();
    printf("Commands registered.\n");

    return 0;
}
