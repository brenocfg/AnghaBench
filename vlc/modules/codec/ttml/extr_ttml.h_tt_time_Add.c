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
struct TYPE_5__ {int frames; scalar_t__ base; } ;
typedef  TYPE_1__ tt_time_t ;

/* Variables and functions */
 int TT_FRAME_RATE ; 
 scalar_t__ vlc_tick_from_samples (int,int) ; 

__attribute__((used)) static inline tt_time_t tt_time_Add( tt_time_t t1, tt_time_t t2 )
{
    t1.base += t2.base;
    t1.frames += t2.frames;
    t1.base += vlc_tick_from_samples( t1.frames, TT_FRAME_RATE );
    t1.frames = t1.frames % TT_FRAME_RATE;
    return t1;
}