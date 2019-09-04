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
struct TYPE_5__ {scalar_t__ encoding; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ robj ;

/* Variables and functions */
 int LIST_HEAD ; 
 scalar_t__ OBJ_ENCODING_QUICKLIST ; 
 int QUICKLIST_HEAD ; 
 int QUICKLIST_TAIL ; 
 TYPE_1__* createStringObjectFromLongLong (long long) ; 
 int /*<<< orphan*/  listPopSaver ; 
 scalar_t__ quicklistPopCustom (int /*<<< orphan*/ ,int,unsigned char**,int /*<<< orphan*/ *,long long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serverPanic (char*) ; 

robj *listTypePop(robj *subject, int where) {
    long long vlong;
    robj *value = NULL;

    int ql_where = where == LIST_HEAD ? QUICKLIST_HEAD : QUICKLIST_TAIL;
    if (subject->encoding == OBJ_ENCODING_QUICKLIST) {
        if (quicklistPopCustom(subject->ptr, ql_where, (unsigned char **)&value,
                               NULL, &vlong, listPopSaver)) {
            if (!value)
                value = createStringObjectFromLongLong(vlong);
        }
    } else {
        serverPanic("Unknown list encoding");
    }
    return value;
}