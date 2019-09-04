#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ encoding; char* ptr; } ;
typedef  TYPE_1__ robj ;
typedef  int /*<<< orphan*/  llbuf ;
struct TYPE_13__ {int /*<<< orphan*/ * argv; } ;
typedef  TYPE_2__ client ;
struct TYPE_14__ {int /*<<< orphan*/  emptybulk; } ;

/* Variables and functions */
 scalar_t__ C_OK ; 
 scalar_t__ OBJ_ENCODING_INT ; 
 int /*<<< orphan*/  OBJ_STRING ; 
 int /*<<< orphan*/  addReply (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyBulkCBuffer (TYPE_2__*,char*,long long) ; 
 scalar_t__ checkType (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ getLongLongFromObjectOrReply (TYPE_2__*,int /*<<< orphan*/ ,long long*,int /*<<< orphan*/ *) ; 
 size_t ll2string (char*,int,long) ; 
 TYPE_1__* lookupKeyReadOrReply (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t sdslen (char*) ; 
 TYPE_3__ shared ; 

void getrangeCommand(client *c) {
    robj *o;
    long long start, end;
    char *str, llbuf[32];
    size_t strlen;

    if (getLongLongFromObjectOrReply(c,c->argv[2],&start,NULL) != C_OK)
        return;
    if (getLongLongFromObjectOrReply(c,c->argv[3],&end,NULL) != C_OK)
        return;
    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.emptybulk)) == NULL ||
        checkType(c,o,OBJ_STRING)) return;

    if (o->encoding == OBJ_ENCODING_INT) {
        str = llbuf;
        strlen = ll2string(llbuf,sizeof(llbuf),(long)o->ptr);
    } else {
        str = o->ptr;
        strlen = sdslen(str);
    }

    /* Convert negative indexes */
    if (start < 0 && end < 0 && start > end) {
        addReply(c,shared.emptybulk);
        return;
    }
    if (start < 0) start = strlen+start;
    if (end < 0) end = strlen+end;
    if (start < 0) start = 0;
    if (end < 0) end = 0;
    if ((unsigned long long)end >= strlen) end = strlen-1;

    /* Precondition: end >= 0 && end < strlen, so the only condition where
     * nothing can be returned is: start > end. */
    if (start > end || strlen == 0) {
        addReply(c,shared.emptybulk);
    } else {
        addReplyBulkCBuffer(c,(char*)str+start,end-start+1);
    }
}