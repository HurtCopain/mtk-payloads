/*
 * SPDX-License-Identifier: AGPL-3.0-or-later
 * SPDX-FileCopyrightText: 2026 Shomy
 */

#ifndef DA_XML_SEARCH_H
#define DA_XML_SEARCH_H

#include <stdint.h>

uintptr_t search_pattern(uintptr_t start, uintptr_t end, const uint32_t* pattern, uint32_t plen, const uint32_t* mask);

#endif //DA_XML_SEARCH_H
