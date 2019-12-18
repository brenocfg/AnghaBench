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
typedef  int /*<<< orphan*/  pdf_document ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_2__ {int /*<<< orphan*/ * doc; } ;

/* Variables and functions */
 scalar_t__ OBJ_IS_INDIRECT (int /*<<< orphan*/ *) ; 
 TYPE_1__* REF (int /*<<< orphan*/ *) ; 

pdf_document *pdf_get_indirect_document(fz_context *ctx, pdf_obj *obj)
{
	if (OBJ_IS_INDIRECT(obj))
		return REF(obj)->doc;
	return NULL;
}