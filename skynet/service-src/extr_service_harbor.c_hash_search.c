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
typedef  size_t uint32_t ;
struct keyvalue {size_t hash; struct keyvalue* next; int /*<<< orphan*/  key; } ;
struct hashmap {struct keyvalue** node; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLOBALNAME_LENGTH ; 
 size_t HASH_SIZE ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct keyvalue *
hash_search(struct hashmap * hash, const char name[GLOBALNAME_LENGTH]) {
	uint32_t *ptr = (uint32_t*) name;
	uint32_t h = ptr[0] ^ ptr[1] ^ ptr[2] ^ ptr[3];
	struct keyvalue * node = hash->node[h % HASH_SIZE];
	while (node) {
		if (node->hash == h && strncmp(node->key, name, GLOBALNAME_LENGTH) == 0) {
			return node;
		}
		node = node->next;
	}
	return NULL;
}