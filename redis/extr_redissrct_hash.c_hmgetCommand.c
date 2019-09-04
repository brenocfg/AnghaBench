#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ type; } ;
typedef  TYPE_1__ robj ;
struct TYPE_12__ {int argc; TYPE_5__** argv; int /*<<< orphan*/  db; } ;
typedef  TYPE_2__ client ;
struct TYPE_14__ {int /*<<< orphan*/  ptr; } ;
struct TYPE_13__ {int /*<<< orphan*/  wrongtypeerr; } ;

/* Variables and functions */
 scalar_t__ OBJ_HASH ; 
 int /*<<< orphan*/  addHashFieldToReply (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReply (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyArrayLen (TYPE_2__*,int) ; 
 TYPE_1__* lookupKeyRead (int /*<<< orphan*/ ,TYPE_5__*) ; 
 TYPE_3__ shared ; 

void hmgetCommand(client *c) {
    robj *o;
    int i;

    /* Don't abort when the key cannot be found. Non-existing keys are empty
     * hashes, where HMGET should respond with a series of null bulks. */
    o = lookupKeyRead(c->db, c->argv[1]);
    if (o != NULL && o->type != OBJ_HASH) {
        addReply(c, shared.wrongtypeerr);
        return;
    }

    addReplyArrayLen(c, c->argc-2);
    for (i = 2; i < c->argc; i++) {
        addHashFieldToReply(c, o, c->argv[i]->ptr);
    }
}