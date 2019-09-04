#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * items; } ;
struct glyphinfo {TYPE_1__ ordered_vertices; } ;
typedef  size_t WORD ;
typedef  int /*<<< orphan*/  D3DXVECTOR2 ;

/* Variables and functions */
 int /*<<< orphan*/ * get_indexed_point (int /*<<< orphan*/ *) ; 

__attribute__((used)) static D3DXVECTOR2 *get_ordered_vertex(struct glyphinfo *glyph, WORD index)
{
    return get_indexed_point(&glyph->ordered_vertices.items[index]);
}