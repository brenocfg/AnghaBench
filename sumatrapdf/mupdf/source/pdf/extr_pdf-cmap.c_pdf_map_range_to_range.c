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
typedef  int /*<<< orphan*/  pdf_cmap ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  add_range (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,unsigned int,int,int,int /*<<< orphan*/ ) ; 

void
pdf_map_range_to_range(fz_context *ctx, pdf_cmap *cmap, unsigned int low, unsigned int high, int out)
{
	add_range(ctx, cmap, low, high, out, 1, 0);
}