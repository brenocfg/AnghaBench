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
struct TYPE_4__ {int /*<<< orphan*/  refs; } ;
typedef  TYPE_1__ fz_storable ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 void* fz_keep_imp (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 

void *
fz_keep_storable(fz_context *ctx, const fz_storable *sc)
{
	/* Explicitly drop const to allow us to use const
	 * sanely throughout the code. */
	fz_storable *s = (fz_storable *)sc;

	return fz_keep_imp(ctx, s, &s->refs);
}