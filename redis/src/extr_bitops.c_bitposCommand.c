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
struct TYPE_9__ {int argc; int /*<<< orphan*/ * argv; int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ client ;
struct TYPE_10__ {int /*<<< orphan*/  syntaxerr; } ;

/* Variables and functions */
 scalar_t__ C_OK ; 
 int LONG_STR_SIZE ; 
 int /*<<< orphan*/  OBJ_STRING ; 
 int /*<<< orphan*/  addReply (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyError (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  addReplyLongLong (TYPE_1__*,long) ; 
 scalar_t__ checkType (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ getLongFromObjectOrReply (TYPE_1__*,int /*<<< orphan*/ ,long*,int /*<<< orphan*/ *) ; 
 unsigned char* getObjectReadOnlyString (int /*<<< orphan*/ *,long*,char*) ; 
 int /*<<< orphan*/ * lookupKeyRead (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long redisBitpos (unsigned char*,long,long) ; 
 TYPE_2__ shared ; 

void bitposCommand(client *c) {
    robj *o;
    long bit, start, end, strlen;
    unsigned char *p;
    char llbuf[LONG_STR_SIZE];
    int end_given = 0;

    /* Parse the bit argument to understand what we are looking for, set
     * or clear bits. */
    if (getLongFromObjectOrReply(c,c->argv[2],&bit,NULL) != C_OK)
        return;
    if (bit != 0 && bit != 1) {
        addReplyError(c, "The bit argument must be 1 or 0.");
        return;
    }

    /* If the key does not exist, from our point of view it is an infinite
     * array of 0 bits. If the user is looking for the fist clear bit return 0,
     * If the user is looking for the first set bit, return -1. */
    if ((o = lookupKeyRead(c->db,c->argv[1])) == NULL) {
        addReplyLongLong(c, bit ? -1 : 0);
        return;
    }
    if (checkType(c,o,OBJ_STRING)) return;
    p = getObjectReadOnlyString(o,&strlen,llbuf);

    /* Parse start/end range if any. */
    if (c->argc == 4 || c->argc == 5) {
        if (getLongFromObjectOrReply(c,c->argv[3],&start,NULL) != C_OK)
            return;
        if (c->argc == 5) {
            if (getLongFromObjectOrReply(c,c->argv[4],&end,NULL) != C_OK)
                return;
            end_given = 1;
        } else {
            end = strlen-1;
        }
        /* Convert negative indexes */
        if (start < 0) start = strlen+start;
        if (end < 0) end = strlen+end;
        if (start < 0) start = 0;
        if (end < 0) end = 0;
        if (end >= strlen) end = strlen-1;
    } else if (c->argc == 3) {
        /* The whole string. */
        start = 0;
        end = strlen-1;
    } else {
        /* Syntax error. */
        addReply(c,shared.syntaxerr);
        return;
    }

    /* For empty ranges (start > end) we return -1 as an empty range does
     * not contain a 0 nor a 1. */
    if (start > end) {
        addReplyLongLong(c, -1);
    } else {
        long bytes = end-start+1;
        long pos = redisBitpos(p+start,bytes,bit);

        /* If we are looking for clear bits, and the user specified an exact
         * range with start-end, we can't consider the right of the range as
         * zero padded (as we do when no explicit end is given).
         *
         * So if redisBitpos() returns the first bit outside the range,
         * we return -1 to the caller, to mean, in the specified range there
         * is not a single "0" bit. */
        if (end_given && bit == 0 && pos == bytes*8) {
            addReplyLongLong(c,-1);
            return;
        }
        if (pos != -1) pos += start*8; /* Adjust for the bytes we skipped. */
        addReplyLongLong(c,pos);
    }
}