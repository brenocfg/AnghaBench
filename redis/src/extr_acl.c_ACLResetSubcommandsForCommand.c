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
struct TYPE_3__ {scalar_t__** allowed_subcommands; } ;
typedef  TYPE_1__ user ;

/* Variables and functions */
 int /*<<< orphan*/  sdsfree (scalar_t__) ; 
 int /*<<< orphan*/  zfree (scalar_t__*) ; 

void ACLResetSubcommandsForCommand(user *u, unsigned long id) {
    if (u->allowed_subcommands && u->allowed_subcommands[id]) {
        for (int i = 0; u->allowed_subcommands[id][i]; i++)
            sdsfree(u->allowed_subcommands[id][i]);
        zfree(u->allowed_subcommands[id]);
        u->allowed_subcommands[id] = NULL;
    }
}