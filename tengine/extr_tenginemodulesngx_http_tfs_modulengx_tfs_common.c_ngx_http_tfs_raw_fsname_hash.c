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
typedef  scalar_t__ int32_t ;

/* Variables and functions */

int32_t
ngx_http_tfs_raw_fsname_hash(const u_char *str, const int32_t len)
{
    int32_t  h, i;

    h = 0;

    if (str == NULL || len <=0) {
        return 0;
    }

    for (i = 0; i < len; ++i) {
        h += str[i];
        h *= 7;
    }

    return (h | 0x80000000);
}