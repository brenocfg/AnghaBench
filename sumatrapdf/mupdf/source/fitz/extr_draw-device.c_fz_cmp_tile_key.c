#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ id; scalar_t__ has_shape; scalar_t__ has_group_alpha; scalar_t__* ctm; scalar_t__ cs; } ;
typedef  TYPE_1__ tile_key ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */

__attribute__((used)) static int
fz_cmp_tile_key(fz_context *ctx, void *k0_, void *k1_)
{
	tile_key *k0 = k0_;
	tile_key *k1 = k1_;
	return k0->id == k1->id &&
		k0->has_shape == k1->has_shape &&
		k0->has_group_alpha == k1->has_group_alpha &&
		k0->ctm[0] == k1->ctm[0] &&
		k0->ctm[1] == k1->ctm[1] &&
		k0->ctm[2] == k1->ctm[2] &&
		k0->ctm[3] == k1->ctm[3] &&
		k0->cs == k1->cs;
}