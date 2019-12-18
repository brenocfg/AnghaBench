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
typedef  int /*<<< orphan*/  fz_storable ;
struct TYPE_3__ {int /*<<< orphan*/  gctx; } ;
typedef  TYPE_1__ fz_jbig2_globals ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  jbig2_global_ctx_free (int /*<<< orphan*/ ) ; 

void
fz_drop_jbig2_globals_imp(fz_context *ctx, fz_storable *globals_)
{
	fz_jbig2_globals *globals = (fz_jbig2_globals *)globals_;
	jbig2_global_ctx_free(globals->gctx);
	fz_free(ctx, globals);
}