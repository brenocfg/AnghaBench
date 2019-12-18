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
struct TYPE_5__ {TYPE_2__* unsaved_sigs; } ;
typedef  TYPE_1__ pdf_xref ;
struct TYPE_6__ {int /*<<< orphan*/  field; struct TYPE_6__* next; } ;
typedef  TYPE_2__ pdf_unsaved_sig ;
typedef  int /*<<< orphan*/  pdf_obj ;
struct TYPE_7__ {int num_incremental_sections; TYPE_1__* xref_sections; } ;
typedef  TYPE_3__ pdf_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  ByteRange ; 
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V ; 
 int /*<<< orphan*/  pdf_array_push_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pdf_dict_getl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void presize_unsaved_signature_byteranges(fz_context *ctx, pdf_document *doc)
{
	int s;

	for (s = 0; s < doc->num_incremental_sections; s++)
	{
		pdf_xref *xref = &doc->xref_sections[s];

		if (xref->unsaved_sigs)
		{
			/* The ByteRange objects of signatures are initially written out with
			* dummy values, and then overwritten later. We need to make sure their
			* initial form at least takes enough sufficient file space */
			pdf_unsaved_sig *usig;
			int n = 0;

			for (usig = xref->unsaved_sigs; usig; usig = usig->next)
				n++;

			for (usig = xref->unsaved_sigs; usig; usig = usig->next)
			{
				/* There will be segments of bytes at the beginning, at
				* the end and between each consecutive pair of signatures,
				* hence n + 1 */
				int i;
				pdf_obj *byte_range = pdf_dict_getl(ctx, usig->field, PDF_NAME(V), PDF_NAME(ByteRange), NULL);

				for (i = 0; i < n+1; i++)
				{
					pdf_array_push_int(ctx, byte_range, INT_MAX);
					pdf_array_push_int(ctx, byte_range, INT_MAX);
				}
			}
		}
	}
}