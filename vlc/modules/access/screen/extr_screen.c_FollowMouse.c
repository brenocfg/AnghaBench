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
struct TYPE_3__ {int i_width; int i_height; scalar_t__ i_screen_height; void* i_top; scalar_t__ i_screen_width; void* i_left; } ;
typedef  TYPE_1__ demux_sys_t ;

/* Variables and functions */
 void* __MIN (unsigned int,scalar_t__) ; 

void FollowMouse( demux_sys_t *p_sys, int i_x, int i_y )
{
    i_x -= p_sys->i_width/2;
    if( i_x < 0 ) i_x = 0;
    p_sys->i_left = __MIN( (unsigned int)i_x,
    p_sys->i_screen_width - p_sys->i_width );

    i_y -= p_sys->i_height/2;
    if( i_y < 0 ) i_y = 0;
    p_sys->i_top = __MIN( (unsigned int)i_y,
    p_sys->i_screen_height - p_sys->i_height );
}