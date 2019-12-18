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
typedef  int /*<<< orphan*/  zap_leaf_t ;
struct zap_leaf_entry {scalar_t__ le_type; unsigned long long le_hash; } ;
typedef  scalar_t__ boolean_t ;
struct TYPE_3__ {int lh_prefix_len; int lh_prefix; int /*<<< orphan*/  lh_flags; } ;
struct TYPE_4__ {TYPE_1__ l_hdr; int /*<<< orphan*/  l_hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHAIN_END ; 
 scalar_t__ ZAP_CHUNK_ENTRY ; 
 struct zap_leaf_entry* ZAP_LEAF_ENTRY (int /*<<< orphan*/ *,int) ; 
 int ZAP_LEAF_HASH_NUMENTRIES (int /*<<< orphan*/ *) ; 
 int ZAP_LEAF_NUMCHUNKS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZLF_ENTRIES_CDSORTED ; 
 TYPE_2__* zap_leaf_phys (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_leaf_rehash_entry (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zap_leaf_transfer_entry (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
zap_leaf_split(zap_leaf_t *l, zap_leaf_t *nl, boolean_t sort)
{
	int bit = 64 - 1 - zap_leaf_phys(l)->l_hdr.lh_prefix_len;

	/* set new prefix and prefix_len */
	zap_leaf_phys(l)->l_hdr.lh_prefix <<= 1;
	zap_leaf_phys(l)->l_hdr.lh_prefix_len++;
	zap_leaf_phys(nl)->l_hdr.lh_prefix =
	    zap_leaf_phys(l)->l_hdr.lh_prefix | 1;
	zap_leaf_phys(nl)->l_hdr.lh_prefix_len =
	    zap_leaf_phys(l)->l_hdr.lh_prefix_len;

	/* break existing hash chains */
	zap_memset(zap_leaf_phys(l)->l_hash, CHAIN_END,
	    2*ZAP_LEAF_HASH_NUMENTRIES(l));

	if (sort)
		zap_leaf_phys(l)->l_hdr.lh_flags |= ZLF_ENTRIES_CDSORTED;

	/*
	 * Transfer entries whose hash bit 'bit' is set to nl; rehash
	 * the remaining entries
	 *
	 * NB: We could find entries via the hashtable instead. That
	 * would be O(hashents+numents) rather than O(numblks+numents),
	 * but this accesses memory more sequentially, and when we're
	 * called, the block is usually pretty full.
	 */
	for (int i = 0; i < ZAP_LEAF_NUMCHUNKS(l); i++) {
		struct zap_leaf_entry *le = ZAP_LEAF_ENTRY(l, i);
		if (le->le_type != ZAP_CHUNK_ENTRY)
			continue;

		if (le->le_hash & (1ULL << bit))
			zap_leaf_transfer_entry(l, i, nl);
		else
			(void) zap_leaf_rehash_entry(l, i);
	}
}