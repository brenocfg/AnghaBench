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
struct TYPE_4__ {int /*<<< orphan*/  cs; int /*<<< orphan*/  refs; } ;
typedef  TYPE_1__ tile_key ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_drop_colorspace_store_key (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ fz_drop_imp (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void
fz_drop_tile_key(fz_context *ctx, void *key_)
{
	tile_key *key = key_;
	if (fz_drop_imp(ctx, key, &key->refs))
	{
		fz_drop_colorspace_store_key(ctx, key->cs);
		fz_free(ctx, key);
	}
}