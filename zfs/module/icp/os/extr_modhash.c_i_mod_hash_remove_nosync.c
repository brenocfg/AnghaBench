#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct mod_hash_entry {int /*<<< orphan*/  mhe_val; int /*<<< orphan*/  mhe_key; struct mod_hash_entry* mhe_next; } ;
typedef  int /*<<< orphan*/  mod_hash_val_t ;
struct TYPE_7__ {int /*<<< orphan*/  mhs_nelems; } ;
struct TYPE_8__ {TYPE_1__ mh_stat; struct mod_hash_entry** mh_entries; } ;
typedef  TYPE_2__ mod_hash_t ;
typedef  int /*<<< orphan*/  mod_hash_key_t ;

/* Variables and functions */
 int MH_ERR_NOTFOUND ; 
 scalar_t__ MH_KEYCMP (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MH_KEY_DESTROY (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int i_mod_hash (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct mod_hash_entry*) ; 
 int /*<<< orphan*/  mh_e_cache ; 

int
i_mod_hash_remove_nosync(mod_hash_t *hash, mod_hash_key_t key,
    mod_hash_val_t *val)
{
	int hashidx;
	struct mod_hash_entry *e, *ep;

	hashidx = i_mod_hash(hash, key);
	ep = NULL; /* e's parent */

	for (e = hash->mh_entries[hashidx]; e != NULL; e = e->mhe_next) {
		if (MH_KEYCMP(hash, e->mhe_key, key) == 0)
			break;
		ep = e;
	}

	if (e == NULL) {	/* not found */
		return (MH_ERR_NOTFOUND);
	}

	if (ep == NULL) 	/* special case 1st element in bucket */
		hash->mh_entries[hashidx] = e->mhe_next;
	else
		ep->mhe_next = e->mhe_next;

	/*
	 * Clean up resources used by the node's key.
	 */
	MH_KEY_DESTROY(hash, e->mhe_key);

	*val = e->mhe_val;
	kmem_cache_free(mh_e_cache, e);
	hash->mh_stat.mhs_nelems--;

	return (0);
}