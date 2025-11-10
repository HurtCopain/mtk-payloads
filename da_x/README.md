## DA Extensions for V5/XFlash devices

This directory contains DA Extensions for V5/XFlash devices, allowing to define custom commands during DA2.

DA Extensions are originally developed by [B.Kerler](https://github.com/bkerler) for V5 devices, and later adapted for more cmds by [Shomy](https://github.com/shomykohai).

### Supported cmds

- `0xF0000` - CMD ACK, used to aknowledge wether da extensions got loaded
- `0xF0001` - CMD READMEM, used to read memory from device
- `0xF0002` - CMD READREG, used to read registers from device
- `0xF0003` - CMD WRITEMEM, used to write memory to device
- `0xF0004` - CMD WRITEREG, used to write registers to device
- `0xF0005` - CMD SETSTORAGE, used to set storage type (eMMC/UFS)
- `0xF0006` - CMD RPMB SETKEY, used to set RPMB key
- `0xF0008` - CMD RPMB INIT, used to init RPMB (depends on storage type, defaults to eMMC)
- `0xF0009` - CMD RPMB READ, used to read RPMB
- `0xF000A` - CMD RPMB WRITE, used to write RPMB
- `0xF000B` - CMD SEJ, used to interact with SEJ for performing cryptological operations (AES)

### Building

You'll need the arm-linux-gnueabihf toolchain to build the payload.

To build the payload, run:

```bash
make clean
make
```

### License
This payload is licensed under the *GPL-3.0* License, copyright (C) 2024 B.Kerler, 2025 Shomy.
See the [LICENSE](../LICENSE.gpl) file for details.

### Disclaimer
This payload is intended for educational purposes only. Use it at your own risk. The author is not responsible for any damage caused by using this payload.
