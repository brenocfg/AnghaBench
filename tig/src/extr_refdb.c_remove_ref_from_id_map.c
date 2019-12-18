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
struct ref {int /*<<< orphan*/  id; struct ref* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  refs_by_id ; 
 void** string_map_get_at (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_map_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
remove_ref_from_id_map(struct ref *ref)
{
	void **ref_slot = string_map_get_at(&refs_by_id, ref->id);
	struct ref *list = ref_slot ? *ref_slot : NULL;
	struct ref *prev = NULL;

	for (; list; prev = list, list = list->next) {
		if (list != ref)
			continue;

		if (!prev)
			*ref_slot = ref->next;
		else
			prev->next = ref->next;
		ref->next = NULL;
		break;
	}

	if (ref_slot && !*ref_slot)
		string_map_remove(&refs_by_id, ref->id);
}