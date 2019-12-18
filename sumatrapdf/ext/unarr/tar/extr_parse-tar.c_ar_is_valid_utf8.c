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

__attribute__((used)) static bool ar_is_valid_utf8(const char *string)
{
    const unsigned char *s;
    for (s = (const unsigned char *)string; *s; s++) {
        int skip = *s < 0x80 ? 0 :
                   *s < 0xC0 ? -1 :
                   *s < 0xE0 ? 1 :
                   *s < 0xF0 ? 2 :
                   *s < 0xF5 ? 3 : -1;
        if (skip < 0)
            return false;
        while (skip-- > 0) {
            if ((*++s & 0xC0) != 0x80)
                return false;
        }
    }
    return true;
}