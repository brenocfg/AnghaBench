#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  robj ;
typedef  int /*<<< orphan*/  rio ;
struct TYPE_16__ {int argc; TYPE_2__** argv; int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ client ;
struct TYPE_19__ {int /*<<< orphan*/  dirty; } ;
struct TYPE_18__ {int /*<<< orphan*/  ok; int /*<<< orphan*/  busykeyerr; int /*<<< orphan*/  syntaxerr; } ;
struct TYPE_17__ {int /*<<< orphan*/  ptr; } ;

/* Variables and functions */
 scalar_t__ C_ERR ; 
 scalar_t__ C_OK ; 
 long long LRU_CLOCK () ; 
 int /*<<< orphan*/  addReply (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyError (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dbAdd (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbDelete (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ getLongLongFromObjectOrReply (TYPE_1__*,TYPE_2__*,long long*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lookupKeyWrite (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ mstime () ; 
 int /*<<< orphan*/  objectSetLRUOrLFU (int /*<<< orphan*/ *,long long,long long,long long) ; 
 int /*<<< orphan*/ * rdbLoadObject (int,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int rdbLoadObjectType (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rioInitWithBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdslen (int /*<<< orphan*/ ) ; 
 TYPE_6__ server ; 
 int /*<<< orphan*/  setExpire (TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__*,long long) ; 
 TYPE_3__ shared ; 
 int /*<<< orphan*/  signalModifiedKey (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ verifyDumpPayload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void restoreCommand(client *c) {
    long long ttl, lfu_freq = -1, lru_idle = -1, lru_clock = -1;
    rio payload;
    int j, type, replace = 0, absttl = 0;
    robj *obj;

    /* Parse additional options */
    for (j = 4; j < c->argc; j++) {
        int additional = c->argc-j-1;
        if (!strcasecmp(c->argv[j]->ptr,"replace")) {
            replace = 1;
        } else if (!strcasecmp(c->argv[j]->ptr,"absttl")) {
            absttl = 1;
        } else if (!strcasecmp(c->argv[j]->ptr,"idletime") && additional >= 1 &&
                   lfu_freq == -1)
        {
            if (getLongLongFromObjectOrReply(c,c->argv[j+1],&lru_idle,NULL)
                    != C_OK) return;
            if (lru_idle < 0) {
                addReplyError(c,"Invalid IDLETIME value, must be >= 0");
                return;
            }
            lru_clock = LRU_CLOCK();
            j++; /* Consume additional arg. */
        } else if (!strcasecmp(c->argv[j]->ptr,"freq") && additional >= 1 &&
                   lru_idle == -1)
        {
            if (getLongLongFromObjectOrReply(c,c->argv[j+1],&lfu_freq,NULL)
                    != C_OK) return;
            if (lfu_freq < 0 || lfu_freq > 255) {
                addReplyError(c,"Invalid FREQ value, must be >= 0 and <= 255");
                return;
            }
            j++; /* Consume additional arg. */
        } else {
            addReply(c,shared.syntaxerr);
            return;
        }
    }

    /* Make sure this key does not already exist here... */
    if (!replace && lookupKeyWrite(c->db,c->argv[1]) != NULL) {
        addReply(c,shared.busykeyerr);
        return;
    }

    /* Check if the TTL value makes sense */
    if (getLongLongFromObjectOrReply(c,c->argv[2],&ttl,NULL) != C_OK) {
        return;
    } else if (ttl < 0) {
        addReplyError(c,"Invalid TTL value, must be >= 0");
        return;
    }

    /* Verify RDB version and data checksum. */
    if (verifyDumpPayload(c->argv[3]->ptr,sdslen(c->argv[3]->ptr)) == C_ERR)
    {
        addReplyError(c,"DUMP payload version or checksum are wrong");
        return;
    }

    rioInitWithBuffer(&payload,c->argv[3]->ptr);
    if (((type = rdbLoadObjectType(&payload)) == -1) ||
        ((obj = rdbLoadObject(type,&payload,c->argv[1])) == NULL))
    {
        addReplyError(c,"Bad data format");
        return;
    }

    /* Remove the old key if needed. */
    if (replace) dbDelete(c->db,c->argv[1]);

    /* Create the key and set the TTL if any */
    dbAdd(c->db,c->argv[1],obj);
    if (ttl) {
        if (!absttl) ttl+=mstime();
        setExpire(c,c->db,c->argv[1],ttl);
    }
    objectSetLRUOrLFU(obj,lfu_freq,lru_idle,lru_clock);
    signalModifiedKey(c->db,c->argv[1]);
    addReply(c,shared.ok);
    server.dirty++;
}