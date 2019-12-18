#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int cap; int /*<<< orphan*/  code; } ;
struct TYPE_5__ {TYPE_2__ p; } ;
struct TYPE_7__ {TYPE_1__ u; } ;
typedef  TYPE_3__ pdf_function ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_realloc_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psobj ; 

__attribute__((used)) static void
resize_code(fz_context *ctx, pdf_function *func, int newsize)
{
	if (newsize >= func->u.p.cap)
	{
		int new_cap = func->u.p.cap + 64;
		func->u.p.code = fz_realloc_array(ctx, func->u.p.code, new_cap, psobj);
		func->u.p.cap = new_cap;
	}
}