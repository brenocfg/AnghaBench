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
 int utf8_encoded_valid_unichar (char const*,size_t) ; 

size_t utf8_n_codepoints(const char *str) {
        size_t n = 0;

        /* Returns the number of UTF-8 codepoints in this string, or (size_t) -1 if the string is not valid UTF-8. */

        while (*str != 0) {
                int k;

                k = utf8_encoded_valid_unichar(str, (size_t) -1);
                if (k < 0)
                        return (size_t) -1;

                str += k;
                n++;
        }

        return n;
}