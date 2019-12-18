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
struct TYPE_2__ {char* buf; } ;

/* Variables and functions */
 scalar_t__ OBJ_IS_STRING (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RESOLVE (int /*<<< orphan*/ *) ; 
 TYPE_1__* STRING (int /*<<< orphan*/ *) ; 

char *pdf_to_str_buf(fz_context *ctx, pdf_obj *obj)
{
	RESOLVE(obj);
	if (OBJ_IS_STRING(obj))
		return STRING(obj)->buf;
	return "";
}