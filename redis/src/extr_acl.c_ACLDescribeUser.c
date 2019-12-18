#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flags; int /*<<< orphan*/  patterns; int /*<<< orphan*/  passwords; } ;
typedef  TYPE_1__ user ;
typedef  int /*<<< orphan*/  sds ;
typedef  int /*<<< orphan*/  listNode ;
typedef  int /*<<< orphan*/  listIter ;
struct TYPE_6__ {int flag; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACLDescribeUserCommandRules (TYPE_1__*) ; 
 TYPE_2__* ACLUserFlags ; 
 int USER_FLAG_ALLCOMMANDS ; 
 int USER_FLAG_ALLKEYS ; 
 int /*<<< orphan*/ * listNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listNodeValue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRewind (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdscat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdscatlen (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sdscatsds (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsempty () ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 

sds ACLDescribeUser(user *u) {
    sds res = sdsempty();

    /* Flags. */
    for (int j = 0; ACLUserFlags[j].flag; j++) {
        /* Skip the allcommands and allkeys flags because they'll be emitted
         * later as ~* and +@all. */
        if (ACLUserFlags[j].flag == USER_FLAG_ALLKEYS ||
            ACLUserFlags[j].flag == USER_FLAG_ALLCOMMANDS) continue;
        if (u->flags & ACLUserFlags[j].flag) {
            res = sdscat(res,ACLUserFlags[j].name);
            res = sdscatlen(res," ",1);
        }
    }

    /* Passwords. */
    listIter li;
    listNode *ln;
    listRewind(u->passwords,&li);
    while((ln = listNext(&li))) {
        sds thispass = listNodeValue(ln);
        res = sdscatlen(res,"#",1);
        res = sdscatsds(res,thispass);
        res = sdscatlen(res," ",1);
    }

    /* Key patterns. */
    if (u->flags & USER_FLAG_ALLKEYS) {
        res = sdscatlen(res,"~* ",3);
    } else {
        listRewind(u->patterns,&li);
        while((ln = listNext(&li))) {
            sds thispat = listNodeValue(ln);
            res = sdscatlen(res,"~",1);
            res = sdscatsds(res,thispat);
            res = sdscatlen(res," ",1);
        }
    }

    /* Command rules. */
    sds rules = ACLDescribeUserCommandRules(u);
    res = sdscatsds(res,rules);
    sdsfree(rules);
    return res;
}