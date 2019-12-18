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
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 int /*<<< orphan*/  block_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_demux_chained_Send (void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stream_decode (demux_t *demux, void *data, block_t *block)
{
    if (data)
        vlc_demux_chained_Send(data, block);
    else
        block_Release (block);
    (void)demux;
}