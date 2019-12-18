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
 int /*<<< orphan*/  assert (char const*) ; 
 int c_order (char const) ; 
 scalar_t__ is_digit (char const) ; 
 int strcmp (char const*,char const*) ; 

int str_verscmp(const char *s1, const char *s2) {
        const char *os1, *os2;

        assert(s1);
        assert(s2);

        os1 = s1;
        os2 = s2;

        while (*s1 || *s2) {
                int first;

                while ((*s1 && !is_digit(*s1)) || (*s2 && !is_digit(*s2))) {
                        int order;

                        order = c_order(*s1) - c_order(*s2);
                        if (order != 0)
                                return order;
                        s1++;
                        s2++;
                }

                while (*s1 == '0')
                        s1++;
                while (*s2 == '0')
                        s2++;

                first = 0;
                while (is_digit(*s1) && is_digit(*s2)) {
                        if (first == 0)
                                first = *s1 - *s2;
                        s1++;
                        s2++;
                }

                if (is_digit(*s1))
                        return 1;
                if (is_digit(*s2))
                        return -1;

                if (first != 0)
                        return first;
        }

        return strcmp(os1, os2);
}