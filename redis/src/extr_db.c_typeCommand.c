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
struct TYPE_4__ {int /*<<< orphan*/ * argv; int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ client ;

/* Variables and functions */
 int /*<<< orphan*/  LOOKUP_NOTOUCH ; 
 int /*<<< orphan*/  addReplyStatus (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getObjectTypeName (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lookupKeyReadWithFlags (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void typeCommand(client *c) {
    robj *o;
    o = lookupKeyReadWithFlags(c->db,c->argv[1],LOOKUP_NOTOUCH);
    addReplyStatus(c, getObjectTypeName(o));
}