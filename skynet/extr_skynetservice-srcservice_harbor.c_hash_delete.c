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
struct keyvalue {int /*<<< orphan*/  queue; struct keyvalue* next; struct keyvalue** node; } ;
struct hashmap {int /*<<< orphan*/  queue; struct hashmap* next; struct hashmap** node; } ;

/* Variables and functions */
 int HASH_SIZE ; 
 int /*<<< orphan*/  release_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skynet_free (struct keyvalue*) ; 

__attribute__((used)) static void
hash_delete(struct hashmap *hash) {
	int i;
	for (i=0;i<HASH_SIZE;i++) {
		struct keyvalue * node = hash->node[i];
		while (node) {
			struct keyvalue * next = node->next;
			release_queue(node->queue);
			skynet_free(node);
			node = next;
		}
	}
	skynet_free(hash);
}