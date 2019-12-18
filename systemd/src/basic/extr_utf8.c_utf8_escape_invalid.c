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

/* Variables and functions */
 int /*<<< orphan*/  UTF8_REPLACEMENT_CHARACTER ; 
 int /*<<< orphan*/  assert (char const*) ; 
 char* malloc (int) ; 
 char* mempcpy (char*,char const*,int) ; 
 char* stpcpy (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  str_realloc (char**) ; 
 int strlen (char const*) ; 
 int utf8_encoded_valid_unichar (char const*,size_t) ; 

char *utf8_escape_invalid(const char *str) {
        char *p, *s;

        assert(str);

        p = s = malloc(strlen(str) * 4 + 1);
        if (!p)
                return NULL;

        while (*str) {
                int len;

                len = utf8_encoded_valid_unichar(str, (size_t) -1);
                if (len > 0) {
                        s = mempcpy(s, str, len);
                        str += len;
                } else {
                        s = stpcpy(s, UTF8_REPLACEMENT_CHARACTER);
                        str += 1;
                }
        }

        *s = '\0';
        (void) str_realloc(&p);
        return p;
}