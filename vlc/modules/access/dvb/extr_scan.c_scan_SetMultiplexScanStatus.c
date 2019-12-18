#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int i_multiplex_toscan; } ;
typedef  TYPE_1__ scan_t ;
struct TYPE_6__ {int b_scanned; } ;
typedef  TYPE_2__ scan_multiplex_t ;

/* Variables and functions */

__attribute__((used)) static void scan_SetMultiplexScanStatus( scan_t *p_scan, scan_multiplex_t *p_mplex, bool b_scanned )
{
    if( p_mplex->b_scanned != b_scanned )
    {
        p_mplex->b_scanned = b_scanned;
        p_scan->i_multiplex_toscan += ( b_scanned ) ? -1 : 1;
    }
}