#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  robj ;
struct TYPE_4__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ client ;

/* Variables and functions */
 int /*<<< orphan*/  addReply (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lookupKeyRead (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

robj *lookupKeyReadOrReply(client *c, robj *key, robj *reply) {
    robj *o = lookupKeyRead(c->db, key);
    if (!o) addReply(c,reply);
    return o;
}