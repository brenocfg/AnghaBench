#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  pdf_drop_obj (int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static void pdf_drop_obj_as_void(fz_context *ctx, void *obj)
{
	pdf_drop_obj(ctx, obj);
}