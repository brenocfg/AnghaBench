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
typedef  scalar_t__ u_char ;
typedef  scalar_t__ ngx_int_t ;

/* Variables and functions */

ngx_int_t
ngx_rstrncmp(u_char *s1, u_char *s2, size_t n)
{
    if (n == 0) {
        return 0;
    }

    n--;

    for ( ;; ) {
        if (s1[n] != s2[n]) {
            return s1[n] - s2[n];
        }

        if (n == 0) {
            return 0;
        }

        n--;
    }
}