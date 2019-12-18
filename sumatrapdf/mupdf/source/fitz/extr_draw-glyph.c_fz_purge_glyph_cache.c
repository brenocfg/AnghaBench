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
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_LOCK_GLYPHCACHE ; 
 int /*<<< orphan*/  do_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
fz_purge_glyph_cache(fz_context *ctx)
{
	fz_lock(ctx, FZ_LOCK_GLYPHCACHE);
	do_purge(ctx);
	fz_unlock(ctx, FZ_LOCK_GLYPHCACHE);
}