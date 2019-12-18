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
struct TYPE_3__ {int /*<<< orphan*/  group_alpha; int /*<<< orphan*/  shape; int /*<<< orphan*/  dest; } ;
typedef  TYPE_1__ tile_record ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 size_t fz_pixmap_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

size_t
fz_tile_size(fz_context *ctx, tile_record *tile)
{
	if (!tile)
		return 0;
	return sizeof(*tile) + fz_pixmap_size(ctx, tile->dest) + fz_pixmap_size(ctx, tile->shape) + fz_pixmap_size(ctx, tile->group_alpha);
}