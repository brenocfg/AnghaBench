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

/* Variables and functions */
 scalar_t__ EBUSY ; 
 scalar_t__ EEXIST ; 
 scalar_t__ EINVAL ; 
 scalar_t__ ENODEV ; 
 scalar_t__ ENOENT ; 
 scalar_t__ errno ; 

char *ACLSetUserStringError(void) {
    char *errmsg = "Wrong format";
    if (errno == ENOENT)
        errmsg = "Unknown command or category name in ACL";
    else if (errno == EINVAL)
        errmsg = "Syntax error";
    else if (errno == EBUSY)
        errmsg = "Adding a subcommand of a command already fully "
                 "added is not allowed. Remove the command to start. "
                 "Example: -DEBUG +DEBUG|DIGEST";
    else if (errno == EEXIST)
        errmsg = "Adding a pattern after the * pattern (or the "
                 "'allkeys' flag) is not valid and does not have any "
                 "effect. Try 'resetkeys' to start with an empty "
                 "list of patterns";
    else if (errno == ENODEV)
        errmsg = "The password you are trying to remove from the user does "
                 "not exist";
    return errmsg;
}