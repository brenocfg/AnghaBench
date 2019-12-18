#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {size_t mlen; size_t rlen; size_t xlen; TYPE_3__* xranges; TYPE_2__* ranges; TYPE_1__* mranges; } ;
typedef  TYPE_4__ pdf_cmap ;
struct TYPE_11__ {int low; int high; int out; scalar_t__ many; } ;
typedef  TYPE_5__ cmap_splay ;
struct TYPE_9__ {int low; int high; int out; } ;
struct TYPE_8__ {int low; int high; int out; } ;
struct TYPE_7__ {int low; int out; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void
copy_node_types(cmap_splay *node, void *arg)
{
	pdf_cmap *cmap = (pdf_cmap *)arg;

	if (node->many)
	{
		assert(node->low == node->high);
		cmap->mranges[cmap->mlen].low = node->low;
		cmap->mranges[cmap->mlen].out = node->out;
		cmap->mlen++;
	}
	else if (node->low <= 0xffff && node->high <= 0xFFFF && node->out <= 0xFFFF)
	{
		cmap->ranges[cmap->rlen].low = node->low;
		cmap->ranges[cmap->rlen].high = node->high;
		cmap->ranges[cmap->rlen].out = node->out;
		cmap->rlen++;
	}
	else
	{
		cmap->xranges[cmap->xlen].low = node->low;
		cmap->xranges[cmap->xlen].high = node->high;
		cmap->xranges[cmap->xlen].out = node->out;
		cmap->xlen++;
	}
}