#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flags; } ;
typedef  TYPE_1__ pdf_obj ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int PDF_FLAGS_MARKED ; 
 TYPE_1__* PDF_LIMIT ; 
 int /*<<< orphan*/  RESOLVE (TYPE_1__*) ; 

int
pdf_mark_obj(fz_context *ctx, pdf_obj *obj)
{
	int marked;
	RESOLVE(obj);
	if (obj < PDF_LIMIT)
		return 0;
	marked = !!(obj->flags & PDF_FLAGS_MARKED);
	obj->flags |= PDF_FLAGS_MARKED;
	return marked;
}