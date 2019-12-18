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
struct TYPE_2__ {int /*<<< orphan*/  has_group_alpha; int /*<<< orphan*/  has_shape; int /*<<< orphan*/  cs; int /*<<< orphan*/ * ctm; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ tile_key ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_snprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fz_format_tile_key(fz_context *ctx, char *s, int n, void *key_)
{
	tile_key *key = (tile_key *)key_;
	fz_snprintf(s, n, "(tile id=%x, ctm=%g %g %g %g, cs=%x, shape=%d, ga=%d)",
			key->id, key->ctm[0], key->ctm[1], key->ctm[2], key->ctm[3], key->cs,
			key->has_shape, key->has_group_alpha);
}