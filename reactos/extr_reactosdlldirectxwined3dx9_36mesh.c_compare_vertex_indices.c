#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct point2d_index {size_t vertex; TYPE_2__* outline; } ;
struct TYPE_6__ {float x; float y; } ;
struct TYPE_5__ {TYPE_1__* items; } ;
struct TYPE_4__ {TYPE_3__ pos; } ;
typedef  TYPE_3__ D3DXVECTOR2 ;

/* Variables and functions */

__attribute__((used)) static int compare_vertex_indices(const void *a, const void *b)
{
    const struct point2d_index *idx1 = a, *idx2 = b;
    const D3DXVECTOR2 *p1 = &idx1->outline->items[idx1->vertex].pos;
    const D3DXVECTOR2 *p2 = &idx2->outline->items[idx2->vertex].pos;
    float diff = p1->x - p2->x;

    if (diff == 0.0f)
        diff = p1->y - p2->y;

    return diff == 0.0f ? 0 : (diff > 0.0f ? -1 : 1);
}