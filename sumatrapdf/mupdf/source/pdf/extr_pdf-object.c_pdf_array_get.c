#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_obj ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_2__ {int len; int /*<<< orphan*/ ** items; } ;

/* Variables and functions */
 TYPE_1__* ARRAY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OBJ_IS_ARRAY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RESOLVE (int /*<<< orphan*/ *) ; 

pdf_obj *
pdf_array_get(fz_context *ctx, pdf_obj *obj, int i)
{
	RESOLVE(obj);
	if (!OBJ_IS_ARRAY(obj))
		return NULL;
	if (i < 0 || i >= ARRAY(obj)->len)
		return NULL;
	return ARRAY(obj)->items[i];
}