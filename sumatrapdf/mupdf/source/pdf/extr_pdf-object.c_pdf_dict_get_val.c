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
struct TYPE_3__ {int /*<<< orphan*/ * v; } ;

/* Variables and functions */
 TYPE_2__* DICT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OBJ_IS_DICT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RESOLVE (int /*<<< orphan*/ *) ; 

pdf_obj *
pdf_dict_get_val(fz_context *ctx, pdf_obj *obj, int i)
{
	RESOLVE(obj);
	if (!OBJ_IS_DICT(obj))
		return NULL;
	if (i < 0 || i >= DICT(obj)->len)
		return NULL;
	return DICT(obj)->items[i].v;
}