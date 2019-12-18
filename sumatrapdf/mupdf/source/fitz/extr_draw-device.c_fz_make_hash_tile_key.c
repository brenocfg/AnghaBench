#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  cs; int /*<<< orphan*/ * ctm; int /*<<< orphan*/  has_group_alpha; int /*<<< orphan*/  has_shape; int /*<<< orphan*/  id; } ;
typedef  TYPE_3__ tile_key ;
struct TYPE_6__ {int /*<<< orphan*/  ptr; int /*<<< orphan*/ * m; int /*<<< orphan*/  has_group_alpha; int /*<<< orphan*/  has_shape; int /*<<< orphan*/  id; } ;
struct TYPE_7__ {TYPE_1__ im; } ;
struct TYPE_9__ {TYPE_2__ u; } ;
typedef  TYPE_4__ fz_store_hash ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */

__attribute__((used)) static int
fz_make_hash_tile_key(fz_context *ctx, fz_store_hash *hash, void *key_)
{
	tile_key *key = key_;

	hash->u.im.id = key->id;
	hash->u.im.has_shape = key->has_shape;
	hash->u.im.has_group_alpha = key->has_group_alpha;
	hash->u.im.m[0] = key->ctm[0];
	hash->u.im.m[1] = key->ctm[1];
	hash->u.im.m[2] = key->ctm[2];
	hash->u.im.m[3] = key->ctm[3];
	hash->u.im.ptr = key->cs;
	return 1;
}