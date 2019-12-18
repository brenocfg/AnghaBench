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
typedef  int /*<<< orphan*/  demux_t ;

/* Variables and functions */
 int demux_filter_enable_disable (int /*<<< orphan*/ *,char const*,int) ; 

bool demux_FilterEnable( demux_t *p_demux_chain, const char* psz_demux )
{
    return demux_filter_enable_disable( p_demux_chain, psz_demux, true );
}