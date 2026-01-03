/*
 * SPDX-License-Identifier: AGPL-3.0-or-later
 * SPDX-FileCopyrightText: 2026 Shomy
 */

#include <search.h>

uintptr_t search_pattern(uintptr_t start, uintptr_t end, const uint32_t* pattern, uint32_t plen, const uint32_t* mask)
{
    for (uintptr_t addr = start; addr < end; addr += 4) {
        uint32_t *curr = (uint32_t *)addr;
        uint32_t i = 0;

        while (i < plen) {
            uint32_t val = curr[i];
            uint32_t pat = pattern[i];

            if (mask) {
                if ((val & mask[i]) != (pat & mask[i]))
                    break;
            } else {
                if (val != pat)
                    break;
            }
            i++;
        }
        if (i == plen)
            return addr;
    }
    return 0;
}
