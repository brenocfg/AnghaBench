#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ encoding; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ robj ;

/* Variables and functions */
 int LIST_HEAD ; 
 scalar_t__ OBJ_ENCODING_QUICKLIST ; 
 int QUICKLIST_HEAD ; 
 int QUICKLIST_TAIL ; 
 int /*<<< orphan*/  decrRefCount (TYPE_1__*) ; 
 TYPE_1__* getDecodedObject (TYPE_1__*) ; 
 int /*<<< orphan*/  quicklistPush (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int) ; 
 size_t sdslen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serverPanic (char*) ; 

void listTypePush(robj *subject, robj *value, int where) {
    if (subject->encoding == OBJ_ENCODING_QUICKLIST) {
        int pos = (where == LIST_HEAD) ? QUICKLIST_HEAD : QUICKLIST_TAIL;
        value = getDecodedObject(value);
        size_t len = sdslen(value->ptr);
        quicklistPush(subject->ptr, value->ptr, len, pos);
        decrRefCount(value);
    } else {
        serverPanic("Unknown list encoding");
    }
}