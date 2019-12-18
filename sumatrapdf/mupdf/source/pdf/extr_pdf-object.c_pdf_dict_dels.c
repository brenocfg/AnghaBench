#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_9__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_2__ pdf_obj ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_13__ {int len; TYPE_1__* items; } ;
struct TYPE_11__ {int /*<<< orphan*/  v; int /*<<< orphan*/  k; } ;

/* Variables and functions */
 TYPE_9__* DICT (TYPE_2__*) ; 
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  OBJ_IS_DICT (TYPE_2__*) ; 
 int /*<<< orphan*/  PDF_FLAGS_SORTED ; 
 int /*<<< orphan*/  RESOLVE (TYPE_2__*) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int pdf_dict_finds (int /*<<< orphan*/ *,TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  pdf_drop_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_objkindstr (TYPE_2__*) ; 
 int /*<<< orphan*/  prepare_object_for_alteration (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 

void
pdf_dict_dels(fz_context *ctx, pdf_obj *obj, const char *key)
{
	int i;

	RESOLVE(obj);
	if (!OBJ_IS_DICT(obj))
		fz_throw(ctx, FZ_ERROR_GENERIC, "not a dict (%s)", pdf_objkindstr(obj));
	if (!key)
		fz_throw(ctx, FZ_ERROR_GENERIC, "key is null");

	prepare_object_for_alteration(ctx, obj, NULL);
	i = pdf_dict_finds(ctx, obj, key);
	if (i >= 0)
	{
		pdf_drop_obj(ctx, DICT(obj)->items[i].k);
		pdf_drop_obj(ctx, DICT(obj)->items[i].v);
		obj->flags &= ~PDF_FLAGS_SORTED;
		DICT(obj)->items[i] = DICT(obj)->items[DICT(obj)->len-1];
		DICT(obj)->len --;
	}
}