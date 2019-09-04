#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flags; } ;
typedef  TYPE_1__ user ;
typedef  char* sds ;
typedef  int /*<<< orphan*/  listNode ;
typedef  int /*<<< orphan*/  listIter ;

/* Variables and functions */
 TYPE_1__* ACLCreateUser (char*,int) ; 
 TYPE_1__* ACLGetUserByName (char*,int) ; 
 scalar_t__ ACLSetUser (TYPE_1__*,char*,int) ; 
 char* ACLSetUserStringError () ; 
 int C_ERR ; 
 scalar_t__ C_OK ; 
 int /*<<< orphan*/  LL_NOTICE ; 
 int /*<<< orphan*/  LL_WARNING ; 
 int USER_FLAG_DISABLED ; 
 int /*<<< orphan*/  UsersToLoad ; 
 int /*<<< orphan*/ * listNext (int /*<<< orphan*/ *) ; 
 char** listNodeValue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRewind (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sdslen (char*) ; 
 int /*<<< orphan*/  serverAssert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,char*,...) ; 

int ACLLoadConfiguredUsers(void) {
    listIter li;
    listNode *ln;
    listRewind(UsersToLoad,&li);
    while ((ln = listNext(&li)) != NULL) {
        sds *aclrules = listNodeValue(ln);
        sds username = aclrules[0];
        user *u = ACLCreateUser(username,sdslen(username));
        if (!u) {
            u = ACLGetUserByName(username,sdslen(username));
            serverAssert(u != NULL);
            ACLSetUser(u,"reset",-1);
        }

        /* Load every rule defined for this user. */
        for (int j = 1; aclrules[j]; j++) {
            if (ACLSetUser(u,aclrules[j],sdslen(aclrules[j])) != C_OK) {
                char *errmsg = ACLSetUserStringError();
                serverLog(LL_WARNING,"Error loading ACL rule '%s' for "
                                     "the user named '%s': %s",
                          aclrules[j],aclrules[0],errmsg);
                return C_ERR;
            }
        }

        /* Having a disabled user in the configuration may be an error,
         * warn about it without returning any error to the caller. */
        if (u->flags & USER_FLAG_DISABLED) {
            serverLog(LL_NOTICE, "The user '%s' is disabled (there is no "
                                 "'on' modifier in the user description). Make "
                                 "sure this is not a configuration error.",
                      aclrules[0]);
        }
    }
    return C_OK;
}