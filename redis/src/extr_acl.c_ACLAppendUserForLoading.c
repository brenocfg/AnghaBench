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
typedef  int /*<<< orphan*/  user ;
typedef  int /*<<< orphan*/ * sds ;

/* Variables and functions */
 int /*<<< orphan*/ * ACLCreateUnlinkedUser () ; 
 int /*<<< orphan*/  ACLFreeUser (int /*<<< orphan*/ *) ; 
 int ACLSetUser (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int C_ERR ; 
 int C_OK ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  UsersToLoad ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  listAddNodeTail (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * sdsdup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdslen (int /*<<< orphan*/ *) ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ ** zmalloc (int) ; 

int ACLAppendUserForLoading(sds *argv, int argc, int *argc_err) {
    if (argc < 2 || strcasecmp(argv[0],"user")) {
        if (argc_err) *argc_err = 0;
        return C_ERR;
    }

    /* Try to apply the user rules in a fake user to see if they
     * are actually valid. */
    user *fakeuser = ACLCreateUnlinkedUser();

    for (int j = 2; j < argc; j++) {
        if (ACLSetUser(fakeuser,argv[j],sdslen(argv[j])) == C_ERR) {
            if (errno != ENOENT) {
                ACLFreeUser(fakeuser);
                if (argc_err) *argc_err = j;
                return C_ERR;
            }
        }
    }

    /* Rules look valid, let's append the user to the list. */
    sds *copy = zmalloc(sizeof(sds)*argc);
    for (int j = 1; j < argc; j++) copy[j-1] = sdsdup(argv[j]);
    copy[argc-1] = NULL;
    listAddNodeTail(UsersToLoad,copy);
    ACLFreeUser(fakeuser);
    return C_OK;
}