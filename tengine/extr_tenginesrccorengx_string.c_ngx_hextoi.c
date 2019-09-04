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
typedef  char u_char ;
typedef  int ngx_int_t ;

/* Variables and functions */
 int NGX_ERROR ; 
 int NGX_MAX_INT_T_VALUE ; 

ngx_int_t
ngx_hextoi(u_char *line, size_t n)
{
    u_char     c, ch;
    ngx_int_t  value, cutoff;

    if (n == 0) {
        return NGX_ERROR;
    }

    cutoff = NGX_MAX_INT_T_VALUE / 16;

    for (value = 0; n--; line++) {
        if (value > cutoff) {
            return NGX_ERROR;
        }

        ch = *line;

        if (ch >= '0' && ch <= '9') {
            value = value * 16 + (ch - '0');
            continue;
        }

        c = (u_char) (ch | 0x20);

        if (c >= 'a' && c <= 'f') {
            value = value * 16 + (c - 'a' + 10);
            continue;
        }

        return NGX_ERROR;
    }

    return value;
}