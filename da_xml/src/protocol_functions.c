/*
 * SPDX-License-Identifier: AGPL-3.0-or-later
 * SPDX-FileCopyrightText: 2026 Shomy
 */

#include <stddef.h>
#include <stdint.h>
#include <protocol_functions.h>

void (*register_major_command)(const char *, const char *, HHANDLE) = (const void*)0x22222222;
int (*download)(struct com_channel_struct*, const char*, char**, uint32_t*, const char*) = (const void*)0x33333333;
int (*upload)(struct com_channel_struct*, const char*, const char*, uint32_t, const char*) = (const void*)0x44444444;

void *(*malloc)(size_t size) = (const void*)0x55555555;
void (*free)(void *ptr) = (const void*)0x66666666;

char *(*mxmlGetNodeText)(void*, const char*) = (void*)0x77777777;
void *(*mxmlLoadString)(void*, const char*, void*) = (void*)0x88888888;
