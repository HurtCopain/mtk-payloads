/*
 * SPDX-License-Identifier: AGPL-3.0-or-later
 * SPDX-FileCopyrightText: 2026 Shomy
 */

#include <stdarg.h>
#include <debug.h>
#include <drivers/uart.h>

#define NANOPRINTF_IMPLEMENTATION
#define NANOPRINTF_USE_FIELD_WIDTH_FORMAT_SPECIFIERS 1
#define NANOPRINTF_USE_PRECISION_FORMAT_SPECIFIERS 1
#define NANOPRINTF_USE_FLOAT_FORMAT_SPECIFIERS 0
#define NANOPRINTF_USE_SMALL_FORMAT_SPECIFIERS 1
#define NANOPRINTF_USE_LARGE_FORMAT_SPECIFIERS 0 // Add back for arm64
#define NANOPRINTF_USE_BINARY_FORMAT_SPECIFIERS 0
#define NANOPRINTF_USE_WRITEBACK_FORMAT_SPECIFIERS 0
#define NANOPRINTF_USE_ALT_FORM_FLAG 0

#include <nanoprintf.h>

void uart_putc(int ch, void* /* ctx */) {
    if (ch == '\n')
        mtk_uart_putc('\r');
    mtk_uart_putc(ch);
}

int printf(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    int ret = npf_vpprintf(&uart_putc, NULL, fmt, args);

    va_end(args);
    return ret;
}
