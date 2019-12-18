#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  zap_leaf_t ;
typedef  scalar_t__ uint16_t ;
struct zap_leaf_entry {scalar_t__ le_next; scalar_t__ le_cd; int /*<<< orphan*/  le_hash; } ;

/* Variables and functions */
 scalar_t__ CHAIN_END ; 
 scalar_t__* LEAF_HASH_ENTPTR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct zap_leaf_entry* ZAP_LEAF_ENTRY (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static uint16_t *
zap_leaf_rehash_entry(zap_leaf_t *l, uint16_t entry)
{
	struct zap_leaf_entry *le = ZAP_LEAF_ENTRY(l, entry);
	struct zap_leaf_entry *le2;
	uint16_t *chunkp;

	/*
	 * keep the entry chain sorted by cd
	 * NB: this will not cause problems for unsorted leafs, though
	 * it is unnecessary there.
	 */
	for (chunkp = LEAF_HASH_ENTPTR(l, le->le_hash);
	    *chunkp != CHAIN_END; chunkp = &le2->le_next) {
		le2 = ZAP_LEAF_ENTRY(l, *chunkp);
		if (le2->le_cd > le->le_cd)
			break;
	}

	le->le_next = *chunkp;
	*chunkp = entry;
	return (chunkp);
}