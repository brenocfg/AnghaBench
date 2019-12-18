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
typedef  void demux_t ;
struct TYPE_3__ {int* p_buffer; int /*<<< orphan*/  i_flags; } ;
typedef  TYPE_1__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_FLAG_DISCONTINUITY ; 
 int /*<<< orphan*/  VLC_UNUSED (void*) ; 

__attribute__((used)) static void stream_header (demux_t *demux, void *data, block_t *block)
{
    VLC_UNUSED(demux);
    VLC_UNUSED(data);
    if(block->p_buffer[1] & 0x80) /* TS M-bit == discontinuity (RFC 2250, 2.1) */
    {
        block->i_flags |= BLOCK_FLAG_DISCONTINUITY;
    }
}