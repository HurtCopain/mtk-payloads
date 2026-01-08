## DA Extensions for V6/XML devices

This directory contains DA Extensions for V6/XML  devices, allowing to define custom commands during DA2.

### Supported cmds

- `CMD:EXT-ACK` - used to aknowledge whether da extensions got loaded or not
- `CMD:EXT-SEJ` - used to interact with SEJ for performing cryptological operations (AES)
- `CMD:EXT-SET-SEJ-BASE` - used to set the SEJ base address, which may vary between devices
- `CMD:EXT-READ-MEM` - used to read memory from device
- `CMD:EXT-WRITE-MEM` - used to write memory to device

### Building

You'll need the arm-none-eabi toolchain and aarch64-none-linux-gnu to build the payload.

To build the payload, run:

```bash
make clean
make
make ARCH=aarch64 CROSS_COMPILE=aarch64-none-linux-gnu-
```

### License
This payload is licensed under the *AGPL-3.0-or-later* License, copyright (C) 2026 Shomy.
See the [LICENSE](../LICENSE.agpl) file for details.

Additionally, this payload makes use of: 
* [libsej](../libsej), which is licensed under the *GPL-3.0* License, copyright (C) 2024 B.Kerler, 2025 Shomy.
* [nanoprintf](lib/nanoprintf.h), dual-licensed under the *Unlicense* and the *Zero-Clause BSD (0BSD)* licenses, copyright (C) 2019 Charles Nicholson. Original source [here](https://github.com/charlesnicholson/nanoprintf)
* [libc](src/libc.c), of which some functions are derived from the work of musl libc. Copyright (c) 2005-2018 Rich Felker.

### Disclaimer
This payload is intended for educational purposes only. Use it at your own risk. The author is not responsible for any damage caused by using this payload.
