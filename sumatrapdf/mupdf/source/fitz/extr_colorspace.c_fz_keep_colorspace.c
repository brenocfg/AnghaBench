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
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_5__ {int /*<<< orphan*/  key_storable; } ;
typedef  TYPE_1__ fz_colorspace ;

/* Variables and functions */
 TYPE_1__* fz_keep_key_storable (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

fz_colorspace *
fz_keep_colorspace(fz_context *ctx, fz_colorspace *cs)
{
	return fz_keep_key_storable(ctx, &cs->key_storable);
}