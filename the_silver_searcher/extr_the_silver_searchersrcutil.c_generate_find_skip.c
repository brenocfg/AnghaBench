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
 size_t* ag_malloc (size_t const) ; 
 scalar_t__ is_prefix (char const*,size_t const,size_t,int const) ; 
 size_t suffix_len (char const*,size_t const,size_t,int const) ; 

void generate_find_skip(const char *find, const size_t f_len, size_t **skip_lookup, const int case_sensitive) {
    size_t i;
    size_t s_len;
    size_t *sl = ag_malloc(f_len * sizeof(size_t));
    *skip_lookup = sl;
    size_t last_prefix = f_len;

    for (i = last_prefix; i > 0; i--) {
        if (is_prefix(find, f_len, i, case_sensitive)) {
            last_prefix = i;
        }
        sl[i - 1] = last_prefix + (f_len - i);
    }

    for (i = 0; i < f_len; i++) {
        s_len = suffix_len(find, f_len, i, case_sensitive);
        if (find[i - s_len] != find[f_len - 1 - s_len]) {
            sl[f_len - 1 - s_len] = f_len - 1 - i + s_len;
        }
    }
}