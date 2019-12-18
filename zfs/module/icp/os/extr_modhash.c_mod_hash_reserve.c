#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  mhs_nomem; } ;
struct TYPE_5__ {TYPE_1__ mh_stat; int /*<<< orphan*/  mh_sleep; } ;
typedef  TYPE_2__ mod_hash_t ;
typedef  int /*<<< orphan*/ * mod_hash_hndl_t ;

/* Variables and functions */
 int MH_ERR_NOMEM ; 
 int /*<<< orphan*/ * kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mh_e_cache ; 

int
mod_hash_reserve(mod_hash_t *hash, mod_hash_hndl_t *handlep)
{
	*handlep = kmem_cache_alloc(mh_e_cache, hash->mh_sleep);
	if (*handlep == NULL) {
		hash->mh_stat.mhs_nomem++;
		return (MH_ERR_NOMEM);
	}

	return (0);
}