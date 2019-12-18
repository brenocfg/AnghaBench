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
typedef  int /*<<< orphan*/  pdf_obj ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int OBJ_IS_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RESOLVE (int /*<<< orphan*/ *) ; 

int pdf_is_null(fz_context *ctx, pdf_obj *obj)
{
	RESOLVE(obj);
	return OBJ_IS_NULL(obj);
}