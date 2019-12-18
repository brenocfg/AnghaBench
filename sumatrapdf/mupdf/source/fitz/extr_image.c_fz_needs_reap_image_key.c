#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* image; } ;
typedef  TYPE_2__ fz_image_key ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_3__ {int /*<<< orphan*/  key_storable; } ;

/* Variables and functions */
 int fz_key_storable_needs_reaping (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
fz_needs_reap_image_key(fz_context *ctx, void *key_)
{
	fz_image_key *key = (fz_image_key *)key_;

	return fz_key_storable_needs_reaping(ctx, &key->image->key_storable);
}