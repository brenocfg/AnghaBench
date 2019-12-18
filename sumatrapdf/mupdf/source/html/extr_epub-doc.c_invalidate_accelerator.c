#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_3__ {int max_chapters; int* pages_in_chapter; } ;
typedef  TYPE_1__ epub_accelerator ;

/* Variables and functions */

__attribute__((used)) static void
invalidate_accelerator(fz_context *ctx, epub_accelerator *acc)
{
	int i;

	for (i = 0; i < acc->max_chapters; i++)
		acc->pages_in_chapter[i] = -1;
}