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
typedef  scalar_t__ vlc_tick_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  i_samples; } ;
typedef  TYPE_1__ frame_span_t ;

/* Variables and functions */
 scalar_t__ VLC_TICK_0 ; 
 scalar_t__ VLC_TICK_INVALID ; 
 scalar_t__ vlc_tick_from_samples (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline vlc_tick_t FrameSpanGetTime( frame_span_t *span, uint32_t i_sample_rate )
{
    if( !i_sample_rate )
        return VLC_TICK_INVALID;

    return vlc_tick_from_samples( span->i_samples, i_sample_rate) + VLC_TICK_0;
}