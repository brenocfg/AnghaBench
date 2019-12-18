#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ flv_header_bytes_sent; scalar_t__ flv_header_len; } ;
typedef  TYPE_1__ stream_sys_t ;

/* Variables and functions */

__attribute__((used)) static inline bool header_unfinished( stream_sys_t *p_sys )
{
    return p_sys->flv_header_bytes_sent < p_sys->flv_header_len;
}