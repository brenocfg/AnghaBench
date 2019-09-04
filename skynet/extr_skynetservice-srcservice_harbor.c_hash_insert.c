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
struct keyvalue {size_t hash; scalar_t__ value; int /*<<< orphan*/ * queue; struct keyvalue* next; int /*<<< orphan*/  key; } ;
struct hashmap {struct keyvalue** node; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLOBALNAME_LENGTH ; 
 size_t HASH_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 struct keyvalue* skynet_malloc (int) ; 

__attribute__((used)) static struct keyvalue *
hash_insert(struct hashmap * hash, const char name[GLOBALNAME_LENGTH]) {
	uint32_t *ptr = (uint32_t *)name;
	uint32_t h = ptr[0] ^ ptr[1] ^ ptr[2] ^ ptr[3];
	struct keyvalue ** pkv = &hash->node[h % HASH_SIZE];
	struct keyvalue * node = skynet_malloc(sizeof(*node));
	memcpy(node->key, name, GLOBALNAME_LENGTH);
	node->next = *pkv;
	node->queue = NULL;
	node->hash = h;
	node->value = 0;
	*pkv = node;

	return node;
}