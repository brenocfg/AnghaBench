#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;
typedef  struct TYPE_26__   TYPE_15__ ;
typedef  struct TYPE_25__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  streamID ;
typedef  int /*<<< orphan*/  stream ;
struct TYPE_27__ {int /*<<< orphan*/ * ptr; } ;
typedef  TYPE_1__ robj ;
struct TYPE_28__ {int argc; TYPE_6__** argv; TYPE_11__* db; } ;
typedef  TYPE_2__ client ;
struct TYPE_29__ {char* ptr; } ;
struct TYPE_26__ {scalar_t__* blocked_clients_by_type; int /*<<< orphan*/  dirty; } ;
struct TYPE_25__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 size_t BLOCKED_STREAM ; 
 scalar_t__ C_ERR ; 
 scalar_t__ C_OK ; 
 int /*<<< orphan*/  NOTIFY_STREAM ; 
 int /*<<< orphan*/  addReplyError (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  addReplyStreamID (TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* createObjectFromStreamID (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decrRefCount (TYPE_1__*) ; 
 scalar_t__ getLongLongFromObjectOrReply (TYPE_2__*,TYPE_6__*,long long*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  notifyKeyspaceEvent (int /*<<< orphan*/ ,char*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rewriteClientCommandArgument (TYPE_2__*,int,TYPE_1__*) ; 
 TYPE_15__ server ; 
 int /*<<< orphan*/  signalKeyAsReady (TYPE_11__*,TYPE_6__*) ; 
 int /*<<< orphan*/  signalModifiedKey (TYPE_11__*,TYPE_6__*) ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 
 scalar_t__ streamAppendItem (int /*<<< orphan*/ *,TYPE_6__**,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ streamParseStrictIDOrReply (TYPE_2__*,TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  streamRewriteApproxMaxlen (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ streamTrimByLength (int /*<<< orphan*/ *,long long,int) ; 
 TYPE_1__* streamTypeLookupWriteOrCreate (TYPE_2__*,TYPE_6__*) ; 

void xaddCommand(client *c) {
    streamID id;
    int id_given = 0; /* Was an ID different than "*" specified? */
    long long maxlen = -1;  /* If left to -1 no trimming is performed. */
    int approx_maxlen = 0;  /* If 1 only delete whole radix tree nodes, so
                               the maxium length is not applied verbatim. */
    int maxlen_arg_idx = 0; /* Index of the count in MAXLEN, for rewriting. */

    /* Parse options. */
    int i = 2; /* This is the first argument position where we could
                  find an option, or the ID. */
    for (; i < c->argc; i++) {
        int moreargs = (c->argc-1) - i; /* Number of additional arguments. */
        char *opt = c->argv[i]->ptr;
        if (opt[0] == '*' && opt[1] == '\0') {
            /* This is just a fast path for the common case of auto-ID
             * creation. */
            break;
        } else if (!strcasecmp(opt,"maxlen") && moreargs) {
            approx_maxlen = 0;
            char *next = c->argv[i+1]->ptr;
            /* Check for the form MAXLEN ~ <count>. */
            if (moreargs >= 2 && next[0] == '~' && next[1] == '\0') {
                approx_maxlen = 1;
                i++;
            } else if (moreargs >= 2 && next[0] == '=' && next[1] == '\0') {
                i++;
            }
            if (getLongLongFromObjectOrReply(c,c->argv[i+1],&maxlen,NULL)
                != C_OK) return;

            if (maxlen < 0) {
                addReplyError(c,"The MAXLEN argument must be >= 0.");
                return;
            }
            i++;
            maxlen_arg_idx = i;
        } else {
            /* If we are here is a syntax error or a valid ID. */
            if (streamParseStrictIDOrReply(c,c->argv[i],&id,0) != C_OK) return;
            id_given = 1;
            break;
        }
    }
    int field_pos = i+1;

    /* Check arity. */
    if ((c->argc - field_pos) < 2 || ((c->argc-field_pos) % 2) == 1) {
        addReplyError(c,"wrong number of arguments for XADD");
        return;
    }

    /* Lookup the stream at key. */
    robj *o;
    stream *s;
    if ((o = streamTypeLookupWriteOrCreate(c,c->argv[1])) == NULL) return;
    s = o->ptr;

    /* Append using the low level function and return the ID. */
    if (streamAppendItem(s,c->argv+field_pos,(c->argc-field_pos)/2,
        &id, id_given ? &id : NULL)
        == C_ERR)
    {
        addReplyError(c,"The ID specified in XADD is equal or smaller than the "
                        "target stream top item");
        return;
    }
    addReplyStreamID(c,&id);

    signalModifiedKey(c->db,c->argv[1]);
    notifyKeyspaceEvent(NOTIFY_STREAM,"xadd",c->argv[1],c->db->id);
    server.dirty++;

    if (maxlen >= 0) {
        /* Notify xtrim event if needed. */
        if (streamTrimByLength(s,maxlen,approx_maxlen)) {
            notifyKeyspaceEvent(NOTIFY_STREAM,"xtrim",c->argv[1],c->db->id);
        }
        if (approx_maxlen) streamRewriteApproxMaxlen(c,s,maxlen_arg_idx);
    }

    /* Let's rewrite the ID argument with the one actually generated for
     * AOF/replication propagation. */
    robj *idarg = createObjectFromStreamID(&id);
    rewriteClientCommandArgument(c,i,idarg);
    decrRefCount(idarg);

    /* We need to signal to blocked clients that there is new data on this
     * stream. */
    if (server.blocked_clients_by_type[BLOCKED_STREAM])
        signalKeyAsReady(c->db, c->argv[1]);
}