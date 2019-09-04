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

/* Variables and functions */
 size_t ngx_strlen (char*) ; 
 scalar_t__ ngx_strncmp (scalar_t__*,scalar_t__*,size_t) ; 

u_char *
ngx_strnstr(u_char *s1, char *s2, size_t len)
{
    u_char  c1, c2;
    size_t  n;

    c2 = *(u_char *) s2++;

    n = ngx_strlen(s2);

    do {
        do {
            if (len-- == 0) {
                return NULL;
            }

            c1 = *s1++;

            if (c1 == 0) {
                return NULL;
            }

        } while (c1 != c2);

        if (n > len) {
            return NULL;
        }

    } while (ngx_strncmp(s1, (u_char *) s2, n) != 0);

    return --s1;
}