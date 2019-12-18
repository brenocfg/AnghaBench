#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int UnitWriteFlags ;

/* Variables and functions */
 int UNIT_ESCAPE_C ; 
 int UNIT_ESCAPE_SPECIFIERS ; 
 char* cescape (char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* specifier_escape (char const*) ; 
 char* strdup (char const*) ; 

char* unit_escape_setting(const char *s, UnitWriteFlags flags, char **buf) {
        char *ret = NULL;

        if (!s)
                return NULL;

        /* Escapes the input string as requested. Returns the escaped string. If 'buf' is specified then the allocated
         * return buffer pointer is also written to *buf, except if no escaping was necessary, in which case *buf is
         * set to NULL, and the input pointer is returned as-is. This means the return value always contains a properly
         * escaped version, but *buf when passed only contains a pointer if an allocation was necessary. If *buf is
         * not specified, then the return value always needs to be freed. Callers can use this to optimize memory
         * allocations. */

        if (flags & UNIT_ESCAPE_SPECIFIERS) {
                ret = specifier_escape(s);
                if (!ret)
                        return NULL;

                s = ret;
        }

        if (flags & UNIT_ESCAPE_C) {
                char *a;

                a = cescape(s);
                free(ret);
                if (!a)
                        return NULL;

                ret = a;
        }

        if (buf) {
                *buf = ret;
                return ret ?: (char*) s;
        }

        return ret ?: strdup(s);
}