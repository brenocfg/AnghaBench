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
typedef  int uint64_t ;

/* Variables and functions */
 int INT_MAX ; 

uint64_t
ngx_http_tfs_generate_packet_id(void)
{
    static uint64_t id = 2;

    if (id >= INT_MAX - 1) {
        id = 1;
    }

    return ++id;
}