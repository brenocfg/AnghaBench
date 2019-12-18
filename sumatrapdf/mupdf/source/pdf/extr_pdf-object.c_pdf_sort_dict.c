#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct keyval {int dummy; } ;
struct TYPE_7__ {int flags; } ;
typedef  TYPE_1__ pdf_obj ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_8__ {int /*<<< orphan*/  len; int /*<<< orphan*/  items; } ;

/* Variables and functions */
 TYPE_5__* DICT (TYPE_1__*) ; 
 int /*<<< orphan*/  OBJ_IS_DICT (TYPE_1__*) ; 
 int PDF_FLAGS_SORTED ; 
 int /*<<< orphan*/  RESOLVE (TYPE_1__*) ; 
 int /*<<< orphan*/  keyvalcmp ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void
pdf_sort_dict(fz_context *ctx, pdf_obj *obj)
{
	RESOLVE(obj);
	if (!OBJ_IS_DICT(obj))
		return;
	if (!(obj->flags & PDF_FLAGS_SORTED))
	{
		qsort(DICT(obj)->items, DICT(obj)->len, sizeof(struct keyval), keyvalcmp);
		obj->flags |= PDF_FLAGS_SORTED;
	}
}