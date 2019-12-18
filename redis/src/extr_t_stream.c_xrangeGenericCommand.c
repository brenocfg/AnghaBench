#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  streamID ;
typedef  int /*<<< orphan*/  stream ;
struct TYPE_17__ {int /*<<< orphan*/ * ptr; } ;
typedef  TYPE_1__ robj ;
struct TYPE_18__ {int argc; TYPE_1__** argv; } ;
typedef  TYPE_2__ client ;
struct TYPE_19__ {int /*<<< orphan*/  emptyarray; int /*<<< orphan*/  syntaxerr; } ;

/* Variables and functions */
 scalar_t__ C_ERR ; 
 scalar_t__ C_OK ; 
 int /*<<< orphan*/  OBJ_STREAM ; 
 int /*<<< orphan*/  UINT64_MAX ; 
 int /*<<< orphan*/  addReply (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyNullArray (TYPE_2__*) ; 
 scalar_t__ checkType (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ getLongLongFromObjectOrReply (TYPE_2__*,TYPE_1__*,long long*,int /*<<< orphan*/ *) ; 
 TYPE_1__* lookupKeyReadOrReply (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_7__ shared ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ streamParseIDOrReply (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  streamReplyWithRange (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,long long,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void xrangeGenericCommand(client *c, int rev) {
    robj *o;
    stream *s;
    streamID startid, endid;
    long long count = -1;
    robj *startarg = rev ? c->argv[3] : c->argv[2];
    robj *endarg = rev ? c->argv[2] : c->argv[3];

    if (streamParseIDOrReply(c,startarg,&startid,0) == C_ERR) return;
    if (streamParseIDOrReply(c,endarg,&endid,UINT64_MAX) == C_ERR) return;

    /* Parse the COUNT option if any. */
    if (c->argc > 4) {
        for (int j = 4; j < c->argc; j++) {
            int additional = c->argc-j-1;
            if (strcasecmp(c->argv[j]->ptr,"COUNT") == 0 && additional >= 1) {
                if (getLongLongFromObjectOrReply(c,c->argv[j+1],&count,NULL)
                    != C_OK) return;
                if (count < 0) count = 0;
                j++; /* Consume additional arg. */
            } else {
                addReply(c,shared.syntaxerr);
                return;
            }
        }
    }

    /* Return the specified range to the user. */
    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.emptyarray)) == NULL ||
         checkType(c,o,OBJ_STREAM)) return;

    s = o->ptr;

    if (count == 0) {
        addReplyNullArray(c);
    } else {
        if (count == -1) count = 0;
        streamReplyWithRange(c,s,&startid,&endid,count,rev,NULL,NULL,0,NULL);
    }
}