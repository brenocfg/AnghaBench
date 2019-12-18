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
struct TYPE_2__ {int len; int /*<<< orphan*/ * items; } ;

/* Variables and functions */
 TYPE_1__* ARRAY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  OBJ_IS_ARRAY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RESOLVE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  pdf_array_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_drop_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_keep_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_objkindstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_object_for_alteration (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
pdf_array_put(fz_context *ctx, pdf_obj *obj, int i, pdf_obj *item)
{
	RESOLVE(obj);
	if (!OBJ_IS_ARRAY(obj))
		fz_throw(ctx, FZ_ERROR_GENERIC, "not an array (%s)", pdf_objkindstr(obj));
	if (i == ARRAY(obj)->len)
	{
		pdf_array_push(ctx, obj, item);
		return;
	}
	if (i < 0 || i > ARRAY(obj)->len)
		fz_throw(ctx, FZ_ERROR_GENERIC, "index out of bounds");
	prepare_object_for_alteration(ctx, obj, item);
	pdf_drop_obj(ctx, ARRAY(obj)->items[i]);
	ARRAY(obj)->items[i] = pdf_keep_obj(ctx, item);
}