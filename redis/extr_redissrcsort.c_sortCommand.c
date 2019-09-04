#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_85__   TYPE_9__ ;
typedef  struct TYPE_84__   TYPE_8__ ;
typedef  struct TYPE_83__   TYPE_7__ ;
typedef  struct TYPE_82__   TYPE_6__ ;
typedef  struct TYPE_81__   TYPE_5__ ;
typedef  struct TYPE_80__   TYPE_4__ ;
typedef  struct TYPE_79__   TYPE_3__ ;
typedef  struct TYPE_78__   TYPE_32__ ;
typedef  struct TYPE_77__   TYPE_2__ ;
typedef  struct TYPE_76__   TYPE_24__ ;
typedef  struct TYPE_75__   TYPE_22__ ;
typedef  struct TYPE_74__   TYPE_1__ ;
typedef  struct TYPE_73__   TYPE_12__ ;
typedef  struct TYPE_72__   TYPE_11__ ;
typedef  struct TYPE_71__   TYPE_10__ ;

/* Type definitions */
struct TYPE_81__ {char* ele; TYPE_3__* level; struct TYPE_81__* backward; } ;
typedef  TYPE_5__ zskiplistNode ;
struct TYPE_82__ {TYPE_2__* header; TYPE_5__* tail; } ;
typedef  TYPE_6__ zskiplist ;
struct TYPE_83__ {int /*<<< orphan*/ * dict; TYPE_6__* zsl; } ;
typedef  TYPE_7__ zset ;
typedef  int /*<<< orphan*/  setTypeIterator ;
typedef  char* sds ;
struct TYPE_84__ {int type; scalar_t__ encoding; TYPE_7__* ptr; } ;
typedef  TYPE_8__ robj ;
struct TYPE_85__ {scalar_t__ type; TYPE_8__* pattern; } ;
typedef  TYPE_9__ redisSortOperation ;
struct TYPE_80__ {long score; TYPE_8__* cmpobj; } ;
struct TYPE_71__ {TYPE_4__ u; TYPE_8__* obj; } ;
typedef  TYPE_10__ redisSortObject ;
typedef  int /*<<< orphan*/  listTypeIterator ;
typedef  int /*<<< orphan*/  listTypeEntry ;
struct TYPE_72__ {TYPE_9__* value; } ;
typedef  TYPE_11__ listNode ;
typedef  int /*<<< orphan*/  listIter ;
typedef  int /*<<< orphan*/  list ;
typedef  int /*<<< orphan*/  dictIterator ;
typedef  int /*<<< orphan*/  dictEntry ;
typedef  int /*<<< orphan*/  dict ;
struct TYPE_73__ {int argc; int flags; TYPE_22__* db; TYPE_8__** argv; } ;
typedef  TYPE_12__ client ;
struct TYPE_79__ {TYPE_5__* forward; } ;
struct TYPE_78__ {int sort_desc; int sort_alpha; int sort_bypattern; int sort_store; scalar_t__ dirty; scalar_t__ cluster_enabled; } ;
struct TYPE_77__ {TYPE_1__* level; } ;
struct TYPE_76__ {int /*<<< orphan*/  wrongtypeerr; int /*<<< orphan*/  syntaxerr; } ;
struct TYPE_75__ {int /*<<< orphan*/  id; } ;
struct TYPE_74__ {TYPE_5__* forward; } ;

/* Variables and functions */
 int CLIENT_LUA ; 
 scalar_t__ C_OK ; 
 scalar_t__ ERANGE ; 
 int /*<<< orphan*/  LIST_HEAD ; 
 int /*<<< orphan*/  LIST_TAIL ; 
 int /*<<< orphan*/  NOTIFY_GENERIC ; 
 int /*<<< orphan*/  NOTIFY_LIST ; 
 scalar_t__ OBJ_ENCODING_INT ; 
 int /*<<< orphan*/  OBJ_ENCODING_SKIPLIST ; 
#define  OBJ_LIST 130 
#define  OBJ_SET 129 
 int /*<<< orphan*/  OBJ_STRING ; 
