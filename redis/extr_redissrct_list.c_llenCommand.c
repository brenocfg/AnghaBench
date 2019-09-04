#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  robj ;
struct TYPE_7__ {int /*<<< orphan*/ * argv; } ;
typedef  TYPE_1__ client ;
struct TYPE_8__ {int /*<<< orphan*/  czero; } ;

/* Variables and functions */
 int /*<<< orphan*/  OBJ_LIST ; 
 int /*<<< orphan*/  addReplyLongLong (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ checkType (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listTypeLength (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lookupKeyReadOrReply (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ shared ; 

void llenCommand(client *c) {
    robj *o = lookupKeyReadOrReply(c,c->argv[1],shared.czero);
    if (o == NULL || checkType(c,o,OBJ_LIST)) return;
    addReplyLongLong(c,listTypeLength(o));
}