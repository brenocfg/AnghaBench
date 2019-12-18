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
struct mod_hash_entry {int /*<<< orphan*/  mhe_val; int /*<<< orphan*/  mhe_key; struct mod_hash_entry* mhe_next; } ;
typedef  int /*<<< orphan*/  mod_hash_val_t ;
struct TYPE_6__ {int /*<<< orphan*/  mhs_miss; int /*<<< orphan*/  mhs_hit; } ;
struct TYPE_7__ {TYPE_1__ mh_stat; struct mod_hash_entry** mh_entries; } ;
typedef  TYPE_2__ mod_hash_t ;
typedef  int /*<<< orphan*/  mod_hash_key_t ;

/* Variables and functions */
 int MH_ERR_NOTFOUND ; 
 scalar_t__ MH_KEYCMP (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t i_mod_hash (TYPE_2__*,int /*<<< orphan*/ ) ; 

int
i_mod_hash_find_nosync(mod_hash_t *hash, mod_hash_key_t key,
    mod_hash_val_t *val)
{
	uint_t hashidx;
	struct mod_hash_entry *e;

	hashidx = i_mod_hash(hash, key);

	for (e = hash->mh_entries[hashidx]; e != NULL; e = e->mhe_next) {
		if (MH_KEYCMP(hash, e->mhe_key, key) == 0) {
			*val = e->mhe_val;
			hash->mh_stat.mhs_hit++;
			return (0);
		}
	}
	hash->mh_stat.mhs_miss++;
	return (MH_ERR_NOTFOUND);
}