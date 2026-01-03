/*
 * SPDX-License-Identifier: AGPL-3.0-or-later
 * SPDX-FileCopyrightText: 2026 Shomy
 */

#include <stddef.h>
#include <stdint.h>
#include <protocol_functions.h>
#include <arch/function_patterns.h>

void (*register_major_command)(const char *, const char *, HHANDLE) = (void*)NULL;
int (*download)(struct com_channel_struct*, const char*, char**, uint32_t*, const char*) = (void*)NULL;
int (*upload)(struct com_channel_struct*, const char*, const char*, uint32_t, const char*) = (void*)NULL;

void *(*malloc)(size_t size) = (const void*)NULL;
void (*free)(void *ptr) = (const void*)NULL;

char *(*mxmlGetNodeText)(void*, const char*) = (void*)NULL;
void *(*mxmlLoadString)(void*, const char*, void*) = (void*)NULL;

function_pattern_t entries[] = {
    FUNC_SINGLE(MALLOC, &malloc, "malloc"),
    FUNC_SINGLE(FREE, &free, "free"),
    FUNC_DUAL(REGISTER_MAJOR_COMMAND_V1, REGISTER_MAJOR_COMMAND_V2, &register_major_command, "register_major_command"),
    FUNC_DUAL(FP_READ_HOST_FILE_V1, FP_READ_HOST_FILE_V2, &download, "download"),
    FUNC_DUAL(FP_WRITE_HOST_FILE_V1, FP_WRITE_HOST_FILE_V2, &upload, "upload"),
    FUNC_SINGLE(MXML_GET_NODE_TEXT, &mxmlGetNodeText, "mxmlGetNodeText"),
    FUNC_SINGLE(MXML_LOAD_STRING, &mxmlLoadString, "mxmlLoadString"),
};

/*
 * Finds and assigns function pointers based on predefined patterns.
 * Returns true on failure, false on success.
 */
 bool find_functions(uintptr_t start, uintptr_t end) {
     size_t num_entries = sizeof(entries) / sizeof(entries[0]);
     for (size_t i = 0; i < num_entries; i++) {
         function_pattern_t *entry = &entries[i];
         uintptr_t addr = 0;

         for (size_t v = 0; v < entry->num_variants; v++) {
             pattern_variant_t *var = &entry->variants[v];
             addr = search_pattern(start, end, var->pattern, (uint32_t)var->pattern_len, var->mask);
             if (addr != 0) {
                 break;
             }
         }
         if (addr == 0) {
             printf("Failed to find function:  %s\n", entry->func_name);
             return true;
         }
         *(entry->func_ptr) = (void *)addr;
         printf("Found function %s at address:  0x%lx\n", entry->func_name, addr);
     }
     return false;
 }
