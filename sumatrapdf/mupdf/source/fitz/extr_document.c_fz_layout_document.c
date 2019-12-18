#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int did_layout; int /*<<< orphan*/  (* layout ) (int /*<<< orphan*/ *,TYPE_1__*,float,float,float) ;} ;
typedef  TYPE_1__ fz_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_1__*,float,float,float) ; 

void
fz_layout_document(fz_context *ctx, fz_document *doc, float w, float h, float em)
{
	if (doc && doc->layout)
	{
		doc->layout(ctx, doc, w, h, em);
		doc->did_layout = 1;
	}
}