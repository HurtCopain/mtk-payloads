/*
 * SPDX-License-Identifier: AGPL-3.0-or-later
 * SPDX-FileCopyrightText: 2026 Shomy
 */

#ifndef DA_XML_UART_H
#define DA_XML_UART_H

#define DEFAULT_UART_BASE 0x11002000

#define UART_THR_OFFSET     0x00
#define UART_LSR_OFFSET     0x14
#define UART_LSR_THRE       0x20

void mtk_uart_putc(int ch);

#endif //DA_XML_UART_H
