#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_obj ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_4__ {int len; TYPE_1__* items; } ;
struct TYPE_3__ {int /*<<< orphan*/  v; } ;

/* Variables and functions */
 TYPE_2__* DICT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  OBJ_IS_DICT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PDF_NULL ; 
 int /*<<< orphan*/  RESOLVE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  pdf_drop_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_objkindstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_object_for_alteration (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
pdf_dict_put_val_null(fz_context *ctx, pdf_obj *obj, int idx)
{
	RESOLVE(obj);
	if (!OBJ_IS_DICT(obj))
		fz_throw(ctx, FZ_ERROR_GENERIC, "not a dict (%s)", pdf_objkindstr(obj));
	if (idx < 0 || idx >= DICT(obj)->len)
		fz_throw(ctx, FZ_ERROR_GENERIC, "index out of bounds");

	prepare_object_for_alteration(ctx, obj, NULL);
	pdf_drop_obj(ctx, DICT(obj)->items[idx].v);
	DICT(obj)->items[idx].v = PDF_NULL;
}