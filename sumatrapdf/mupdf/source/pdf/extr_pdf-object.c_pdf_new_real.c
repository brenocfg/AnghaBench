#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int refs; scalar_t__ flags; int /*<<< orphan*/  kind; } ;
struct TYPE_6__ {float f; } ;
struct TYPE_7__ {TYPE_3__ super; TYPE_1__ u; } ;
typedef  TYPE_2__ pdf_obj_num ;
typedef  TYPE_3__ pdf_obj ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 TYPE_2__* Memento_label (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PDF_REAL ; 
 int /*<<< orphan*/  fz_malloc (int /*<<< orphan*/ *,int) ; 

pdf_obj *
pdf_new_real(fz_context *ctx, float f)
{
	pdf_obj_num *obj;
	obj = Memento_label(fz_malloc(ctx, sizeof(pdf_obj_num)), "pdf_obj(real)");
	obj->super.refs = 1;
	obj->super.kind = PDF_REAL;
	obj->super.flags = 0;
	obj->u.f = f;
	return &obj->super;
}