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
 int /*<<< orphan*/  NEWLINE ; 
 int /*<<< orphan*/  assert (char const*) ; 
 scalar_t__ isempty (char*) ; 
 char* mfree (char*) ; 
 size_t strv_length (char**) ; 
 char** strv_split (char const*,int /*<<< orphan*/ ) ; 

char **strv_split_newlines(const char *s) {
        char **l;
        size_t n;

        assert(s);

        /* Special version of strv_split() that splits on newlines and
         * suppresses an empty string at the end */

        l = strv_split(s, NEWLINE);
        if (!l)
                return NULL;

        n = strv_length(l);
        if (n <= 0)
                return l;

        if (isempty(l[n - 1]))
                l[n - 1] = mfree(l[n - 1]);

        return l;
}