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
struct ext2fs_hashmap_entry {size_t size; int /*<<< orphan*/  data; int /*<<< orphan*/  (* free ) (int /*<<< orphan*/ ) ;struct ext2fs_hashmap_entry* next; struct ext2fs_hashmap_entry** entries; } ;
struct ext2fs_hashmap {size_t size; int /*<<< orphan*/  data; int /*<<< orphan*/  (* free ) (int /*<<< orphan*/ ) ;struct ext2fs_hashmap* next; struct ext2fs_hashmap** entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct ext2fs_hashmap_entry*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void ext2fs_hashmap_free(struct ext2fs_hashmap *h)
{
	size_t	i;

	for (i = 0; i < h->size; ++i) {
		struct ext2fs_hashmap_entry *it = h->entries[i];
		while (it) {
			struct ext2fs_hashmap_entry *tmp = it->next;
			if (h->free)
				h->free(it->data);
			free(it);
			it = tmp;
		}
	}
	free(h);
}