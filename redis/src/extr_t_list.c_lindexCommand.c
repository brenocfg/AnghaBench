#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__ encoding; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ robj ;
struct TYPE_19__ {int /*<<< orphan*/  longval; int /*<<< orphan*/  sz; scalar_t__ value; } ;
typedef  TYPE_2__ quicklistEntry ;
struct TYPE_20__ {size_t resp; int /*<<< orphan*/ * argv; } ;
typedef  TYPE_3__ client ;
struct TYPE_21__ {int /*<<< orphan*/ * null; } ;

/* Variables and functions */
 scalar_t__ C_OK ; 
 scalar_t__ OBJ_ENCODING_QUICKLIST ; 
 int /*<<< orphan*/  OBJ_LIST ; 
 int /*<<< orphan*/  addReplyBulk (TYPE_3__*,TYPE_1__*) ; 
 int /*<<< orphan*/  addReplyNull (TYPE_3__*) ; 
 scalar_t__ checkType (TYPE_3__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* createStringObject (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* createStringObjectFromLongLong (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decrRefCount (TYPE_1__*) ; 
 scalar_t__ getLongFromObjectOrReply (TYPE_3__*,int /*<<< orphan*/ ,long*,int /*<<< orphan*/ *) ; 
 TYPE_1__* lookupKeyReadOrReply (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ quicklistIndex (int /*<<< orphan*/ ,long,TYPE_2__*) ; 
 int /*<<< orphan*/  serverPanic (char*) ; 
 TYPE_4__ shared ; 

void lindexCommand(client *c) {
    robj *o = lookupKeyReadOrReply(c,c->argv[1],shared.null[c->resp]);
    if (o == NULL || checkType(c,o,OBJ_LIST)) return;
    long index;
    robj *value = NULL;

    if ((getLongFromObjectOrReply(c, c->argv[2], &index, NULL) != C_OK))
        return;

    if (o->encoding == OBJ_ENCODING_QUICKLIST) {
        quicklistEntry entry;
        if (quicklistIndex(o->ptr, index, &entry)) {
            if (entry.value) {
                value = createStringObject((char*)entry.value,entry.sz);
            } else {
                value = createStringObjectFromLongLong(entry.longval);
            }
            addReplyBulk(c,value);
            decrRefCount(value);
        } else {
            addReplyNull(c);
        }
    } else {
        serverPanic("Unknown list encoding");
    }
}