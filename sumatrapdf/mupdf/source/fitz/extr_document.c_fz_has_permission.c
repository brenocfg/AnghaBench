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
typedef  int /*<<< orphan*/  fz_permission ;
struct TYPE_4__ {int (* has_permission ) (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ fz_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 

int
fz_has_permission(fz_context *ctx, fz_document *doc, fz_permission p)
{
	if (doc && doc->has_permission)
		return doc->has_permission(ctx, doc, p);
	return 1;
}