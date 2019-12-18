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
 scalar_t__ tolower (char const) ; 
 scalar_t__ toupper (char const) ; 

void generate_alpha_skip(const char *find, size_t f_len, size_t skip_lookup[], const int case_sensitive) {
    size_t i;

    for (i = 0; i < 256; i++) {
        skip_lookup[i] = f_len;
    }

    f_len--;

    for (i = 0; i < f_len; i++) {
        if (case_sensitive) {
            skip_lookup[(unsigned char)find[i]] = f_len - i;
        } else {
            skip_lookup[(unsigned char)tolower(find[i])] = f_len - i;
            skip_lookup[(unsigned char)toupper(find[i])] = f_len - i;
        }
    }
}