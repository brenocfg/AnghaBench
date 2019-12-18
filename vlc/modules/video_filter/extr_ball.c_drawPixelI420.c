#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
struct TYPE_5__ {TYPE_1__* p; } ;
typedef  TYPE_2__ picture_t ;
typedef  int /*<<< orphan*/  filter_sys_t ;
struct TYPE_4__ {int i_pitch; void** p_pixels; } ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void drawPixelI420( filter_sys_t *p_sys, picture_t *p_outpic,
                           uint8_t Y, uint8_t U, uint8_t V,
                           int x, int y, bool b_skip )
{
    VLC_UNUSED( p_sys );
    *( p_outpic->p[0].p_pixels + p_outpic->p[0].i_pitch * y + x ) = Y;
    if( !b_skip )
    {
        *( p_outpic->p[2].p_pixels + p_outpic->p[2].i_pitch
                                     * ( y / 2 ) + x / 2 ) = U;
        *( p_outpic->p[1].p_pixels + p_outpic->p[1].i_pitch
                                     * ( y / 2 ) + x / 2 ) = V;
    }
}