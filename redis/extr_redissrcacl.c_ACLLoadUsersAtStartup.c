#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ sds ;
struct TYPE_2__ {char* acl_filename; } ;

/* Variables and functions */
 scalar_t__ ACLLoadConfiguredUsers () ; 
 scalar_t__ ACLLoadFromFile (char*) ; 
 scalar_t__ C_ERR ; 
 int /*<<< orphan*/  LL_WARNING ; 
 int /*<<< orphan*/  UsersToLoad ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ listLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsfree (scalar_t__) ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,...) ; 

void ACLLoadUsersAtStartup(void) {
    if (server.acl_filename[0] != '\0' && listLength(UsersToLoad) != 0) {
        serverLog(LL_WARNING,
            "Configuring Redis with users defined in redis.conf and at "
            "the same setting an ACL file path is invalid. This setup "
            "is very likely to lead to configuration errors and security "
            "holes, please define either an ACL file or declare users "
            "directly in your redis.conf, but not both.");
        exit(1);
    }

    if (ACLLoadConfiguredUsers() == C_ERR) {
        serverLog(LL_WARNING,
            "Critical error while loading ACLs. Exiting.");
        exit(1);
    }

    if (server.acl_filename[0] != '\0') {
        sds errors = ACLLoadFromFile(server.acl_filename);
        if (errors) {
            serverLog(LL_WARNING,
                "Aborting Redis startup because of ACL errors: %s", errors);
            sdsfree(errors);
            exit(1);
        }
    }
}