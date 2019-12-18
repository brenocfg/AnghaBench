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
typedef  int /*<<< orphan*/  fz_outline ;
struct TYPE_5__ {int /*<<< orphan*/ * (* load_outline ) (int /*<<< orphan*/ *,TYPE_1__*) ;} ;
typedef  TYPE_1__ fz_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_ensure_layout (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ *,TYPE_1__*) ; 

fz_outline *
fz_load_outline(fz_context *ctx, fz_document *doc)
{
	fz_ensure_layout(ctx, doc);
	if (doc && doc->load_outline)
		return doc->load_outline(ctx, doc);
	return NULL;
}