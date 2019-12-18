#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_5__* code; } ;
struct TYPE_9__ {int k; TYPE_5__* encode; TYPE_5__* bounds; TYPE_5__* funcs; } ;
struct TYPE_8__ {TYPE_5__* samples; } ;
struct TYPE_11__ {TYPE_3__ p; TYPE_2__ st; TYPE_1__ sa; } ;
struct TYPE_12__ {int type; TYPE_4__ u; } ;
typedef  TYPE_5__ pdf_function ;
typedef  int /*<<< orphan*/  fz_storable ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
#define  EXPONENTIAL 131 
#define  POSTSCRIPT 130 
#define  SAMPLE 129 
#define  STITCHING 128 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  pdf_drop_function (int /*<<< orphan*/ *,TYPE_5__) ; 

__attribute__((used)) static void
pdf_drop_function_imp(fz_context *ctx, fz_storable *func_)
{
	pdf_function *func = (pdf_function *)func_;
	int i;

	switch (func->type)
	{
	case SAMPLE:
		fz_free(ctx, func->u.sa.samples);
		break;
	case EXPONENTIAL:
		break;
	case STITCHING:
		for (i = 0; i < func->u.st.k; i++)
			pdf_drop_function(ctx, func->u.st.funcs[i]);
		fz_free(ctx, func->u.st.funcs);
		fz_free(ctx, func->u.st.bounds);
		fz_free(ctx, func->u.st.encode);
		break;
	case POSTSCRIPT:
		fz_free(ctx, func->u.p.code);
		break;
	}
	fz_free(ctx, func);
}