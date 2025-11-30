// Copyright 2024 (c) B.Kerler
// Use of this source code is governed by a GPLv3 license, see LICENSE.txt.

#include <stdint.h>
#include <sej.h>
#include <common/defs.h>
#include <libc/libc.h>
#include <common/flash_handler.h>
#include <common/com.h>
#include <string.h>
#include "commands_x.c"

typedef int (*HHANDLE)(com_channel_struct*);
extern void apmcu_dcache_clean_invalidate();
extern void apmcu_dcache_invalidate();
extern int cache_init(int param);
extern int cache_close(int param);

int (*register_major_command)(uint32_t /*ctrl_code*/, HHANDLE /*handle*/)=(const void*)0x11111111;
uint32_t efuse_addr=0x88888888;


__attribute__ ((section(".text.main"))) int main() {
    cache_init(3);
    init_sej_ctx();

    register_major_command(0xF0000,(void*)cmd_ack);
    register_major_command(0xF0001,(void*)cmd_readmem);
    register_major_command(0xF0002,(void*)cmd_readregister);
    register_major_command(0xF0003,(void*)cmd_writemem);
    register_major_command(0xF0004,(void*)cmd_writeregister);
    register_major_command(0xF0005,(void*)cmd_set_storage);
    register_major_command(0xF0006,(void*)cmd_rpmb_set_key);
    register_major_command(0xF0008,(void*)cmd_rpmb_init);
    register_major_command(0xF0009,(void*)cmd_rpmb_read);
    register_major_command(0xF000A,(void*)cmd_rpmb_write);
    register_major_command(0xF000B,(void*)cmd_sej_aes);
    register_major_command(0xF000C,(void*)cmd_setup_da_ctx);
    cache_close(1);
    return 0;
}
