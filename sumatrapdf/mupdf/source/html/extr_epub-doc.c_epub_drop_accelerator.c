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
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_4__ {struct TYPE_4__* pages_in_chapter; } ;
typedef  TYPE_1__ epub_accelerator ;

/* Variables and functions */
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void
epub_drop_accelerator(fz_context *ctx, epub_accelerator *acc)
{
	if (acc == NULL)
		return;

	fz_free(ctx, acc->pages_in_chapter);
	fz_free(ctx, acc);
}