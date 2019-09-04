#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  (* trigger_handler ) (int /*<<< orphan*/ *,void*) ;
struct TYPE_5__ {int numtriggers; int /*<<< orphan*/ * triggers; } ;
typedef  TYPE_1__ TriggerDesc ;
typedef  int /*<<< orphan*/  Trigger ;
struct TYPE_6__ {TYPE_1__* trigdesc; } ;
typedef  TYPE_2__* Relation ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  relation_close (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* relation_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
for_each_trigger(Oid relid, trigger_handler on_trigger, void *arg)
{
	Relation rel;

	rel = relation_open(relid, AccessShareLock);

	if (rel->trigdesc != NULL)
	{
		TriggerDesc *trigdesc = rel->trigdesc;
		int i;

		for (i = 0; i < trigdesc->numtriggers; i++)
		{
			Trigger *trigger = &trigdesc->triggers[i];

			if (!on_trigger(trigger, arg))
				break;
		}
	}

	relation_close(rel, AccessShareLock);
}