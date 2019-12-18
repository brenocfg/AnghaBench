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
typedef  scalar_t__ INTN ;
typedef  scalar_t__ CHAR16 ;

/* Variables and functions */
 scalar_t__ StrCmp (scalar_t__*,scalar_t__*) ; 
 scalar_t__ c_order (scalar_t__) ; 
 scalar_t__ is_digit (scalar_t__) ; 

__attribute__((used)) static INTN str_verscmp(CHAR16 *s1, CHAR16 *s2) {
        CHAR16 *os1 = s1;
        CHAR16 *os2 = s2;

        while (*s1 || *s2) {
                INTN first;

                while ((*s1 && !is_digit(*s1)) || (*s2 && !is_digit(*s2))) {
                        INTN order;

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

        return StrCmp(os1, os2);
}