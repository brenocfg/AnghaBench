#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  v; int /*<<< orphan*/  k; } ;
typedef  TYPE_1__ pdf_obj ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_7__ {int len; TYPE_1__* items; } ;

/* Variables and functions */
 TYPE_4__* DICT (TYPE_1__*) ; 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  pdf_drop_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pdf_drop_dict(fz_context *ctx, pdf_obj *obj)
{
	int i;

	for (i = 0; i < DICT(obj)->len; i++) {
		pdf_drop_obj(ctx, DICT(obj)->items[i].k);
		pdf_drop_obj(ctx, DICT(obj)->items[i].v);
	}

	fz_free(ctx, DICT(obj)->items);
	fz_free(ctx, obj);
}