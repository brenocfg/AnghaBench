#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_39__   TYPE_3__ ;
typedef  struct TYPE_38__   TYPE_2__ ;
typedef  struct TYPE_37__   TYPE_20__ ;
typedef  struct TYPE_36__   TYPE_1__ ;
typedef  struct TYPE_35__   TYPE_19__ ;
typedef  struct TYPE_34__   TYPE_17__ ;

/* Type definitions */
struct TYPE_36__ {int /*<<< orphan*/  dict; int /*<<< orphan*/  zsl; } ;
typedef  TYPE_1__ zset ;
typedef  int /*<<< orphan*/  zrangespec ;
typedef  int /*<<< orphan*/  zlexrangespec ;
struct TYPE_38__ {scalar_t__ encoding; TYPE_1__* ptr; } ;
typedef  TYPE_2__ robj ;
struct TYPE_39__ {TYPE_17__* db; TYPE_2__** argv; } ;
typedef  TYPE_3__ client ;
struct TYPE_37__ {unsigned long dirty; } ;
struct TYPE_35__ {int /*<<< orphan*/  czero; } ;
struct TYPE_34__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 scalar_t__ C_OK ; 
 int /*<<< orphan*/  NOTIFY_GENERIC ; 
 int /*<<< orphan*/  NOTIFY_ZSET ; 
 scalar_t__ OBJ_ENCODING_SKIPLIST ; 
 scalar_t__ OBJ_ENCODING_ZIPLIST ; 
 int /*<<< orphan*/  OBJ_ZSET ; 
#define  ZRANGE_LEX 130 
#define  ZRANGE_RANK 129 
#define  ZRANGE_SCORE 128 
 int /*<<< orphan*/  addReply (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyError (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  addReplyLongLong (TYPE_3__*,unsigned long) ; 
 scalar_t__ checkType (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbDelete (TYPE_17__*,TYPE_2__*) ; 
 int /*<<< orphan*/  dictResize (int /*<<< orphan*/ ) ; 
 scalar_t__ dictSize (int /*<<< orphan*/ ) ; 
 scalar_t__ getLongFromObjectOrReply (TYPE_3__*,TYPE_2__*,long*,int /*<<< orphan*/ *) ; 
 scalar_t__ htNeedsResize (int /*<<< orphan*/ ) ; 
 TYPE_2__* lookupKeyWriteOrReply (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  notifyKeyspaceEvent (int /*<<< orphan*/ ,char*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_20__ server ; 
 int /*<<< orphan*/  serverPanic (char*) ; 
 TYPE_19__ shared ; 
 int /*<<< orphan*/  signalModifiedKey (TYPE_17__*,TYPE_2__*) ; 
 long zsetLength (TYPE_2__*) ; 
 unsigned long zslDeleteRangeByLex (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned long zslDeleteRangeByRank (int /*<<< orphan*/ ,long,long,int /*<<< orphan*/ ) ; 
 unsigned long zslDeleteRangeByScore (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zslFreeLexRange (int /*<<< orphan*/ *) ; 
 scalar_t__ zslParseLexRange (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ zslParseRange (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* zzlDeleteRangeByLex (TYPE_1__*,int /*<<< orphan*/ *,unsigned long*) ; 
 TYPE_1__* zzlDeleteRangeByRank (TYPE_1__*,long,long,unsigned long*) ; 
 TYPE_1__* zzlDeleteRangeByScore (TYPE_1__*,int /*<<< orphan*/ *,unsigned long*) ; 
 scalar_t__ zzlLength (TYPE_1__*) ; 

void zremrangeGenericCommand(client *c, int rangetype) {
    robj *key = c->argv[1];
    robj *zobj;
    int keyremoved = 0;
    unsigned long deleted = 0;
    zrangespec range;
    zlexrangespec lexrange;
    long start, end, llen;

    /* Step 1: Parse the range. */
    if (rangetype == ZRANGE_RANK) {
        if ((getLongFromObjectOrReply(c,c->argv[2],&start,NULL) != C_OK) ||
            (getLongFromObjectOrReply(c,c->argv[3],&end,NULL) != C_OK))
            return;
    } else if (rangetype == ZRANGE_SCORE) {
        if (zslParseRange(c->argv[2],c->argv[3],&range) != C_OK) {
            addReplyError(c,"min or max is not a float");
            return;
        }
    } else if (rangetype == ZRANGE_LEX) {
        if (zslParseLexRange(c->argv[2],c->argv[3],&lexrange) != C_OK) {
            addReplyError(c,"min or max not valid string range item");
            return;
        }
    }

    /* Step 2: Lookup & range sanity checks if needed. */
    if ((zobj = lookupKeyWriteOrReply(c,key,shared.czero)) == NULL ||
        checkType(c,zobj,OBJ_ZSET)) goto cleanup;

    if (rangetype == ZRANGE_RANK) {
        /* Sanitize indexes. */
        llen = zsetLength(zobj);
        if (start < 0) start = llen+start;
        if (end < 0) end = llen+end;
        if (start < 0) start = 0;

        /* Invariant: start >= 0, so this test will be true when end < 0.
         * The range is empty when start > end or start >= length. */
        if (start > end || start >= llen) {
            addReply(c,shared.czero);
            goto cleanup;
        }
        if (end >= llen) end = llen-1;
    }

    /* Step 3: Perform the range deletion operation. */
    if (zobj->encoding == OBJ_ENCODING_ZIPLIST) {
        switch(rangetype) {
        case ZRANGE_RANK:
            zobj->ptr = zzlDeleteRangeByRank(zobj->ptr,start+1,end+1,&deleted);
            break;
        case ZRANGE_SCORE:
            zobj->ptr = zzlDeleteRangeByScore(zobj->ptr,&range,&deleted);
            break;
        case ZRANGE_LEX:
            zobj->ptr = zzlDeleteRangeByLex(zobj->ptr,&lexrange,&deleted);
            break;
        }
        if (zzlLength(zobj->ptr) == 0) {
            dbDelete(c->db,key);
            keyremoved = 1;
        }
    } else if (zobj->encoding == OBJ_ENCODING_SKIPLIST) {
        zset *zs = zobj->ptr;
        switch(rangetype) {
        case ZRANGE_RANK:
            deleted = zslDeleteRangeByRank(zs->zsl,start+1,end+1,zs->dict);
            break;
        case ZRANGE_SCORE:
            deleted = zslDeleteRangeByScore(zs->zsl,&range,zs->dict);
            break;
        case ZRANGE_LEX:
            deleted = zslDeleteRangeByLex(zs->zsl,&lexrange,zs->dict);
            break;
        }
        if (htNeedsResize(zs->dict)) dictResize(zs->dict);
        if (dictSize(zs->dict) == 0) {
            dbDelete(c->db,key);
            keyremoved = 1;
        }
    } else {
        serverPanic("Unknown sorted set encoding");
    }

    /* Step 4: Notifications and reply. */
    if (deleted) {
        char *event[3] = {"zremrangebyrank","zremrangebyscore","zremrangebylex"};
        signalModifiedKey(c->db,key);
        notifyKeyspaceEvent(NOTIFY_ZSET,event[rangetype],key,c->db->id);
        if (keyremoved)
            notifyKeyspaceEvent(NOTIFY_GENERIC,"del",key,c->db->id);
    }
    server.dirty += deleted;
    addReplyLongLong(c,deleted);

cleanup:
    if (rangetype == ZRANGE_LEX) zslFreeLexRange(&lexrange);
}