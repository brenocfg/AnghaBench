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
typedef  int uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/  f_y; int /*<<< orphan*/  f_x; } ;
typedef  TYPE_1__ point_t ;

/* Variables and functions */
 TYPE_1__* malloc (int) ; 

point_t *puzzle_curve_V_2_negative(uint8_t i_pts_nbr, point_t *ps_pt)
{
    if (ps_pt == NULL)
        return NULL;

    point_t *ps_new_pt = malloc( sizeof( point_t ) * (3 * (i_pts_nbr-1) + 1) );
    if (ps_new_pt == NULL)
        return NULL;

    for (uint8_t i=0; i < (3 * (i_pts_nbr-1) + 1); i++) {
        ps_new_pt[i].f_x = -ps_pt[i].f_x;
        ps_new_pt[i].f_y = ps_pt[i].f_y;
    }

    return ps_new_pt;
}