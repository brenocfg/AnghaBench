#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_69__   TYPE_8__ ;
typedef  struct TYPE_68__   TYPE_7__ ;
typedef  struct TYPE_67__   TYPE_6__ ;
typedef  struct TYPE_66__   TYPE_5__ ;
typedef  struct TYPE_65__   TYPE_4__ ;
typedef  struct TYPE_64__   TYPE_3__ ;
typedef  struct TYPE_63__   TYPE_35__ ;
typedef  struct TYPE_62__   TYPE_2__ ;
typedef  struct TYPE_61__   TYPE_29__ ;
typedef  struct TYPE_60__   TYPE_28__ ;
typedef  struct TYPE_59__   TYPE_26__ ;
typedef  struct TYPE_58__   TYPE_21__ ;
typedef  struct TYPE_57__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_62__ {int /*<<< orphan*/  score; } ;
typedef  TYPE_2__ zskiplistNode ;
struct TYPE_64__ {double score; } ;
typedef  TYPE_3__ zsetopval ;
struct TYPE_65__ {scalar_t__ type; double weight; TYPE_6__* subject; int /*<<< orphan*/  encoding; } ;
typedef  TYPE_4__ zsetopsrc ;
struct TYPE_66__ {TYPE_21__* zsl; int /*<<< orphan*/ * dict; } ;
typedef  TYPE_5__ zset ;
typedef  int /*<<< orphan*/  sds ;
struct TYPE_67__ {scalar_t__ type; TYPE_5__* ptr; int /*<<< orphan*/  encoding; } ;
typedef  TYPE_6__ robj ;
typedef  int /*<<< orphan*/  dictIterator ;
struct TYPE_57__ {double d; } ;
struct TYPE_68__ {TYPE_1__ v; } ;
typedef  TYPE_7__ dictEntry ;
typedef  int /*<<< orphan*/  dict ;
struct TYPE_69__ {int argc; TYPE_26__* db; TYPE_35__** argv; } ;
typedef  TYPE_8__ client ;
struct TYPE_63__ {int /*<<< orphan*/  ptr; } ;
struct TYPE_61__ {int /*<<< orphan*/  dirty; } ;
struct TYPE_60__ {int /*<<< orphan*/  czero; int /*<<< orphan*/  syntaxerr; int /*<<< orphan*/  wrongtypeerr; } ;
struct TYPE_59__ {int /*<<< orphan*/  id; } ;
struct TYPE_58__ {scalar_t__ length; } ;

