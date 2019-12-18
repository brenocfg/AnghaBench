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
 int /*<<< orphan*/  DEMUX_GET_SEEKPOINT ; 
 scalar_t__ demux_Control (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 

int demux_GetSeekpoint( demux_t *p_demux )
{
    int seekpoint;

    if (demux_Control(p_demux, DEMUX_GET_SEEKPOINT, &seekpoint))
        seekpoint = 0;
    return seekpoint;
}