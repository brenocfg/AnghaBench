#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {scalar_t__ type; } ;
typedef  TYPE_1__ robj ;
struct TYPE_20__ {int argc; TYPE_3__* db; TYPE_4__** argv; } ;
typedef  TYPE_2__ client ;
struct TYPE_24__ {int dirty; } ;
struct TYPE_23__ {int /*<<< orphan*/  wrongtypeerr; } ;
struct TYPE_22__ {int /*<<< orphan*/  ptr; } ;
struct TYPE_21__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  NOTIFY_SET ; 
 scalar_t__ OBJ_SET ; 
 int /*<<< orphan*/  addReply (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyLongLong (TYPE_2__*,int) ; 
 int /*<<< orphan*/  dbAdd (TYPE_3__*,TYPE_4__*,TYPE_1__*) ; 
 TYPE_1__* lookupKeyWrite (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  notifyKeyspaceEvent (int /*<<< orphan*/ ,char*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_8__ server ; 
 scalar_t__ setTypeAdd (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* setTypeCreate (int /*<<< orphan*/ ) ; 
 TYPE_5__ shared ; 
 int /*<<< orphan*/  signalModifiedKey (TYPE_3__*,TYPE_4__*) ; 

void saddCommand(client *c) {
    robj *set;
    int j, added = 0;

    set = lookupKeyWrite(c->db,c->argv[1]);
    if (set == NULL) {
        set = setTypeCreate(c->argv[2]->ptr);
        dbAdd(c->db,c->argv[1],set);
    } else {
        if (set->type != OBJ_SET) {
            addReply(c,shared.wrongtypeerr);
            return;
        }
    }

    for (j = 2; j < c->argc; j++) {
        if (setTypeAdd(set,c->argv[j]->ptr)) added++;
    }
    if (added) {
        signalModifiedKey(c->db,c->argv[1]);
        notifyKeyspaceEvent(NOTIFY_SET,"sadd",c->argv[1],c->db->id);
    }
    server.dirty += added;
    addReplyLongLong(c,added);
}