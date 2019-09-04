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

size_t suffix_len(const char *s, const size_t s_len, const size_t pos, const int case_sensitive) {
    size_t i;

    for (i = 0; i < pos; i++) {
        if (case_sensitive) {
            if (s[pos - i] != s[s_len - i - 1]) {
                break;
            }
        } else {
            if (tolower(s[pos - i]) != tolower(s[s_len - i - 1])) {
                break;
            }
        }
    }

    return i;
}