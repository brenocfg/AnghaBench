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
struct TYPE_4__ {int count; size_t* items; } ;
struct triangulation {scalar_t__ last_on_top; TYPE_1__ vertex_stack; } ;
struct point2d_index {int vertex; struct outline* outline; } ;
struct outline {int count; TYPE_3__* items; } ;
struct TYPE_5__ {struct point2d_index* items; } ;
struct glyphinfo {TYPE_2__ ordered_vertices; } ;
typedef  size_t WORD ;
struct TYPE_6__ {int /*<<< orphan*/  pos; } ;
typedef  int /*<<< orphan*/  D3DXVECTOR2 ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */

__attribute__((used)) static D3DXVECTOR2 *triangulation_get_next_point(struct triangulation *t, struct glyphinfo *glyph, BOOL on_top)
{
    int i = t->last_on_top == on_top ? t->vertex_stack.count - 1 : 0;
    WORD idx = t->vertex_stack.items[i];
    struct point2d_index *pt_idx = &glyph->ordered_vertices.items[idx];
    struct outline *outline = pt_idx->outline;

    if (on_top)
        i = (pt_idx->vertex + outline->count - 1) % outline->count;
    else
        i = (pt_idx->vertex + 1) % outline->count;

    return &outline->items[i].pos;
}