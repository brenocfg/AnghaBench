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
struct TYPE_4__ {int /*<<< orphan*/ * items; } ;
struct TYPE_3__ {int len; int /*<<< orphan*/ * items; } ;

/* Variables and functions */
 TYPE_2__* ARRAY (int /*<<< orphan*/ *) ; 
 TYPE_1__* DICT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_drop_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pdf_drop_array(fz_context *ctx, pdf_obj *obj)
{
	int i;

	for (i = 0; i < DICT(obj)->len; i++)
		pdf_drop_obj(ctx, ARRAY(obj)->items[i]);

	fz_free(ctx, DICT(obj)->items);
	fz_free(ctx, obj);
}