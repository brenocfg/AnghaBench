#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  uid_refs; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  manager_deserialize_uid_refs_one_internal (TYPE_1__*,int /*<<< orphan*/ *,char const*) ; 

void manager_deserialize_uid_refs_one(Manager *m, const char *value) {
        manager_deserialize_uid_refs_one_internal(m, &m->uid_refs, value);
}