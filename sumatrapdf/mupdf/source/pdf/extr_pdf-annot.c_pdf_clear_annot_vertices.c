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
struct TYPE_5__ {int /*<<< orphan*/  obj; } ;
typedef  TYPE_1__ pdf_annot ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Vertices ; 
 int /*<<< orphan*/  check_allowed_subtypes (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_dict_del (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_dirty_annot (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  vertices_subtypes ; 

void pdf_clear_annot_vertices(fz_context *ctx, pdf_annot *annot)
{
	check_allowed_subtypes(ctx, annot, PDF_NAME(Vertices), vertices_subtypes);
	pdf_dict_del(ctx, annot->obj, PDF_NAME(Vertices));
	pdf_dirty_annot(ctx, annot);
}