/* Variables and functions */
 scalar_t__ C_OK ; 
 int /*<<< orphan*/  NOTIFY_GENERIC ; 
 int /*<<< orphan*/  NOTIFY_ZSET ; 
 scalar_t__ OBJ_SET ; 
 scalar_t__ OBJ_ZSET ; 
 int REDIS_AGGR_MAX ; 
 int REDIS_AGGR_MIN ; 
 int REDIS_AGGR_SUM ; 
 int SET_OP_INTER ; 
 int SET_OP_UNION ; 
 int /*<<< orphan*/  addReply (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyError (TYPE_8__*,char*) ; 
 int /*<<< orphan*/  addReplyLongLong (TYPE_8__*,int /*<<< orphan*/ ) ; 
 TYPE_6__* createZsetObject () ; 
 int /*<<< orphan*/  dbAdd (TYPE_26__*,TYPE_6__*,TYPE_6__*) ; 
 scalar_t__ dbDelete (TYPE_26__*,TYPE_6__*) ; 
 int /*<<< orphan*/  decrRefCount (TYPE_6__*) ; 
 int /*<<< orphan*/  dictAdd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_7__* dictAddRaw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_7__**) ; 
 int /*<<< orphan*/ * dictCreate (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictExpand (int /*<<< orphan*/ *,scalar_t__) ; 
 double dictGetDoubleVal (TYPE_7__*) ; 
 int /*<<< orphan*/ * dictGetIterator (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictGetKey (TYPE_7__*) ; 
 TYPE_7__* dictNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictReleaseIterator (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictSetDoubleVal (TYPE_7__*,double) ; 
 int /*<<< orphan*/  dictSetKey (int /*<<< orphan*/ *,TYPE_7__*,int /*<<< orphan*/ ) ; 
 scalar_t__ dictSize (int /*<<< orphan*/ *) ; 
 scalar_t__ getDoubleFromObjectOrReply (TYPE_8__*,TYPE_35__*,double*,char*) ; 
 scalar_t__ getLongFromObjectOrReply (TYPE_8__*,TYPE_35__*,long*,int /*<<< orphan*/ *) ; 
 scalar_t__ isnan (double) ; 
 TYPE_6__* lookupKeyWrite (TYPE_26__*,TYPE_35__*) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  notifyKeyspaceEvent (int /*<<< orphan*/ ,char*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qsort (TYPE_4__*,long,int,int /*<<< orphan*/ ) ; 
 size_t sdslen (int /*<<< orphan*/ ) ; 
 TYPE_29__ server ; 
 int /*<<< orphan*/  serverPanic (char*) ; 
 int /*<<< orphan*/  setAccumulatorDictType ; 
 TYPE_28__ shared ; 
 int /*<<< orphan*/  signalModifiedKey (TYPE_26__*,TYPE_6__*) ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,char*) ; 
 TYPE_4__* zcalloc (int) ; 
 int /*<<< orphan*/  zfree (TYPE_4__*) ; 
 int /*<<< orphan*/  zsetConvertToZiplistIfNeeded (TYPE_6__*,size_t) ; 
 int /*<<< orphan*/  zsetLength (TYPE_6__*) ; 
 TYPE_2__* zslInsert (TYPE_21__*,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zuiClearIterator (TYPE_4__*) ; 
 int /*<<< orphan*/  zuiCompareByCardinality ; 
 scalar_t__ zuiFind (TYPE_4__*,TYPE_3__*,double*) ; 
 int /*<<< orphan*/  zuiInitIterator (TYPE_4__*) ; 
 scalar_t__ zuiLength (TYPE_4__*) ; 
 int /*<<< orphan*/  zuiNewSdsFromValue (TYPE_3__*) ; 
 scalar_t__ zuiNext (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  zuiSdsFromValue (TYPE_3__*) ; 
 int /*<<< orphan*/  zunionInterAggregate (double*,double,int) ; 

void zunionInterGenericCommand(client *c, robj *dstkey, int op) {
    int i, j;
    long setnum;
    int aggregate = REDIS_AGGR_SUM;
    zsetopsrc *src;
    zsetopval zval;
    sds tmp;
    size_t maxelelen = 0;
    robj *dstobj;
    zset *dstzset;
    zskiplistNode *znode;
    int touched = 0;

    /* expect setnum input keys to be given */
    if ((getLongFromObjectOrReply(c, c->argv[2], &setnum, NULL) != C_OK))
        return;

    if (setnum < 1) {
        addReplyError(c,
            "at least 1 input key is needed for ZUNIONSTORE/ZINTERSTORE");
        return;
    }

    /* test if the expected number of keys would overflow */
    if (setnum > c->argc-3) {
        addReply(c,shared.syntaxerr);
        return;
    }

    /* read keys to be used for input */
    src = zcalloc(sizeof(zsetopsrc) * setnum);
    for (i = 0, j = 3; i < setnum; i++, j++) {
        robj *obj = lookupKeyWrite(c->db,c->argv[j]);
        if (obj != NULL) {
            if (obj->type != OBJ_ZSET && obj->type != OBJ_SET) {
                zfree(src);
                addReply(c,shared.wrongtypeerr);
                return;
            }

            src[i].subject = obj;
            src[i].type = obj->type;
            src[i].encoding = obj->encoding;
        } else {
            src[i].subject = NULL;
        }

        /* Default all weights to 1. */
        src[i].weight = 1.0;
    }

    /* parse optional extra arguments */
    if (j < c->argc) {
        int remaining = c->argc - j;

        while (remaining) {
            if (remaining >= (setnum + 1) &&
                !strcasecmp(c->argv[j]->ptr,"weights"))
            {
                j++; remaining--;
                for (i = 0; i < setnum; i++, j++, remaining--) {
                    if (getDoubleFromObjectOrReply(c,c->argv[j],&src[i].weight,
                            "weight value is not a float") != C_OK)
                    {
                        zfree(src);
                        return;
                    }
                }
            } else if (remaining >= 2 &&
                       !strcasecmp(c->argv[j]->ptr,"aggregate"))
            {
                j++; remaining--;
                if (!strcasecmp(c->argv[j]->ptr,"sum")) {
                    aggregate = REDIS_AGGR_SUM;
                } else if (!strcasecmp(c->argv[j]->ptr,"min")) {
                    aggregate = REDIS_AGGR_MIN;
                } else if (!strcasecmp(c->argv[j]->ptr,"max")) {
                    aggregate = REDIS_AGGR_MAX;
                } else {
                    zfree(src);
                    addReply(c,shared.syntaxerr);
                    return;
                }
                j++; remaining--;
            } else {
                zfree(src);
                addReply(c,shared.syntaxerr);
                return;
            }
        }
    }

    /* sort sets from the smallest to largest, this will improve our
     * algorithm's performance */
    qsort(src,setnum,sizeof(zsetopsrc),zuiCompareByCardinality);

    dstobj = createZsetObject();
    dstzset = dstobj->ptr;
    memset(&zval, 0, sizeof(zval));

    if (op == SET_OP_INTER) {
        /* Skip everything if the smallest input is empty. */
        if (zuiLength(&src[0]) > 0) {
            /* Precondition: as src[0] is non-empty and the inputs are ordered
             * by size, all src[i > 0] are non-empty too. */
            zuiInitIterator(&src[0]);
            while (zuiNext(&src[0],&zval)) {
                double score, value;

                score = src[0].weight * zval.score;
                if (isnan(score)) score = 0;

                for (j = 1; j < setnum; j++) {
                    /* It is not safe to access the zset we are
                     * iterating, so explicitly check for equal object. */
                    if (src[j].subject == src[0].subject) {
                        value = zval.score*src[j].weight;
                        zunionInterAggregate(&score,value,aggregate);
                    } else if (zuiFind(&src[j],&zval,&value)) {
                        value *= src[j].weight;
                        zunionInterAggregate(&score,value,aggregate);
                    } else {
                        break;
                    }
                }

                /* Only continue when present in every input. */
                if (j == setnum) {
                    tmp = zuiNewSdsFromValue(&zval);
                    znode = zslInsert(dstzset->zsl,score,tmp);
                    dictAdd(dstzset->dict,tmp,&znode->score);
                    if (sdslen(tmp) > maxelelen) maxelelen = sdslen(tmp);
                }
            }
            zuiClearIterator(&src[0]);
        }
    } else if (op == SET_OP_UNION) {
        dict *accumulator = dictCreate(&setAccumulatorDictType,NULL);
        dictIterator *di;
        dictEntry *de, *existing;
        double score;

        if (setnum) {
            /* Our union is at least as large as the largest set.
             * Resize the dictionary ASAP to avoid useless rehashing. */
            dictExpand(accumulator,zuiLength(&src[setnum-1]));
        }

        /* Step 1: Create a dictionary of elements -> aggregated-scores
         * by iterating one sorted set after the other. */
        for (i = 0; i < setnum; i++) {
            if (zuiLength(&src[i]) == 0) continue;

            zuiInitIterator(&src[i]);
            while (zuiNext(&src[i],&zval)) {
                /* Initialize value */
                score = src[i].weight * zval.score;
                if (isnan(score)) score = 0;

                /* Search for this element in the accumulating dictionary. */
                de = dictAddRaw(accumulator,zuiSdsFromValue(&zval),&existing);
                /* If we don't have it, we need to create a new entry. */
                if (!existing) {
                    tmp = zuiNewSdsFromValue(&zval);
                    /* Remember the longest single element encountered,
                     * to understand if it's possible to convert to ziplist
                     * at the end. */
                     if (sdslen(tmp) > maxelelen) maxelelen = sdslen(tmp);
                    /* Update the element with its initial score. */
                    dictSetKey(accumulator, de, tmp);
                    dictSetDoubleVal(de,score);
                } else {
                    /* Update the score with the score of the new instance
                     * of the element found in the current sorted set.
                     *
                     * Here we access directly the dictEntry double
                     * value inside the union as it is a big speedup
                     * compared to using the getDouble/setDouble API. */
                    zunionInterAggregate(&existing->v.d,score,aggregate);
                }
            }
            zuiClearIterator(&src[i]);
        }

        /* Step 2: convert the dictionary into the final sorted set. */
        di = dictGetIterator(accumulator);

        /* We now are aware of the final size of the resulting sorted set,
         * let's resize the dictionary embedded inside the sorted set to the
         * right size, in order to save rehashing time. */
        dictExpand(dstzset->dict,dictSize(accumulator));

        while((de = dictNext(di)) != NULL) {
            sds ele = dictGetKey(de);
            score = dictGetDoubleVal(de);
            znode = zslInsert(dstzset->zsl,score,ele);
            dictAdd(dstzset->dict,ele,&znode->score);
        }
        dictReleaseIterator(di);
        dictRelease(accumulator);
    } else {
        serverPanic("Unknown operator");
    }

    if (dbDelete(c->db,dstkey))
        touched = 1;
    if (dstzset->zsl->length) {
        zsetConvertToZiplistIfNeeded(dstobj,maxelelen);
        dbAdd(c->db,dstkey,dstobj);
        addReplyLongLong(c,zsetLength(dstobj));
        signalModifiedKey(c->db,dstkey);
        notifyKeyspaceEvent(NOTIFY_ZSET,
            (op == SET_OP_UNION) ? "zunionstore" : "zinterstore",
            dstkey,c->db->id);
        server.dirty++;
    } else {
        decrRefCount(dstobj);
        addReply(c,shared.czero);
        if (touched) {
            signalModifiedKey(c->db,dstkey);
            notifyKeyspaceEvent(NOTIFY_GENERIC,"del",dstkey,c->db->id);
            server.dirty++;
        }
    }
    zfree(src);
}