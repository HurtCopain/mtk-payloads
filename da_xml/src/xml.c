/*
 * SPDX-License-Identifier: AGPL-3.0-or-later
 * SPDX-FileCopyrightText: 2026 Shomy
 */

#include <stdarg.h>
#include <protocol_functions.h>

bool mxmlCheckNodes(void* tree, ...) {
    va_list args;
    const char *name;
    va_start(args, tree);
    while ((name = va_arg(args, const char *))) {
        if (!mxmlGetNodeText(tree, name)) {
            va_end(args);
            return false;
        }
    }
    va_end(args);
    return true;
}
