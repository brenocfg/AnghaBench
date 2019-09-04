#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {float x; float y; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ D3DXVECTOR2 ;

/* Variables and functions */
 int /*<<< orphan*/  D3DXVec2Subtract (TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static float get_line_to_point_y_distance(D3DXVECTOR2 *line_pt1,
                                          D3DXVECTOR2 *line_pt2,
                                          D3DXVECTOR2 *point)
{
    D3DXVECTOR2 line_vec = {0, 0};
    float line_pt_dx;
    float line_y;

    D3DXVec2Subtract(&line_vec, line_pt2, line_pt1);
    line_pt_dx = point->x - line_pt1->x;
    line_y = line_pt1->y + (line_vec.y * line_pt_dx) / line_vec.x;
    return point->y - line_y;
}