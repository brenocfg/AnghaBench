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
struct TYPE_7__ {struct TYPE_7__* name; TYPE_1__* data; } ;
typedef  TYPE_2__ UserEntry ;
struct TYPE_6__ {int /*<<< orphan*/  entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  entries ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 

__attribute__((used)) static void user_entry_free(UserEntry *p) {
        if (!p)
                return;

        if (p->data)
                LIST_REMOVE(entries, p->data->entries, p);

        free(p->name);
        free(p);
}