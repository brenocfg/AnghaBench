#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_obj ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ pdf_is_indirect (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_resolve_indirect (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_to_num (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

pdf_obj *
pdf_resolve_indirect_chain(fz_context *ctx, pdf_obj *ref)
{
	int sanity = 10;

	while (pdf_is_indirect(ctx, ref))
	{
		if (--sanity == 0)
		{
			fz_warn(ctx, "too many indirections (possible indirection cycle involving %d 0 R)", pdf_to_num(ctx, ref));
			return NULL;
		}

		ref = pdf_resolve_indirect(ctx, ref);
	}

	return ref;
}