#define  OBJ_ZSET 128 
 scalar_t__ SORT_OP_GET ; 
 int /*<<< orphan*/  addReply (TYPE_12__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyArrayLen (TYPE_12__*,unsigned int) ; 
 int /*<<< orphan*/  addReplyBulk (TYPE_12__*,TYPE_8__*) ; 
 int /*<<< orphan*/  addReplyError (TYPE_12__*,char*) ; 
 int /*<<< orphan*/  addReplyLongLong (TYPE_12__*,unsigned int) ; 
 int /*<<< orphan*/  addReplyNull (TYPE_12__*) ; 
 TYPE_8__* createObject (int /*<<< orphan*/ ,char*) ; 
 TYPE_8__* createQuicklistObject () ; 
 int /*<<< orphan*/  createSortOperation (scalar_t__,TYPE_8__*) ; 
 void* createStringObject (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ dbDelete (TYPE_22__*,TYPE_8__*) ; 
 int /*<<< orphan*/  decrRefCount (TYPE_8__*) ; 
 int /*<<< orphan*/ * dictGetIterator (int /*<<< orphan*/ *) ; 
 char* dictGetKey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictReleaseIterator (int /*<<< orphan*/ *) ; 
 void* dictSize (int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 TYPE_8__* getDecodedObject (TYPE_8__*) ; 
 scalar_t__ getLongFromObjectOrReply (TYPE_12__*,TYPE_8__*,long*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  incrRefCount (TYPE_8__*) ; 
 scalar_t__ isnan (long) ; 
 int /*<<< orphan*/  listAddNodeTail (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * listCreate () ; 
 TYPE_11__* listNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRewind (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listSetFreeMethod (int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (TYPE_10__*)) ; 
 void* listTypeGet (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * listTypeInitIterator (TYPE_8__*,long,int /*<<< orphan*/ ) ; 
 long listTypeLength (TYPE_8__*) ; 
 scalar_t__ listTypeNext (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listTypePush (TYPE_8__*,TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listTypeReleaseIterator (int /*<<< orphan*/ *) ; 
 TYPE_8__* lookupKeyByPattern (TYPE_22__*,TYPE_8__*,TYPE_8__*,int /*<<< orphan*/ ) ; 
 TYPE_8__* lookupKeyRead (TYPE_22__*,TYPE_8__*) ; 
 TYPE_8__* lookupKeyWrite (TYPE_22__*,TYPE_8__*) ; 
 int /*<<< orphan*/  notifyKeyspaceEvent (int /*<<< orphan*/ ,char*,TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pqsort (TYPE_10__*,int,int,int /*<<< orphan*/ ,long,long) ; 
 int /*<<< orphan*/  qsort (TYPE_10__*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sdsEncodedObject (TYPE_8__*) ; 
 int /*<<< orphan*/  sdslen (char*) ; 
 TYPE_32__ server ; 
 int /*<<< orphan*/  serverAssertWithInfo (TYPE_12__*,TYPE_8__*,int) ; 
 int /*<<< orphan*/  serverPanic (char*) ; 
 int /*<<< orphan*/  setKey (TYPE_22__*,TYPE_8__*,TYPE_8__*) ; 
 int /*<<< orphan*/ * setTypeInitIterator (TYPE_8__*) ; 
 char* setTypeNextObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setTypeReleaseIterator (int /*<<< orphan*/ *) ; 
 int setTypeSize (TYPE_8__*) ; 
 TYPE_24__ shared ; 
 int /*<<< orphan*/  signalModifiedKey (TYPE_22__*,TYPE_8__*) ; 
 int /*<<< orphan*/  sortCompare ; 
 int /*<<< orphan*/  strcasecmp (TYPE_7__*,char*) ; 
 int /*<<< orphan*/ * strchr (TYPE_7__*,char) ; 
 long strtod (TYPE_7__*,char**) ; 
 int /*<<< orphan*/  zfree (TYPE_10__*) ; 
 TYPE_10__* zmalloc (int) ; 
 int /*<<< orphan*/  zsetConvert (TYPE_8__*,int /*<<< orphan*/ ) ; 
 TYPE_5__* zslGetElementByRank (TYPE_6__*,long) ; 

void sortCommand(client *c) {
    list *operations;
    unsigned int outputlen = 0;
    int desc = 0, alpha = 0;
    long limit_start = 0, limit_count = -1, start, end;
    int j, dontsort = 0, vectorlen;
    int getop = 0; /* GET operation counter */
    int int_conversion_error = 0;
    int syntax_error = 0;
    robj *sortval, *sortby = NULL, *storekey = NULL;
    redisSortObject *vector; /* Resulting vector to sort */

    /* Create a list of operations to perform for every sorted element.
     * Operations can be GET */
    operations = listCreate();
    listSetFreeMethod(operations,zfree);
    j = 2; /* options start at argv[2] */

    /* The SORT command has an SQL-alike syntax, parse it */
    while(j < c->argc) {
        int leftargs = c->argc-j-1;
        if (!strcasecmp(c->argv[j]->ptr,"asc")) {
            desc = 0;
        } else if (!strcasecmp(c->argv[j]->ptr,"desc")) {
            desc = 1;
        } else if (!strcasecmp(c->argv[j]->ptr,"alpha")) {
            alpha = 1;
        } else if (!strcasecmp(c->argv[j]->ptr,"limit") && leftargs >= 2) {
            if ((getLongFromObjectOrReply(c, c->argv[j+1], &limit_start, NULL)
                 != C_OK) ||
                (getLongFromObjectOrReply(c, c->argv[j+2], &limit_count, NULL)
                 != C_OK))
            {
                syntax_error++;
                break;
            }
            j+=2;
        } else if (!strcasecmp(c->argv[j]->ptr,"store") && leftargs >= 1) {
            storekey = c->argv[j+1];
            j++;
        } else if (!strcasecmp(c->argv[j]->ptr,"by") && leftargs >= 1) {
            sortby = c->argv[j+1];
            /* If the BY pattern does not contain '*', i.e. it is constant,
             * we don't need to sort nor to lookup the weight keys. */
            if (strchr(c->argv[j+1]->ptr,'*') == NULL) {
                dontsort = 1;
            } else {
                /* If BY is specified with a real patter, we can't accept
                 * it in cluster mode. */
                if (server.cluster_enabled) {
                    addReplyError(c,"BY option of SORT denied in Cluster mode.");
                    syntax_error++;
                    break;
                }
            }
            j++;
        } else if (!strcasecmp(c->argv[j]->ptr,"get") && leftargs >= 1) {
            if (server.cluster_enabled) {
                addReplyError(c,"GET option of SORT denied in Cluster mode.");
                syntax_error++;
                break;
            }
            listAddNodeTail(operations,createSortOperation(
                SORT_OP_GET,c->argv[j+1]));
            getop++;
            j++;
        } else {
            addReply(c,shared.syntaxerr);
            syntax_error++;
            break;
        }
        j++;
    }

    /* Handle syntax errors set during options parsing. */
    if (syntax_error) {
        listRelease(operations);
        return;
    }

    /* Lookup the key to sort. It must be of the right types */
    if (storekey)
        sortval = lookupKeyRead(c->db,c->argv[1]);
    else
        sortval = lookupKeyWrite(c->db,c->argv[1]);
    if (sortval && sortval->type != OBJ_SET &&
                   sortval->type != OBJ_LIST &&
                   sortval->type != OBJ_ZSET)
    {
        listRelease(operations);
        addReply(c,shared.wrongtypeerr);
        return;
    }

    /* Now we need to protect sortval incrementing its count, in the future
     * SORT may have options able to overwrite/delete keys during the sorting
     * and the sorted key itself may get destroyed */
    if (sortval)
        incrRefCount(sortval);
    else
        sortval = createQuicklistObject();


    /* When sorting a set with no sort specified, we must sort the output
     * so the result is consistent across scripting and replication.
     *
     * The other types (list, sorted set) will retain their native order
     * even if no sort order is requested, so they remain stable across
     * scripting and replication. */
    if (dontsort &&
        sortval->type == OBJ_SET &&
        (storekey || c->flags & CLIENT_LUA))
    {
        /* Force ALPHA sorting */
        dontsort = 0;
        alpha = 1;
        sortby = NULL;
    }

    /* Destructively convert encoded sorted sets for SORT. */
    if (sortval->type == OBJ_ZSET)
        zsetConvert(sortval, OBJ_ENCODING_SKIPLIST);

    /* Objtain the length of the object to sort. */
    switch(sortval->type) {
    case OBJ_LIST: vectorlen = listTypeLength(sortval); break;
    case OBJ_SET: vectorlen =  setTypeSize(sortval); break;
    case OBJ_ZSET: vectorlen = dictSize(((zset*)sortval->ptr)->dict); break;
    default: vectorlen = 0; serverPanic("Bad SORT type"); /* Avoid GCC warning */
    }

    /* Perform LIMIT start,count sanity checking. */
    start = (limit_start < 0) ? 0 : limit_start;
    end = (limit_count < 0) ? vectorlen-1 : start+limit_count-1;
    if (start >= vectorlen) {
        start = vectorlen-1;
        end = vectorlen-2;
    }
    if (end >= vectorlen) end = vectorlen-1;

    /* Whenever possible, we load elements into the output array in a more
     * direct way. This is possible if:
     *
     * 1) The object to sort is a sorted set or a list (internally sorted).
     * 2) There is nothing to sort as dontsort is true (BY <constant string>).
     *
     * In this special case, if we have a LIMIT option that actually reduces
     * the number of elements to fetch, we also optimize to just load the
     * range we are interested in and allocating a vector that is big enough
     * for the selected range length. */
    if ((sortval->type == OBJ_ZSET || sortval->type == OBJ_LIST) &&
        dontsort &&
        (start != 0 || end != vectorlen-1))
    {
        vectorlen = end-start+1;
    }

    /* Load the sorting vector with all the objects to sort */
    vector = zmalloc(sizeof(redisSortObject)*vectorlen);
    j = 0;

    if (sortval->type == OBJ_LIST && dontsort) {
        /* Special handling for a list, if 'dontsort' is true.
         * This makes sure we return elements in the list original
         * ordering, accordingly to DESC / ASC options.
         *
         * Note that in this case we also handle LIMIT here in a direct
         * way, just getting the required range, as an optimization. */
        if (end >= start) {
            listTypeIterator *li;
            listTypeEntry entry;
            li = listTypeInitIterator(sortval,
                    desc ? (long)(listTypeLength(sortval) - start - 1) : start,
                    desc ? LIST_HEAD : LIST_TAIL);

            while(j < vectorlen && listTypeNext(li,&entry)) {
                vector[j].obj = listTypeGet(&entry);
                vector[j].u.score = 0;
                vector[j].u.cmpobj = NULL;
                j++;
            }
            listTypeReleaseIterator(li);
            /* Fix start/end: output code is not aware of this optimization. */
            end -= start;
            start = 0;
        }
    } else if (sortval->type == OBJ_LIST) {
        listTypeIterator *li = listTypeInitIterator(sortval,0,LIST_TAIL);
        listTypeEntry entry;
        while(listTypeNext(li,&entry)) {
            vector[j].obj = listTypeGet(&entry);
            vector[j].u.score = 0;
            vector[j].u.cmpobj = NULL;
            j++;
        }
        listTypeReleaseIterator(li);
    } else if (sortval->type == OBJ_SET) {
        setTypeIterator *si = setTypeInitIterator(sortval);
        sds sdsele;
        while((sdsele = setTypeNextObject(si)) != NULL) {
            vector[j].obj = createObject(OBJ_STRING,sdsele);
            vector[j].u.score = 0;
            vector[j].u.cmpobj = NULL;
            j++;
        }
        setTypeReleaseIterator(si);
    } else if (sortval->type == OBJ_ZSET && dontsort) {
        /* Special handling for a sorted set, if 'dontsort' is true.
         * This makes sure we return elements in the sorted set original
         * ordering, accordingly to DESC / ASC options.
         *
         * Note that in this case we also handle LIMIT here in a direct
         * way, just getting the required range, as an optimization. */

        zset *zs = sortval->ptr;
        zskiplist *zsl = zs->zsl;
        zskiplistNode *ln;
        sds sdsele;
        int rangelen = vectorlen;

        /* Check if starting point is trivial, before doing log(N) lookup. */
        if (desc) {
            long zsetlen = dictSize(((zset*)sortval->ptr)->dict);

            ln = zsl->tail;
            if (start > 0)
                ln = zslGetElementByRank(zsl,zsetlen-start);
        } else {
            ln = zsl->header->level[0].forward;
            if (start > 0)
                ln = zslGetElementByRank(zsl,start+1);
        }

        while(rangelen--) {
            serverAssertWithInfo(c,sortval,ln != NULL);
            sdsele = ln->ele;
            vector[j].obj = createStringObject(sdsele,sdslen(sdsele));
            vector[j].u.score = 0;
            vector[j].u.cmpobj = NULL;
            j++;
            ln = desc ? ln->backward : ln->level[0].forward;
        }
        /* Fix start/end: output code is not aware of this optimization. */
        end -= start;
        start = 0;
    } else if (sortval->type == OBJ_ZSET) {
        dict *set = ((zset*)sortval->ptr)->dict;
        dictIterator *di;
        dictEntry *setele;
        sds sdsele;
        di = dictGetIterator(set);
        while((setele = dictNext(di)) != NULL) {
            sdsele =  dictGetKey(setele);
            vector[j].obj = createStringObject(sdsele,sdslen(sdsele));
            vector[j].u.score = 0;
            vector[j].u.cmpobj = NULL;
            j++;
        }
        dictReleaseIterator(di);
    } else {
        serverPanic("Unknown type");
    }
    serverAssertWithInfo(c,sortval,j == vectorlen);

    /* Now it's time to load the right scores in the sorting vector */
    if (!dontsort) {
        for (j = 0; j < vectorlen; j++) {
            robj *byval;
            if (sortby) {
                /* lookup value to sort by */
                byval = lookupKeyByPattern(c->db,sortby,vector[j].obj,storekey!=NULL);
                if (!byval) continue;
            } else {
                /* use object itself to sort by */
                byval = vector[j].obj;
            }

            if (alpha) {
                if (sortby) vector[j].u.cmpobj = getDecodedObject(byval);
            } else {
                if (sdsEncodedObject(byval)) {
                    char *eptr;

                    vector[j].u.score = strtod(byval->ptr,&eptr);
                    if (eptr[0] != '\0' || errno == ERANGE ||
                        isnan(vector[j].u.score))
                    {
                        int_conversion_error = 1;
                    }
                } else if (byval->encoding == OBJ_ENCODING_INT) {
                    /* Don't need to decode the object if it's
                     * integer-encoded (the only encoding supported) so
                     * far. We can just cast it */
                    vector[j].u.score = (long)byval->ptr;
                } else {
                    serverAssertWithInfo(c,sortval,1 != 1);
                }
            }

            /* when the object was retrieved using lookupKeyByPattern,
             * its refcount needs to be decreased. */
            if (sortby) {
                decrRefCount(byval);
            }
        }

        server.sort_desc = desc;
        server.sort_alpha = alpha;
        server.sort_bypattern = sortby ? 1 : 0;
        server.sort_store = storekey ? 1 : 0;
        if (sortby && (start != 0 || end != vectorlen-1))
            pqsort(vector,vectorlen,sizeof(redisSortObject),sortCompare, start,end);
        else
            qsort(vector,vectorlen,sizeof(redisSortObject),sortCompare);
    }

    /* Send command output to the output buffer, performing the specified
     * GET/DEL/INCR/DECR operations if any. */
    outputlen = getop ? getop*(end-start+1) : end-start+1;
    if (int_conversion_error) {
        addReplyError(c,"One or more scores can't be converted into double");
    } else if (storekey == NULL) {
        /* STORE option not specified, sent the sorting result to client */
        addReplyArrayLen(c,outputlen);
        for (j = start; j <= end; j++) {
            listNode *ln;
            listIter li;

            if (!getop) addReplyBulk(c,vector[j].obj);
            listRewind(operations,&li);
            while((ln = listNext(&li))) {
                redisSortOperation *sop = ln->value;
                robj *val = lookupKeyByPattern(c->db,sop->pattern,
                    vector[j].obj,storekey!=NULL);

                if (sop->type == SORT_OP_GET) {
                    if (!val) {
                        addReplyNull(c);
                    } else {
                        addReplyBulk(c,val);
                        decrRefCount(val);
                    }
                } else {
                    /* Always fails */
                    serverAssertWithInfo(c,sortval,sop->type == SORT_OP_GET);
                }
            }
        }
    } else {
        robj *sobj = createQuicklistObject();

        /* STORE option specified, set the sorting result as a List object */
        for (j = start; j <= end; j++) {
            listNode *ln;
            listIter li;

            if (!getop) {
                listTypePush(sobj,vector[j].obj,LIST_TAIL);
            } else {
                listRewind(operations,&li);
                while((ln = listNext(&li))) {
                    redisSortOperation *sop = ln->value;
                    robj *val = lookupKeyByPattern(c->db,sop->pattern,
                        vector[j].obj,storekey!=NULL);

                    if (sop->type == SORT_OP_GET) {
                        if (!val) val = createStringObject("",0);

                        /* listTypePush does an incrRefCount, so we should take care
                         * care of the incremented refcount caused by either
                         * lookupKeyByPattern or createStringObject("",0) */
                        listTypePush(sobj,val,LIST_TAIL);
                        decrRefCount(val);
                    } else {
                        /* Always fails */
                        serverAssertWithInfo(c,sortval,sop->type == SORT_OP_GET);
                    }
                }
            }
        }
        if (outputlen) {
            setKey(c->db,storekey,sobj);
            notifyKeyspaceEvent(NOTIFY_LIST,"sortstore",storekey,
                                c->db->id);
            server.dirty += outputlen;
        } else if (dbDelete(c->db,storekey)) {
            signalModifiedKey(c->db,storekey);
            notifyKeyspaceEvent(NOTIFY_GENERIC,"del",storekey,c->db->id);
            server.dirty++;
        }
        decrRefCount(sobj);
        addReplyLongLong(c,outputlen);
    }

    /* Cleanup */
    for (j = 0; j < vectorlen; j++)
        decrRefCount(vector[j].obj);

    decrRefCount(sortval);
    listRelease(operations);
    for (j = 0; j < vectorlen; j++) {
        if (alpha && vector[j].u.cmpobj)
            decrRefCount(vector[j].u.cmpobj);
    }
    zfree(vector);
}