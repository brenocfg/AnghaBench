#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  stream ;
struct TYPE_20__ {int /*<<< orphan*/ * ptr; } ;
typedef  TYPE_1__ robj ;
typedef  scalar_t__ int64_t ;
struct TYPE_21__ {int argc; TYPE_5__* db; TYPE_6__** argv; } ;
typedef  TYPE_2__ client ;
struct TYPE_25__ {int /*<<< orphan*/  dirty; } ;
struct TYPE_24__ {int /*<<< orphan*/  syntaxerr; int /*<<< orphan*/  czero; } ;
struct TYPE_23__ {char* ptr; } ;
struct TYPE_22__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 scalar_t__ C_OK ; 
 int /*<<< orphan*/  NOTIFY_STREAM ; 
 int /*<<< orphan*/  OBJ_STREAM ; 
 int TRIM_STRATEGY_MAXLEN ; 
 int TRIM_STRATEGY_NONE ; 
 int /*<<< orphan*/  addReply (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyError (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  addReplyLongLong (TYPE_2__*,scalar_t__) ; 
 scalar_t__ checkType (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ getLongLongFromObjectOrReply (TYPE_2__*,TYPE_6__*,long long*,int /*<<< orphan*/ *) ; 
 TYPE_1__* lookupKeyWriteOrReply (TYPE_2__*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  notifyKeyspaceEvent (int /*<<< orphan*/ ,char*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 TYPE_8__ server ; 
 TYPE_7__ shared ; 
 int /*<<< orphan*/  signalModifiedKey (TYPE_5__*,TYPE_6__*) ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 
 int /*<<< orphan*/  streamRewriteApproxMaxlen (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ streamTrimByLength (int /*<<< orphan*/ *,long long,int) ; 

void xtrimCommand(client *c) {
    robj *o;

    /* If the key does not exist, we are ok returning zero, that is, the
     * number of elements removed from the stream. */
    if ((o = lookupKeyWriteOrReply(c,c->argv[1],shared.czero)) == NULL
        || checkType(c,o,OBJ_STREAM)) return;
    stream *s = o->ptr;

    /* Argument parsing. */
    int trim_strategy = TRIM_STRATEGY_NONE;
    long long maxlen = -1;  /* If left to -1 no trimming is performed. */
    int approx_maxlen = 0;  /* If 1 only delete whole radix tree nodes, so
                               the maxium length is not applied verbatim. */
    int maxlen_arg_idx = 0; /* Index of the count in MAXLEN, for rewriting. */

    /* Parse options. */
    int i = 2; /* Start of options. */
    for (; i < c->argc; i++) {
        int moreargs = (c->argc-1) - i; /* Number of additional arguments. */
        char *opt = c->argv[i]->ptr;
        if (!strcasecmp(opt,"maxlen") && moreargs) {
            approx_maxlen = 0;
            trim_strategy = TRIM_STRATEGY_MAXLEN;
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
            addReply(c,shared.syntaxerr);
            return;
        }
    }

    /* Perform the trimming. */
    int64_t deleted = 0;
    if (trim_strategy == TRIM_STRATEGY_MAXLEN) {
        deleted = streamTrimByLength(s,maxlen,approx_maxlen);
    } else {
        addReplyError(c,"XTRIM called without an option to trim the stream");
        return;
    }

    /* Propagate the write if needed. */
    if (deleted) {
        signalModifiedKey(c->db,c->argv[1]);
        notifyKeyspaceEvent(NOTIFY_STREAM,"xtrim",c->argv[1],c->db->id);
        server.dirty += deleted;
        if (approx_maxlen) streamRewriteApproxMaxlen(c,s,maxlen_arg_idx);
    }
    addReplyLongLong(c,deleted);
}