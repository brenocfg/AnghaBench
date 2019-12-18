#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ type; } ;
typedef  TYPE_1__ robj ;
typedef  int /*<<< orphan*/  mstime_t ;
struct TYPE_14__ {int argc; int flags; int /*<<< orphan*/ * argv; int /*<<< orphan*/  db; } ;
typedef  TYPE_2__ client ;
struct TYPE_15__ {int /*<<< orphan*/  zpopmin; int /*<<< orphan*/  zpopmax; int /*<<< orphan*/  wrongtypeerr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCKED_ZSET ; 
 int CLIENT_MULTI ; 
 scalar_t__ C_OK ; 
 scalar_t__ OBJ_ZSET ; 
 int /*<<< orphan*/  UNIT_SECONDS ; 
 int ZSET_MAX ; 
 int /*<<< orphan*/  addReply (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyNullArray (TYPE_2__*) ; 
 int /*<<< orphan*/  blockForKeys (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  genericZpopCommand (TYPE_2__*,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ getTimeoutFromObjectOrReply (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* lookupKeyWrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rewriteClientCommandVector (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__ shared ; 
 scalar_t__ zsetLength (TYPE_1__*) ; 

void blockingGenericZpopCommand(client *c, int where) {
    robj *o;
    mstime_t timeout;
    int j;

    if (getTimeoutFromObjectOrReply(c,c->argv[c->argc-1],&timeout,UNIT_SECONDS)
        != C_OK) return;

    for (j = 1; j < c->argc-1; j++) {
        o = lookupKeyWrite(c->db,c->argv[j]);
        if (o != NULL) {
            if (o->type != OBJ_ZSET) {
                addReply(c,shared.wrongtypeerr);
                return;
            } else {
                if (zsetLength(o) != 0) {
                    /* Non empty zset, this is like a normal ZPOP[MIN|MAX]. */
                    genericZpopCommand(c,&c->argv[j],1,where,1,NULL);
                    /* Replicate it as an ZPOP[MIN|MAX] instead of BZPOP[MIN|MAX]. */
                    rewriteClientCommandVector(c,2,
                        where == ZSET_MAX ? shared.zpopmax : shared.zpopmin,
                        c->argv[j]);
                    return;
                }
            }
        }
    }

    /* If we are inside a MULTI/EXEC and the zset is empty the only thing
     * we can do is treating it as a timeout (even with timeout 0). */
    if (c->flags & CLIENT_MULTI) {
        addReplyNullArray(c);
        return;
    }

    /* If the keys do not exist we must block */
    blockForKeys(c,BLOCKED_ZSET,c->argv + 1,c->argc - 2,timeout,NULL,NULL);
}