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
typedef  int /*<<< orphan*/  robj ;
struct TYPE_5__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ client ;

/* Variables and functions */
 int /*<<< orphan*/  addReplyBulk (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  addReplyNull (TYPE_1__*) ; 
 int /*<<< orphan*/ * dbRandomKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decrRefCount (int /*<<< orphan*/ *) ; 

void randomkeyCommand(client *c) {
    robj *key;

    if ((key = dbRandomKey(c->db)) == NULL) {
        addReplyNull(c);
        return;
    }

    addReplyBulk(c,key);
    decrRefCount(key);
}