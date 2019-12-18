#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_1__* p; } ;
typedef  TYPE_3__ picture_t ;
struct TYPE_12__ {int i_ball_x; int i_ball_y; int i_ballSize; size_t ballColor; TYPE_2__* colorList; int /*<<< orphan*/  (* drawingPixelFunction ) (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ;} ;
typedef  TYPE_4__ filter_sys_t ;
struct TYPE_10__ {int /*<<< orphan*/  comp3; int /*<<< orphan*/  comp2; int /*<<< orphan*/  comp1; } ;
struct TYPE_9__ {int i_visible_pitch; int i_visible_lines; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void drawBall( filter_sys_t *p_sys, picture_t *p_outpic )
{
    int x = p_sys->i_ball_x;
    int y = p_sys->i_ball_y;
    int size = p_sys->i_ballSize;

    const int i_width = p_outpic->p[0].i_visible_pitch;
    const int i_height = p_outpic->p[0].i_visible_lines;

    for( int j = y - size; j <= y + size; j++ )
    {
        bool b_skip = ( x - size ) % 2;
        for( int i = x - size; i <= x + size; i++ )
        {
            /* Draw the pixel if it is inside the disk
               and check we don't write out the frame. */
            if( ( i - x ) * ( i - x ) + ( j - y ) * ( j - y ) <= size * size
                && i >= 0 && i < i_width
                && j >= 0 && j < i_height )
            {
                ( *p_sys->drawingPixelFunction )( p_sys, p_outpic,
                                    p_sys->colorList[ p_sys->ballColor ].comp1,
                                    p_sys->colorList[ p_sys->ballColor ].comp2,
                                    p_sys->colorList[ p_sys->ballColor ].comp3,
                                    i, j, b_skip );
            }
            b_skip = !b_skip;
        }
    }
}