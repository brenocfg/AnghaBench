#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ user ;
struct rewriteConfigState {int dummy; } ;
typedef  int /*<<< orphan*/  sds ;
struct TYPE_10__ {TYPE_1__* data; } ;
typedef  TYPE_2__ raxIterator ;
struct TYPE_11__ {char* acl_filename; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACLDescribeUser (TYPE_1__*) ; 
 int /*<<< orphan*/  Users ; 
 scalar_t__ raxNext (TYPE_2__*) ; 
 int /*<<< orphan*/  raxSeek (TYPE_2__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raxStart (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raxStop (TYPE_2__*) ; 
 int /*<<< orphan*/  rewriteConfigMarkAsProcessed (struct rewriteConfigState*,char*) ; 
 int /*<<< orphan*/  rewriteConfigRewriteLine (struct rewriteConfigState*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sdscatlen (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sdscatsds (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsnew (char*) ; 
 TYPE_3__ server ; 

void rewriteConfigUserOption(struct rewriteConfigState *state) {
    /* If there is a user file defined we just mark this configuration
     * directive as processed, so that all the lines containing users
     * inside the config file gets discarded. */
    if (server.acl_filename[0] != '\0') {
        rewriteConfigMarkAsProcessed(state,"user");
        return;
    }

    /* Otherwise scan the list of users and rewrite every line. Note that
     * in case the list here is empty, the effect will just be to comment
     * all the users directive inside the config file. */
    raxIterator ri;
    raxStart(&ri,Users);
    raxSeek(&ri,"^",NULL,0);
    while(raxNext(&ri)) {
        user *u = ri.data;
        sds line = sdsnew("user ");
        line = sdscatsds(line,u->name);
        line = sdscatlen(line," ",1);
        sds descr = ACLDescribeUser(u);
        line = sdscatsds(line,descr);
        sdsfree(descr);
        rewriteConfigRewriteLine(state,"user",line,1);
    }
    raxStop(&ri);

    /* Mark "user" as processed in case there are no defined users. */
    rewriteConfigMarkAsProcessed(state,"user");
}