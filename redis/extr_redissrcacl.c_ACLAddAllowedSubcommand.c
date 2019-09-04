#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ *** allowed_subcommands; } ;
typedef  TYPE_1__ user ;
typedef  int /*<<< orphan*/  sds ;

/* Variables and functions */
 int USER_COMMAND_BITS_COUNT ; 
 int /*<<< orphan*/ * sdsnew (char const*) ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ *** zcalloc (int) ; 
 int /*<<< orphan*/ ** zrealloc (int /*<<< orphan*/ **,int) ; 

void ACLAddAllowedSubcommand(user *u, unsigned long id, const char *sub) {
    /* If this is the first subcommand to be configured for
     * this user, we have to allocate the subcommands array. */
    if (u->allowed_subcommands == NULL) {
        u->allowed_subcommands = zcalloc(USER_COMMAND_BITS_COUNT *
                                 sizeof(sds*));
    }

    /* We also need to enlarge the allocation pointing to the
     * null terminated SDS array, to make space for this one.
     * To start check the current size, and while we are here
     * make sure the subcommand is not already specified inside. */
    long items = 0;
    if (u->allowed_subcommands[id]) {
        while(u->allowed_subcommands[id][items]) {
            /* If it's already here do not add it again. */
            if (!strcasecmp(u->allowed_subcommands[id][items],sub)) return;
            items++;
        }
    }

    /* Now we can make space for the new item (and the null term). */
    items += 2;
    u->allowed_subcommands[id] = zrealloc(u->allowed_subcommands[id],
                                 sizeof(sds)*items);
    u->allowed_subcommands[id][items-2] = sdsnew(sub);
    u->allowed_subcommands[id][items-1] = NULL;
}