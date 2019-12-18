#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int len; struct TYPE_6__* ocgs; int /*<<< orphan*/  obj; int /*<<< orphan*/  intent; } ;
typedef  TYPE_1__ pdf_ocg_descriptor ;
struct TYPE_7__ {TYPE_1__* ocg; } ;
typedef  TYPE_2__ pdf_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  drop_ui (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  pdf_drop_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
pdf_drop_ocg(fz_context *ctx, pdf_document *doc)
{
	pdf_ocg_descriptor *desc;
	int i;

	if (!doc)
		return;
	desc = doc->ocg;
	if (!desc)
		return;

	drop_ui(ctx, desc);
	pdf_drop_obj(ctx, desc->intent);
	for (i = 0; i < desc->len; i++)
		pdf_drop_obj(ctx, desc->ocgs[i].obj);
	fz_free(ctx, desc->ocgs);
	fz_free(ctx, desc);
}