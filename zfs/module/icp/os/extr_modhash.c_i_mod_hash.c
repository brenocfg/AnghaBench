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
typedef  int uint_t ;
struct TYPE_3__ {int mh_nchains; int (* mh_hashalg ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  mh_hashalg_data; } ;
typedef  TYPE_1__ mod_hash_t ;
typedef  int /*<<< orphan*/  mod_hash_key_t ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

uint_t
i_mod_hash(mod_hash_t *hash, mod_hash_key_t key)
{
	uint_t h;
	/*
	 * Prevent div by 0 problems;
	 * Also a nice shortcut when using a hash as a list
	 */
	if (hash->mh_nchains == 1)
		return (0);

	h = (hash->mh_hashalg)(hash->mh_hashalg_data, key);
	return (h % (hash->mh_nchains - 1));
}