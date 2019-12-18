#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int has_new_ap; } ;
typedef  TYPE_1__ pdf_annot ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  pdf_update_appearance (int /*<<< orphan*/ *,TYPE_1__*) ; 

int
pdf_update_annot(fz_context *ctx, pdf_annot *annot)
{
	int changed;

	pdf_update_appearance(ctx, annot);

	changed = annot->has_new_ap;
	annot->has_new_ap = 0;
	return changed;
}