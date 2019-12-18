#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint_t ;
struct mod_hash_entry {struct mod_hash_entry* mhe_next; int /*<<< orphan*/  mhe_val; int /*<<< orphan*/  mhe_key; } ;
typedef  int /*<<< orphan*/  mod_hash_val_t ;
struct TYPE_6__ {int /*<<< orphan*/  mhs_nelems; int /*<<< orphan*/  mhs_nomem; } ;
struct TYPE_7__ {TYPE_1__ mh_stat; struct mod_hash_entry** mh_entries; int /*<<< orphan*/  mh_sleep; } ;
typedef  TYPE_2__ mod_hash_t ;
typedef  int /*<<< orphan*/  mod_hash_key_t ;
typedef  scalar_t__ mod_hash_hndl_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (TYPE_2__*) ; 
 int MH_ERR_NOMEM ; 
 size_t i_mod_hash (TYPE_2__*,int /*<<< orphan*/ ) ; 
 struct mod_hash_entry* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mh_e_cache ; 

int
i_mod_hash_insert_nosync(mod_hash_t *hash, mod_hash_key_t key,
    mod_hash_val_t val, mod_hash_hndl_t handle)
{
	uint_t hashidx;
	struct mod_hash_entry *entry;

	ASSERT(hash);

	/*
	 * If we've not been given reserved storage, allocate storage directly,
	 * using the hash's allocation policy.
	 */
	if (handle == (mod_hash_hndl_t)0) {
		entry = kmem_cache_alloc(mh_e_cache, hash->mh_sleep);
		if (entry == NULL) {
			hash->mh_stat.mhs_nomem++;
			return (MH_ERR_NOMEM);
		}
	} else {
		entry = (struct mod_hash_entry *)handle;
	}

	hashidx = i_mod_hash(hash, key);
	entry->mhe_key = key;
	entry->mhe_val = val;
	entry->mhe_next = hash->mh_entries[hashidx];

	hash->mh_entries[hashidx] = entry;
	hash->mh_stat.mhs_nelems++;

	return (0);
}