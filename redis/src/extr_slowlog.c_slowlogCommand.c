#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
struct TYPE_20__ {int argc; int /*<<< orphan*/  cname; int /*<<< orphan*/  peerid; int /*<<< orphan*/ * argv; int /*<<< orphan*/  duration; int /*<<< orphan*/  time; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ slowlogEntry ;
struct TYPE_21__ {TYPE_1__* value; } ;
typedef  TYPE_2__ listNode ;
typedef  int /*<<< orphan*/  listIter ;
struct TYPE_22__ {int argc; TYPE_10__** argv; } ;
typedef  TYPE_3__ client ;
struct TYPE_24__ {int /*<<< orphan*/  slowlog; } ;
struct TYPE_23__ {int /*<<< orphan*/  ok; } ;
struct TYPE_19__ {int /*<<< orphan*/  ptr; } ;

/* Variables and functions */
 scalar_t__ C_OK ; 
 int /*<<< orphan*/  addReply (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyArrayLen (TYPE_3__*,int) ; 
 int /*<<< orphan*/  addReplyBulk (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyBulkCBuffer (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* addReplyDeferredLen (TYPE_3__*) ; 
 int /*<<< orphan*/  addReplyHelp (TYPE_3__*,char const**) ; 
 int /*<<< orphan*/  addReplyLongLong (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplySubcommandSyntaxError (TYPE_3__*) ; 
 scalar_t__ getLongFromObjectOrReply (TYPE_3__*,TYPE_10__*,long*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listLength (int /*<<< orphan*/ ) ; 
 TYPE_2__* listNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRewind (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdslen (int /*<<< orphan*/ ) ; 
 TYPE_7__ server ; 
 int /*<<< orphan*/  setDeferredArrayLen (TYPE_3__*,void*,long) ; 
 TYPE_5__ shared ; 
 int /*<<< orphan*/  slowlogReset () ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,char*) ; 

void slowlogCommand(client *c) {
    if (c->argc == 2 && !strcasecmp(c->argv[1]->ptr,"help")) {
        const char *help[] = {
"GET [count] -- Return top entries from the slowlog (default: 10)."
"    Entries are made of:",
"    id, timestamp, time in microseconds, arguments array, client IP and port, client name",
"LEN -- Return the length of the slowlog.",
"RESET -- Reset the slowlog.",
NULL
        };
        addReplyHelp(c, help);
    } else if (c->argc == 2 && !strcasecmp(c->argv[1]->ptr,"reset")) {
        slowlogReset();
        addReply(c,shared.ok);
    } else if (c->argc == 2 && !strcasecmp(c->argv[1]->ptr,"len")) {
        addReplyLongLong(c,listLength(server.slowlog));
    } else if ((c->argc == 2 || c->argc == 3) &&
               !strcasecmp(c->argv[1]->ptr,"get"))
    {
        long count = 10, sent = 0;
        listIter li;
        void *totentries;
        listNode *ln;
        slowlogEntry *se;

        if (c->argc == 3 &&
            getLongFromObjectOrReply(c,c->argv[2],&count,NULL) != C_OK)
            return;

        listRewind(server.slowlog,&li);
        totentries = addReplyDeferredLen(c);
        while(count-- && (ln = listNext(&li))) {
            int j;

            se = ln->value;
            addReplyArrayLen(c,6);
            addReplyLongLong(c,se->id);
            addReplyLongLong(c,se->time);
            addReplyLongLong(c,se->duration);
            addReplyArrayLen(c,se->argc);
            for (j = 0; j < se->argc; j++)
                addReplyBulk(c,se->argv[j]);
            addReplyBulkCBuffer(c,se->peerid,sdslen(se->peerid));
            addReplyBulkCBuffer(c,se->cname,sdslen(se->cname));
            sent++;
        }
        setDeferredArrayLen(c,totentries,sent);
    } else {
        addReplySubcommandSyntaxError(c);
    }
}