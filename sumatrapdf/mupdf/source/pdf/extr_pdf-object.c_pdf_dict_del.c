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
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_2__ {int /*<<< orphan*/  n; } ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 TYPE_1__* NAME (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OBJ_IS_NAME (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PDF_LIMIT ; 
 int /*<<< orphan*/ * PDF_NAME_LIST ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_dict_dels (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_objkindstr (int /*<<< orphan*/ *) ; 

void
pdf_dict_del(fz_context *ctx, pdf_obj *obj, pdf_obj *key)
{
	if (!OBJ_IS_NAME(key))
		fz_throw(ctx, FZ_ERROR_GENERIC, "key is not a name (%s)", pdf_objkindstr(key));

	if (key < PDF_LIMIT)
		pdf_dict_dels(ctx, obj, PDF_NAME_LIST[(intptr_t)key]);
	else
		pdf_dict_dels(ctx, obj, NAME(key)->n);
}