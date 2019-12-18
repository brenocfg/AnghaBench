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
typedef  scalar_t__ ts_standards_e ;
struct TYPE_3__ {scalar_t__ standard; } ;
typedef  TYPE_1__ demux_sys_t ;

/* Variables and functions */
 scalar_t__ TS_STANDARD_AUTO ; 

void TsChangeStandard( demux_sys_t *p_sys, ts_standards_e v )
{
    if( p_sys->standard != TS_STANDARD_AUTO &&
        p_sys->standard != v )
        return; /* TODO */
    p_sys->standard = v;
}