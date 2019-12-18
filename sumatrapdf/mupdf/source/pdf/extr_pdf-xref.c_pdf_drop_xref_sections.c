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
struct TYPE_4__ {scalar_t__ num_incremental_sections; scalar_t__ num_xref_sections; int /*<<< orphan*/ * xref_sections; scalar_t__ saved_num_xref_sections; int /*<<< orphan*/ * saved_xref_sections; } ;
typedef  TYPE_1__ pdf_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  pdf_drop_xref_sections_imp (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void pdf_drop_xref_sections(fz_context *ctx, pdf_document *doc)
{
	pdf_drop_xref_sections_imp(ctx, doc, doc->saved_xref_sections, doc->saved_num_xref_sections);
	pdf_drop_xref_sections_imp(ctx, doc, doc->xref_sections, doc->num_xref_sections);

	doc->saved_xref_sections = NULL;
	doc->saved_num_xref_sections = 0;
	doc->xref_sections = NULL;
	doc->num_xref_sections = 0;
	doc->num_incremental_sections = 0;
}