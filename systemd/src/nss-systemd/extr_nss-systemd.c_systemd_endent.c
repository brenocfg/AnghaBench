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
typedef  int /*<<< orphan*/  UserEntry ;
struct TYPE_4__ {int /*<<< orphan*/ * position; int /*<<< orphan*/ * entries; } ;
typedef  TYPE_1__ GetentData ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  user_entry_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void systemd_endent(GetentData *data) {
        UserEntry *p;

        assert(data);

        while ((p = data->entries))
                user_entry_free(p);

        data->position = NULL;
}