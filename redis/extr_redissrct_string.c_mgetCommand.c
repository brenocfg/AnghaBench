#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ type; } ;
typedef  TYPE_1__ robj ;
struct TYPE_10__ {int argc; int /*<<< orphan*/ * argv; int /*<<< orphan*/  db; } ;
typedef  TYPE_2__ client ;

/* Variables and functions */
 scalar_t__ OBJ_STRING ; 
 int /*<<< orphan*/  addReplyArrayLen (TYPE_2__*,int) ; 
 int /*<<< orphan*/  addReplyBulk (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  addReplyNull (TYPE_2__*) ; 
 TYPE_1__* lookupKeyRead (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mgetCommand(client *c) {
    int j;

    addReplyArrayLen(c,c->argc-1);
    for (j = 1; j < c->argc; j++) {
        robj *o = lookupKeyRead(c->db,c->argv[j]);
        if (o == NULL) {
            addReplyNull(c);
        } else {
            if (o->type != OBJ_STRING) {
                addReplyNull(c);
            } else {
                addReplyBulk(c,o);
            }
        }
    }
}