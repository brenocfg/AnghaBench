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
typedef  int /*<<< orphan*/  fz_storable ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_drop_pixmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void
fz_drop_tile_record_imp(fz_context *ctx, fz_storable *storable)
{
	tile_record *tr = (tile_record *)storable;
	fz_drop_pixmap(ctx, tr->dest);
	fz_drop_pixmap(ctx, tr->shape);
	fz_drop_pixmap(ctx, tr->group_alpha);
	fz_free(ctx, tr);
}