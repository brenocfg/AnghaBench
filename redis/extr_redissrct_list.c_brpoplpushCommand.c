#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ type; } ;
typedef  TYPE_1__ robj ;
typedef  int /*<<< orphan*/  mstime_t ;
struct TYPE_15__ {int flags; int /*<<< orphan*/ * argv; int /*<<< orphan*/  db; } ;
typedef  TYPE_2__ client ;
struct TYPE_16__ {int /*<<< orphan*/  wrongtypeerr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCKED_LIST ; 
 int CLIENT_MULTI ; 
 scalar_t__ C_OK ; 
 scalar_t__ OBJ_LIST ; 
 int /*<<< orphan*/  UNIT_SECONDS ; 
 int /*<<< orphan*/  addReply (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyNull (TYPE_2__*) ; 
 int /*<<< orphan*/  blockForKeys (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ getTimeoutFromObjectOrReply (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ listTypeLength (TYPE_1__*) ; 
 TYPE_1__* lookupKeyWrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpoplpushCommand (TYPE_2__*) ; 
 int /*<<< orphan*/  serverAssertWithInfo (TYPE_2__*,TYPE_1__*,int) ; 
 TYPE_3__ shared ; 

void brpoplpushCommand(client *c) {
    mstime_t timeout;

    if (getTimeoutFromObjectOrReply(c,c->argv[3],&timeout,UNIT_SECONDS)
        != C_OK) return;

    robj *key = lookupKeyWrite(c->db, c->argv[1]);

    if (key == NULL) {
        if (c->flags & CLIENT_MULTI) {
            /* Blocking against an empty list in a multi state
             * returns immediately. */
            addReplyNull(c);
        } else {
            /* The list is empty and the client blocks. */
            blockForKeys(c,BLOCKED_LIST,c->argv + 1,1,timeout,c->argv[2],NULL);
        }
    } else {
        if (key->type != OBJ_LIST) {
            addReply(c, shared.wrongtypeerr);
        } else {
            /* The list exists and has elements, so
             * the regular rpoplpushCommand is executed. */
            serverAssertWithInfo(c,key,listTypeLength(key) > 0);
            rpoplpushCommand(c);
        }
    }
}