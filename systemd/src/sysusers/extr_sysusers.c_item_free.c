#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  shell; int /*<<< orphan*/  home; int /*<<< orphan*/  description; int /*<<< orphan*/  gid_path; int /*<<< orphan*/  uid_path; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ Item ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 TYPE_1__* mfree (TYPE_1__*) ; 

__attribute__((used)) static Item* item_free(Item *i) {
        if (!i)
                return NULL;

        free(i->name);
        free(i->uid_path);
        free(i->gid_path);
        free(i->description);
        free(i->home);
        free(i->shell);
        return mfree(i);
}