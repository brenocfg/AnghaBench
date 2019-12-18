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
typedef  int vlc_tick_t ;
struct TYPE_3__ {int /*<<< orphan*/  s; } ;
typedef  TYPE_1__ demux_t ;

/* Variables and functions */
 int CDG_FRAME_DELTA ; 
 int CDG_FRAME_SIZE ; 
 int vlc_stream_Tell (int /*<<< orphan*/ ) ; 

__attribute__((used)) static vlc_tick_t PosToDate( demux_t *p_demux )
{
    return vlc_stream_Tell( p_demux->s ) / CDG_FRAME_SIZE * CDG_FRAME_DELTA;
}