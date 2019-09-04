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
typedef  int /*<<< orphan*/  ngx_int_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 unsigned int ULLONG_MAX ; 

ngx_int_t
ngx_http_tfs_atoull(u_char *line, size_t n, unsigned long long *value)
{
    unsigned long long res;

    for (res = 0; n--; line++) {
        unsigned int val;

        if (*line < '0' || *line > '9') {
            return NGX_ERROR;
        }

        val = *line - '0';

        /*
         * Check for overflow
         */

        if (res & (~0ull << 60)) {

            if (res > ((ULLONG_MAX - val) / 10)) {
                return NGX_ERROR;
            }
        }

        res = res * 10 + val;
    }

    *value = res;

    return NGX_OK;
}