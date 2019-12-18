#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_obj ;
struct TYPE_10__ {void* y; void* x; } ;
struct TYPE_9__ {void* y; void* x; } ;
struct TYPE_8__ {void* y; void* x; } ;
struct TYPE_7__ {void* y; void* x; } ;
struct TYPE_11__ {TYPE_4__ lr; TYPE_3__ ll; TYPE_2__ ur; TYPE_1__ ul; } ;
typedef  TYPE_5__ fz_quad ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 void* pdf_array_get_real (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

fz_quad
pdf_to_quad(fz_context *ctx, pdf_obj *array, int offset)
{
	fz_quad q;
	q.ul.x = pdf_array_get_real(ctx, array, offset+0);
	q.ul.y = pdf_array_get_real(ctx, array, offset+1);
	q.ur.x = pdf_array_get_real(ctx, array, offset+2);
	q.ur.y = pdf_array_get_real(ctx, array, offset+3);
	q.ll.x = pdf_array_get_real(ctx, array, offset+4);
	q.ll.y = pdf_array_get_real(ctx, array, offset+5);
	q.lr.x = pdf_array_get_real(ctx, array, offset+6);
	q.lr.y = pdf_array_get_real(ctx, array, offset+7);
	return q;
}