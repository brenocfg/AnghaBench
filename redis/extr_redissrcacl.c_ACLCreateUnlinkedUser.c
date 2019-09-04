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
typedef  int /*<<< orphan*/  username ;
typedef  int /*<<< orphan*/  user ;

/* Variables and functions */
 int /*<<< orphan*/ * ACLCreateUser (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Users ; 
 int raxRemove (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serverAssert (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 

user *ACLCreateUnlinkedUser(void) {
    char username[64];
    for (int j = 0; ; j++) {
        snprintf(username,sizeof(username),"__fakeuser:%d__",j);
        user *fakeuser = ACLCreateUser(username,strlen(username));
        if (fakeuser == NULL) continue;
        int retval = raxRemove(Users,(unsigned char*) username,
                               strlen(username),NULL);
        serverAssert(retval != 0);
        return fakeuser;
    }
}