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
typedef  int /*<<< orphan*/  vout_thread_t ;

/* Variables and functions */
 short OSD_HOR_SLIDER ; 
 int VOUT_SPU_CHANNEL_OSD_HSLIDER ; 
 int VOUT_SPU_CHANNEL_OSD_VSLIDER ; 
 int /*<<< orphan*/  vout_OSDSlider (int /*<<< orphan*/ *,int,int,short) ; 

__attribute__((used)) static inline void
vouts_osd_Slider(vout_thread_t **vouts, size_t count, int position, short type)
{
    int channel = type == OSD_HOR_SLIDER ?
        VOUT_SPU_CHANNEL_OSD_HSLIDER : VOUT_SPU_CHANNEL_OSD_VSLIDER;
    for (size_t i = 0; i < count; ++i)
        vout_OSDSlider(vouts[i], channel, position, type);
}