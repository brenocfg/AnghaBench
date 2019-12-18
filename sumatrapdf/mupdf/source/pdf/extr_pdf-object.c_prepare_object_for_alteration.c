#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct TYPE_16__ {int kind; } ;
typedef  TYPE_1__ pdf_obj ;
struct TYPE_17__ {scalar_t__ repair_attempted; scalar_t__ save_in_progress; } ;
typedef  TYPE_2__ pdf_document ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_15__ {int parent_num; TYPE_2__* doc; } ;
struct TYPE_14__ {int parent_num; TYPE_2__* doc; } ;

/* Variables and functions */
 TYPE_12__* ARRAY (TYPE_1__*) ; 
 TYPE_10__* DICT (TYPE_1__*) ; 
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
#define  PDF_ARRAY 129 
#define  PDF_DICT 128 
 TYPE_1__* PDF_LIMIT ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* pdf_get_bound_document (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  pdf_set_obj_parent (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  pdf_xref_ensure_incremental_object (int /*<<< orphan*/ *,TYPE_2__*,int) ; 

__attribute__((used)) static void prepare_object_for_alteration(fz_context *ctx, pdf_obj *obj, pdf_obj *val)
{
	pdf_document *doc, *val_doc;
	int parent;

	/*
		obj should be a dict or an array. We don't care about
		any other types, as they aren't 'containers'.
	*/
	if (obj < PDF_LIMIT)
		return;

	switch (obj->kind)
	{
	case PDF_DICT:
		doc = DICT(obj)->doc;
		parent = DICT(obj)->parent_num;
		break;
	case PDF_ARRAY:
		doc = ARRAY(obj)->doc;
		parent = ARRAY(obj)->parent_num;
		break;
	default:
		return;
	}

	if (val)
	{
		val_doc = pdf_get_bound_document(ctx, val);
		if (doc && val_doc && val_doc != doc)
			fz_throw(ctx, FZ_ERROR_GENERIC, "container and item belong to different documents");
	}

	/*
		parent_num == 0 while an object is being parsed from the file.
		No further action is necessary.
	*/
	if (parent == 0 || doc->save_in_progress || doc->repair_attempted)
		return;

	/*
		Otherwise we need to ensure that the containing hierarchy of objects
		has been moved to the incremental xref section and the newly linked
		object needs to record the parent_num
	*/
	pdf_xref_ensure_incremental_object(ctx, doc, parent);
	pdf_set_obj_parent(ctx, val, parent);
}