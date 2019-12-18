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
struct TYPE_11__ {int /*<<< orphan*/  length; } ;
typedef  TYPE_1__ stream ;
struct TYPE_12__ {TYPE_1__* ptr; } ;
typedef  TYPE_2__ robj ;
struct TYPE_13__ {int /*<<< orphan*/ * argv; } ;
typedef  TYPE_3__ client ;
struct TYPE_14__ {int /*<<< orphan*/  czero; } ;

/* Variables and functions */
 int /*<<< orphan*/  OBJ_STREAM ; 
 int /*<<< orphan*/  addReplyLongLong (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ checkType (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* lookupKeyReadOrReply (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__ shared ; 

void xlenCommand(client *c) {
    robj *o;
    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.czero)) == NULL
        || checkType(c,o,OBJ_STREAM)) return;
    stream *s = o->ptr;
    addReplyLongLong(c,s->length);
}