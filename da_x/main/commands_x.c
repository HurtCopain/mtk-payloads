// Copyright 2024 (c) B.Kerler
// Copyright 2025 (c) Shomy
// Use of this source code is governed by a GPLv3 license, see LICENSE.txt.

#include <common/com.h>
#include <common/da.h>

static uint32_t storage=STORAGE_EMMC;
da_ctx_t g_da_ctx;

/* -------------------------------- Commands --------------------------------------- */

int cmd_readmem(com_channel_struct *channel){
    volatile uint64_t addr=0;
    uint8_t buffer[0x20000]={0};
    uint32_t length=0;
    uint32_t cmdlen=8;
    channel->read((uint8_t*)&addr,&cmdlen);
    cmdlen=4;
    channel->read((uint8_t*)&length,&cmdlen);
    if (length>0x20000) length=0x20000;
    memcpy(buffer,(volatile uint64_t*)addr,length);
    channel->write((uint8_t *)buffer,length);
    return 0;
}

int cmd_readregister(com_channel_struct *channel){
    int status = 0;
    volatile uint32_t addr=0;
    volatile uint32_t dword=0;
    uint32_t cmdlen=4;
    channel->read((uint8_t*)&addr,&cmdlen);
    channel->write((uint8_t*)&status, 4);

    cmdlen=4;
    dword=WRAP_RD32(addr);
    //dword=*(volatile uint32_t*)addr;
    channel->write((uint8_t *)&dword,cmdlen);
    return 0;
}

int cmd_writemem(com_channel_struct *channel){
    volatile uint64_t addr=0;
    uint32_t length=0;
    uint32_t cmdlen=8;
    channel->read((uint8_t*)&addr,&cmdlen);
    cmdlen=4;
    channel->read((uint8_t*)&length,&cmdlen);
    return channel->read((uint8_t *)addr,&length);
}

int cmd_writeregister(com_channel_struct *channel){
    volatile uint32_t addr=0;
    volatile uint32_t dword=0;
    uint32_t cmdlen=4;
    channel->read((uint8_t*)&addr,&cmdlen);
    cmdlen=4;
    channel->read((uint8_t*)&dword,&cmdlen);
    WRAP_WR32(addr,dword);
    //*(volatile uint32_t*)addr=dword;
    return 0;
}

int cmd_ack(com_channel_struct *channel){
    uint32_t ack=0xA1A2A3A4;
    return channel->write((uint8_t *)&ack,4);
}

int cmd_rpmb_read(com_channel_struct *channel)
{
    uint32_t size = 4;
    uint32_t address = 0;
    uint32_t sectors = 0;
    channel->read((uint8_t*)&address, &size);
    size=4;
    channel->read((uint8_t*)&sectors, &size);
    uint8_t data[0x100]={0};
    int res = -1;
    for (uint32_t cursector=address;cursector<address+sectors;cursector++){
        if (storage==STORAGE_UFS) {
            res = ufs_read_frame(cursector,data);
        }
        else if (storage==STORAGE_EMMC) {
            res = mmc_read_frame(cursector,data);
        }
        if (res) {
            channel->write((uint8_t *)&res, 2);
            break;
        }
        else {
            channel->write((uint8_t *)data, 0x100);
        }
    }
    return res;
}

int cmd_rpmb_write(com_channel_struct *channel, const char* /*xml*/)
{
    uint32_t size = 4;
    uint32_t address = 0;
    uint32_t sectors = 0;
    uint8_t data[0x100]={0};
    channel->read((uint8_t*)&address, &size);
    size=4;
    channel->read((uint8_t*)&sectors, &size);
    int res = -1;
    size = 0x100;
    for (uint32_t cursector=address;cursector<address+sectors;cursector++) {
        channel->read(data, &size);
        if (storage == STORAGE_UFS) {
            res = ufs_write_frame(cursector, data);
        } else if (storage == STORAGE_EMMC) {
            res = mmc_write_frame(cursector, data);
        }
        channel->write((uint8_t*)&res, 2);
        if (res) {
            break;
        }
    }
    return 0;
}

int cmd_rpmb_init(com_channel_struct *channel)
{
  int res = -1;
  if (storage==STORAGE_UFS){
      res=ufs_init();
  } else if (storage==STORAGE_EMMC) {
      res=mmc_init();
  }
  channel->write((uint8_t*)&res, 2);
  if (!res) {
      channel->write((uint8_t*)get_current_rpmb_key(),0x20);
  }
  return 0;
}

int cmd_rpmb_set_key(com_channel_struct *channel)
{
  uint32_t size = 0x20;
  uint8_t rpmbkey[0x20];
  channel->read((uint8_t*)rpmbkey, &size);
  set_current_rpmb_key(rpmbkey);
  channel->write(get_current_rpmb_key(),0x20);
  return 0;
}

int cmd_set_storage(com_channel_struct *channel)
{
    uint32_t size = 0x4;
    channel->read((uint8_t*)&storage, &size);
    return 0;
}

int cmd_sej_aes(com_channel_struct *channel)
{
    /*
     * Format:
     * 0100010020000000
     * Byte 0: Encrypt (1) / Decrypt (0)
     * Byte 1: Legacy SEJ (1) / Non-Legacy SEJ (0)
     * Byte 2: Anti-clone enable (1) / disable (0)
     * Byte 3: Reserved
     * Bytes 4-7: Data length (little-endian)
     *
     */
    #define AES_MAX_LEN 128
    int status = 0;
    uint8_t params[8] = {0};
    bool encrypt = false;
    bool legacy = false;
    bool anti_clone = true;

    static uint8_t data_in[AES_MAX_LEN];
    static uint8_t data_out[AES_MAX_LEN];

    uint32_t param_len = sizeof(params);
    channel->read(params, &param_len);

    encrypt = params[0];
    legacy  = params[1];
    anti_clone = params[2];
    uint32_t length = *(uint32_t*)&params[4];

    if (length > AES_MAX_LEN) {
        status = 0xc0010004;
        return status;
    }

    channel->read(data_in, &length);
    channel->write((uint8_t*)&status, 4);

    if (encrypt)
        sp_sej_enc(data_in, data_out, length, anti_clone, legacy);
    else
        sp_sej_dec(data_in, data_out, length, anti_clone, legacy);

    channel->write(data_out, length);

    return status;
}

int cmd_setup_da_ctx(com_channel_struct *channel)
{
    uint32_t size = 4;
    channel->read((uint8_t*)&g_da_ctx.da2_addr, &size);
    size = 4;
    channel->read((uint8_t*)&g_da_ctx.da2_size, &size);
    return 0;
}
