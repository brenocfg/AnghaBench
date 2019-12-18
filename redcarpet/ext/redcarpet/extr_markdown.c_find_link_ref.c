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
typedef  int /*<<< orphan*/  uint8_t ;
struct link_ref {unsigned int id; struct link_ref* next; } ;

/* Variables and functions */
 unsigned int REF_TABLE_SIZE ; 
 unsigned int hash_link_ref (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static struct link_ref *
find_link_ref(struct link_ref **references, uint8_t *name, size_t length)
{
	unsigned int hash = hash_link_ref(name, length);
	struct link_ref *ref = NULL;

	ref = references[hash % REF_TABLE_SIZE];

	while (ref != NULL) {
		if (ref->id == hash)
			return ref;

		ref = ref->next;
	}

	return NULL;
}