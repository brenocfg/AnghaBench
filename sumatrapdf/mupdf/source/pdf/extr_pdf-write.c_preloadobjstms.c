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
typedef  int /*<<< orphan*/  pdf_obj ;
typedef  int /*<<< orphan*/  pdf_document ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_2__ {char type; } ;

/* Variables and functions */
 int /*<<< orphan*/  pdf_drop_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* pdf_get_xref_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * pdf_load_object (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int pdf_xref_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void preloadobjstms(fz_context *ctx, pdf_document *doc)
{
	pdf_obj *obj;
	int num;

	/* xref_len may change due to repair, so check it every iteration */
	for (num = 0; num < pdf_xref_len(ctx, doc); num++)
	{
		if (pdf_get_xref_entry(ctx, doc, num)->type == 'o')
		{
			obj = pdf_load_object(ctx, doc, num);
			pdf_drop_obj(ctx, obj);
		}
	}
}