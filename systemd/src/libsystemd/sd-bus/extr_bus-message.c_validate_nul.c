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
 scalar_t__ memchr (char const*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static bool validate_nul(const char *s, size_t l) {

        /* Check for NUL chars in the string */
        if (memchr(s, 0, l))
                return false;

        /* Check for NUL termination */
        if (s[l] != 0)
                return false;

        return true;
}