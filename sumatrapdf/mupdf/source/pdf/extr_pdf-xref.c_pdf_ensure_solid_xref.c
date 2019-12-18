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
struct TYPE_5__ {scalar_t__ num_xref_sections; } ;
typedef  TYPE_1__ pdf_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  ensure_solid_xref (int /*<<< orphan*/ *,TYPE_1__*,int,scalar_t__) ; 
 int /*<<< orphan*/  pdf_populate_next_xref_level (int /*<<< orphan*/ *,TYPE_1__*) ; 

void pdf_ensure_solid_xref(fz_context *ctx, pdf_document *doc, int num)
{
	if (doc->num_xref_sections == 0)
		pdf_populate_next_xref_level(ctx, doc);

	ensure_solid_xref(ctx, doc, num, doc->num_xref_sections-1);
}