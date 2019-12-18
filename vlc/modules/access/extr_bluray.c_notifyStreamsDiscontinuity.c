#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_demux_chained_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_6__ {int /*<<< orphan*/  p_buffer; } ;
typedef  TYPE_1__ block_t ;
struct TYPE_7__ {int /*<<< orphan*/  pid; } ;
typedef  TYPE_2__ BLURAY_STREAM_INFO ;

/* Variables and functions */
 TYPE_1__* block_Alloc (int) ; 
 int /*<<< orphan*/  vlc_demux_chained_Send (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  writeTsPacketWDiscontinuity (int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void notifyStreamsDiscontinuity( vlc_demux_chained_t *p_parser,
                                        const BLURAY_STREAM_INFO *p_sinfo, size_t i_sinfo )
{
    for( size_t i=0; i< i_sinfo; i++ )
    {
        const uint16_t i_pid = p_sinfo[i].pid;

        block_t *p_block = block_Alloc(192);
        if (!p_block)
            return;

        writeTsPacketWDiscontinuity( p_block->p_buffer, i_pid, NULL, 0 );

        vlc_demux_chained_Send(p_parser, p_block);
    }
}