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
struct TYPE_6__ {int /*<<< orphan*/  r; int /*<<< orphan*/  i; int /*<<< orphan*/  ptr; } ;
struct TYPE_7__ {TYPE_1__ pir; } ;
struct TYPE_8__ {TYPE_2__ u; } ;
typedef  TYPE_3__ fz_store_hash ;
struct TYPE_9__ {int /*<<< orphan*/  rect; int /*<<< orphan*/  l2factor; int /*<<< orphan*/  image; } ;
typedef  TYPE_4__ fz_image_key ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */

__attribute__((used)) static int
fz_make_hash_image_key(fz_context *ctx, fz_store_hash *hash, void *key_)
{
	fz_image_key *key = (fz_image_key *)key_;
	hash->u.pir.ptr = key->image;
	hash->u.pir.i = key->l2factor;
	hash->u.pir.r = key->rect;
	return 1;
}