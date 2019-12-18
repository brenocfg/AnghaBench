#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int needs_new_ap; TYPE_2__* page; } ;
typedef  TYPE_3__ pdf_annot ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_6__ {TYPE_1__* doc; } ;
struct TYPE_5__ {int dirty; } ;

/* Variables and functions */

void
pdf_dirty_annot(fz_context *ctx, pdf_annot *annot)
{
	annot->needs_new_ap = 1;
	if (annot->page && annot->page->doc)
		annot->page->doc->dirty = 1;
}