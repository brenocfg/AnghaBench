#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * ptr; scalar_t__ i; } ;
struct TYPE_6__ {TYPE_1__ pi; } ;
struct TYPE_7__ {TYPE_2__ u; } ;
typedef  TYPE_3__ fz_store_hash ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */

__attribute__((used)) static int
hail_mary_make_hash_key(fz_context *ctx, fz_store_hash *hash, void *key_)
{
	hash->u.pi.i = 0;
	hash->u.pi.ptr = NULL;
	return 1;
}