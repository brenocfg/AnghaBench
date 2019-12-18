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
struct TYPE_3__ {int /*<<< orphan*/  writer; } ;
typedef  TYPE_1__ vlc_demux_chained_t ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_stream_fifo_Queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void vlc_demux_chained_Send(vlc_demux_chained_t *dc, block_t *block)
{
    vlc_stream_fifo_Queue(dc->writer, block);
}