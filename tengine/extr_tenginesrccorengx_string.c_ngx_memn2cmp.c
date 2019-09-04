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
typedef  int /*<<< orphan*/  u_char ;
typedef  int ngx_int_t ;

/* Variables and functions */
 int ngx_memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

ngx_int_t
ngx_memn2cmp(u_char *s1, u_char *s2, size_t n1, size_t n2)
{
    size_t     n;
    ngx_int_t  m, z;

    if (n1 <= n2) {
        n = n1;
        z = -1;

    } else {
        n = n2;
        z = 1;
    }

    m = ngx_memcmp(s1, s2, n);

    if (m || n1 == n2) {
        return m;
    }

    return z;
}