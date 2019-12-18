#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  demux_t ;
struct TYPE_5__ {int i_buffer; int* p_buffer; } ;
typedef  TYPE_1__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  block_Release (TYPE_1__*) ; 
 int /*<<< orphan*/  codec_decode (int /*<<< orphan*/ *,void*,TYPE_1__*) ; 

__attribute__((used)) static void mpv_decode (demux_t *demux, void *data, block_t *block)
{
    if (block->i_buffer < 4)
    {
        block_Release (block);
        return;
    }

    block->i_buffer -= 4; /* 32-bits RTP/MPV header */
    block->p_buffer += 4;
#if 0
    if (block->p_buffer[-3] & 0x4)
    {
        /* MPEG2 Video extension header */
        /* TODO: shouldn't we skip this too ? */
    }
#endif
    codec_decode (demux, data, block);
}