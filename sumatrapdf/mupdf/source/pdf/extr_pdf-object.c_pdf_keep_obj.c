#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  refs; } ;
typedef  TYPE_1__ pdf_obj ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 TYPE_1__* PDF_LIMIT ; 
 TYPE_1__* fz_keep_imp16 (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 

pdf_obj *
pdf_keep_obj(fz_context *ctx, pdf_obj *obj)
{
	if (obj >= PDF_LIMIT)
		return fz_keep_imp16(ctx, obj, &obj->refs);
	return obj;
}