#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_23__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_17__ ;

/* Type definitions */
struct keyval {int dummy; } ;
struct TYPE_26__ {int flags; } ;
typedef  TYPE_1__ pdf_obj ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_27__ {int len; int cap; TYPE_17__* items; } ;
struct TYPE_25__ {TYPE_1__* v; void* k; } ;

/* Variables and functions */
 TYPE_23__* DICT (TYPE_1__*) ; 
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  OBJ_IS_DICT (TYPE_1__*) ; 
 int /*<<< orphan*/  OBJ_IS_NAME (TYPE_1__*) ; 
 int PDF_FLAGS_SORTED ; 
 TYPE_1__* PDF_LIMIT ; 
 int /*<<< orphan*/  RESOLVE (TYPE_1__*) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (TYPE_17__*,TYPE_17__*,int) ; 
 int pdf_dict_find (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*) ; 
 int pdf_dict_finds (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_dict_grow (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  pdf_drop_obj (int /*<<< orphan*/ *,TYPE_1__*) ; 
 void* pdf_keep_obj (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  pdf_objkindstr (TYPE_1__*) ; 
 int /*<<< orphan*/  pdf_sort_dict (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  pdf_to_name (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  prepare_object_for_alteration (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static void
pdf_dict_get_put(fz_context *ctx, pdf_obj *obj, pdf_obj *key, pdf_obj *val, pdf_obj **old_val)
{
	int i;

	if (old_val)
		*old_val = NULL;

	RESOLVE(obj);
	if (!OBJ_IS_DICT(obj))
		fz_throw(ctx, FZ_ERROR_GENERIC, "not a dict (%s)", pdf_objkindstr(obj));
	if (!OBJ_IS_NAME(key))
		fz_throw(ctx, FZ_ERROR_GENERIC, "key is not a name (%s)", pdf_objkindstr(obj));

	if (DICT(obj)->len > 100 && !(obj->flags & PDF_FLAGS_SORTED))
		pdf_sort_dict(ctx, obj);

	if (key < PDF_LIMIT)
		i = pdf_dict_find(ctx, obj, key);
	else
		i = pdf_dict_finds(ctx, obj, pdf_to_name(ctx, key));

	prepare_object_for_alteration(ctx, obj, val);

	if (i >= 0 && i < DICT(obj)->len)
	{
		if (DICT(obj)->items[i].v != val)
		{
			pdf_obj *d = DICT(obj)->items[i].v;
			DICT(obj)->items[i].v = pdf_keep_obj(ctx, val);
			if (old_val)
				*old_val = d;
			else
				pdf_drop_obj(ctx, d);
		}
	}
	else
	{
		if (DICT(obj)->len + 1 > DICT(obj)->cap)
			pdf_dict_grow(ctx, obj);

		i = -1-i;
		if ((obj->flags & PDF_FLAGS_SORTED) && DICT(obj)->len > 0)
			memmove(&DICT(obj)->items[i + 1],
					&DICT(obj)->items[i],
					(DICT(obj)->len - i) * sizeof(struct keyval));

		DICT(obj)->items[i].k = pdf_keep_obj(ctx, key);
		DICT(obj)->items[i].v = pdf_keep_obj(ctx, val);
		DICT(obj)->len ++;
	}
}