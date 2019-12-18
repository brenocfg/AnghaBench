#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  es_out_id_t ;
struct TYPE_7__ {int /*<<< orphan*/  out; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_8__ {int /*<<< orphan*/  i_pts; int /*<<< orphan*/  i_dts; } ;
typedef  TYPE_2__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_TICK_INVALID ; 
 int /*<<< orphan*/  block_Release (TYPE_2__*) ; 
 int /*<<< orphan*/  es_out_Send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  es_out_SetPCR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void codec_decode (demux_t *demux, void *data, block_t *block)
{
    if (data)
    {
        block->i_dts = VLC_TICK_INVALID; /* RTP does not specify this */
        es_out_SetPCR(demux->out, block->i_pts);
        es_out_Send (demux->out, (es_out_id_t *)data, block);
    }
    else
        block_Release (block);
}