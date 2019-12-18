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
 char* VALID_CHARS_GLOB ; 
 char* VALID_CHARS_WITH_AT ; 
 int /*<<< orphan*/  assert (char const*) ; 
 char* do_escape_char (char const,char*) ; 
 int /*<<< orphan*/  strchr (char const*,char const) ; 

__attribute__((used)) static bool do_escape_mangle(const char *f, bool allow_globs, char *t) {
        const char *valid_chars;
        bool mangled = false;

        assert(f);
        assert(t);

        /* We'll only escape the obvious characters here, to play safe.
         *
         * Returns true if any characters were mangled, false otherwise.
         */

        valid_chars = allow_globs ? VALID_CHARS_GLOB : VALID_CHARS_WITH_AT;

        for (; *f; f++)
                if (*f == '/') {
                        *(t++) = '-';
                        mangled = true;
                } else if (!strchr(valid_chars, *f)) {
                        t = do_escape_char(*f, t);
                        mangled = true;
                } else
                        *(t++) = *f;
        *t = 0;

        return mangled;
}