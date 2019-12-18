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
struct TYPE_5__ {int /*<<< orphan*/  p_blocks; int /*<<< orphan*/ * pp_append; } ;
struct TYPE_6__ {int i_first_frame_index; int b_initializing; int b_contiguous; TYPE_1__ queue; int /*<<< orphan*/  dts; int /*<<< orphan*/  i_pcr; int /*<<< orphan*/  fmt_old; int /*<<< orphan*/  fmt; } ;
typedef  TYPE_2__ logical_stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  UNKNOWN_ES ; 
 int /*<<< orphan*/  VLC_TICK_INVALID ; 
 int /*<<< orphan*/  date_Set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  es_format_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void Ogg_LogicalStreamInit( logical_stream_t *p_stream )
{
    memset( p_stream, 0, sizeof(logical_stream_t) );
    es_format_Init( &p_stream->fmt, UNKNOWN_ES, 0 );
    es_format_Init( &p_stream->fmt_old, UNKNOWN_ES, 0 );
    p_stream->i_pcr = VLC_TICK_INVALID;
    p_stream->i_first_frame_index = 1;
    date_Set( &p_stream->dts, VLC_TICK_INVALID );
    p_stream->b_initializing = true;
    p_stream->b_contiguous = true; /* default */
    p_stream->queue.pp_append = &p_stream->queue.p_blocks;
}