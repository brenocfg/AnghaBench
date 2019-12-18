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
 int /*<<< orphan*/  GREEDY_REALLOC (char*,size_t,size_t) ; 
 int /*<<< orphan*/  assert (char const*) ; 
 char* mfree (char*) ; 
 int /*<<< orphan*/  startswith (char const*,char const*) ; 
 char* stpcpy (char*,char const*) ; 
 size_t strlen (char const*) ; 

char *strreplace(const char *text, const char *old_string, const char *new_string) {
        size_t l, old_len, new_len, allocated = 0;
        char *t, *ret = NULL;
        const char *f;

        assert(old_string);
        assert(new_string);

        if (!text)
                return NULL;

        old_len = strlen(old_string);
        new_len = strlen(new_string);

        l = strlen(text);
        if (!GREEDY_REALLOC(ret, allocated, l+1))
                return NULL;

        f = text;
        t = ret;
        while (*f) {
                size_t d, nl;

                if (!startswith(f, old_string)) {
                        *(t++) = *(f++);
                        continue;
                }

                d = t - ret;
                nl = l - old_len + new_len;

                if (!GREEDY_REALLOC(ret, allocated, nl + 1))
                        return mfree(ret);

                l = nl;
                t = ret + d;

                t = stpcpy(t, new_string);
                f += old_len;
        }

        *t = 0;
        return ret;
}