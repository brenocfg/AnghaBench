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
typedef  int /*<<< orphan*/  robj ;
struct TYPE_9__ {int argc; int /*<<< orphan*/ * argv; } ;
typedef  TYPE_1__ client ;
struct TYPE_10__ {int /*<<< orphan*/  czero; int /*<<< orphan*/  syntaxerr; } ;

/* Variables and functions */
 scalar_t__ C_OK ; 
 int LONG_STR_SIZE ; 
 int /*<<< orphan*/  OBJ_STRING ; 
 int /*<<< orphan*/  addReply (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyLongLong (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ checkType (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ getLongFromObjectOrReply (TYPE_1__*,int /*<<< orphan*/ ,long*,int /*<<< orphan*/ *) ; 
 unsigned char* getObjectReadOnlyString (int /*<<< orphan*/ *,long*,char*) ; 
 int /*<<< orphan*/ * lookupKeyReadOrReply (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  redisPopcount (unsigned char*,long) ; 
 TYPE_2__ shared ; 

void bitcountCommand(client *c) {
    robj *o;
    long start, end, strlen;
    unsigned char *p;
    char llbuf[LONG_STR_SIZE];

    /* Lookup, check for type, and return 0 for non existing keys. */
    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.czero)) == NULL ||
        checkType(c,o,OBJ_STRING)) return;
    p = getObjectReadOnlyString(o,&strlen,llbuf);

    /* Parse start/end range if any. */
    if (c->argc == 4) {
        if (getLongFromObjectOrReply(c,c->argv[2],&start,NULL) != C_OK)
            return;
        if (getLongFromObjectOrReply(c,c->argv[3],&end,NULL) != C_OK)
            return;
        /* Convert negative indexes */
        if (start < 0 && end < 0 && start > end) {
            addReply(c,shared.czero);
            return;
        }
        if (start < 0) start = strlen+start;
        if (end < 0) end = strlen+end;
        if (start < 0) start = 0;
        if (end < 0) end = 0;
        if (end >= strlen) end = strlen-1;
    } else if (c->argc == 2) {
        /* The whole string. */
        start = 0;
        end = strlen-1;
    } else {
        /* Syntax error. */
        addReply(c,shared.syntaxerr);
        return;
    }

    /* Precondition: end >= 0 && end < strlen, so the only condition where
     * zero can be returned is: start > end. */
    if (start > end) {
        addReply(c,shared.czero);
    } else {
        long bytes = end-start+1;

        addReplyLongLong(c,redisPopcount(p+start,bytes));
    }
}