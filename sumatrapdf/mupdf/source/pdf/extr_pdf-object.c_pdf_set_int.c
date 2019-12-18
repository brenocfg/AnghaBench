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
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_3__ {int /*<<< orphan*/  i; } ;
struct TYPE_4__ {TYPE_1__ u; } ;

/* Variables and functions */
 TYPE_2__* NUM (int /*<<< orphan*/ *) ; 
 scalar_t__ OBJ_IS_INT (int /*<<< orphan*/ *) ; 

void pdf_set_int(fz_context *ctx, pdf_obj *obj, int64_t i)
{
	if (OBJ_IS_INT(obj))
		NUM(obj)->u.i = i;
}