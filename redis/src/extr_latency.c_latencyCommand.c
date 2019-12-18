#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct latencyTimeSeries {int dummy; } ;
typedef  int /*<<< orphan*/  sds ;
typedef  int /*<<< orphan*/  dictEntry ;
struct TYPE_14__ {int argc; TYPE_1__** argv; } ;
typedef  TYPE_2__ client ;
struct TYPE_15__ {int /*<<< orphan*/  latency_events; } ;
struct TYPE_13__ {int /*<<< orphan*/ * ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  addReplyArrayLen (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyErrorFormat (TYPE_2__*,char*,char*) ; 
 int /*<<< orphan*/  addReplyHelp (TYPE_2__*,char const**) ; 
 int /*<<< orphan*/  addReplyLongLong (TYPE_2__*,int) ; 
 int /*<<< orphan*/  addReplySubcommandSyntaxError (TYPE_2__*) ; 
 int /*<<< orphan*/  addReplyVerbatim (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  createLatencyReport () ; 
 struct latencyTimeSeries* dictFetchValue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictFind (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* dictGetKey (int /*<<< orphan*/ *) ; 
 struct latencyTimeSeries* dictGetVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  latencyCommandGenSparkeline (char*,struct latencyTimeSeries*) ; 
 int /*<<< orphan*/  latencyCommandReplyWithLatestEvents (TYPE_2__*) ; 
 int /*<<< orphan*/  latencyCommandReplyWithSamples (TYPE_2__*,struct latencyTimeSeries*) ; 
 int latencyResetEvent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdslen (int /*<<< orphan*/ ) ; 
 TYPE_3__ server ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ *,char*) ; 

void latencyCommand(client *c) {
    const char *help[] = {
"DOCTOR              -- Returns a human readable latency analysis report.",
"GRAPH   <event>     -- Returns an ASCII latency graph for the event class.",
"HISTORY <event>     -- Returns time-latency samples for the event class.",
"LATEST              -- Returns the latest latency samples for all events.",
"RESET   [event ...] -- Resets latency data of one or more event classes.",
"                       (default: reset all data for all event classes)",
"HELP                -- Prints this help.",
NULL
    };
    struct latencyTimeSeries *ts;

    if (!strcasecmp(c->argv[1]->ptr,"history") && c->argc == 3) {
        /* LATENCY HISTORY <event> */
        ts = dictFetchValue(server.latency_events,c->argv[2]->ptr);
        if (ts == NULL) {
            addReplyArrayLen(c,0);
        } else {
            latencyCommandReplyWithSamples(c,ts);
        }
    } else if (!strcasecmp(c->argv[1]->ptr,"graph") && c->argc == 3) {
        /* LATENCY GRAPH <event> */
        sds graph;
        dictEntry *de;
        char *event;

        de = dictFind(server.latency_events,c->argv[2]->ptr);
        if (de == NULL) goto nodataerr;
        ts = dictGetVal(de);
        event = dictGetKey(de);

        graph = latencyCommandGenSparkeline(event,ts);
        addReplyVerbatim(c,graph,sdslen(graph),"txt");
        sdsfree(graph);
    } else if (!strcasecmp(c->argv[1]->ptr,"latest") && c->argc == 2) {
        /* LATENCY LATEST */
        latencyCommandReplyWithLatestEvents(c);
    } else if (!strcasecmp(c->argv[1]->ptr,"doctor") && c->argc == 2) {
        /* LATENCY DOCTOR */
        sds report = createLatencyReport();

        addReplyVerbatim(c,report,sdslen(report),"txt");
        sdsfree(report);
    } else if (!strcasecmp(c->argv[1]->ptr,"reset") && c->argc >= 2) {
        /* LATENCY RESET */
        if (c->argc == 2) {
            addReplyLongLong(c,latencyResetEvent(NULL));
        } else {
            int j, resets = 0;

            for (j = 2; j < c->argc; j++)
                resets += latencyResetEvent(c->argv[j]->ptr);
            addReplyLongLong(c,resets);
        }
    } else if (!strcasecmp(c->argv[1]->ptr,"help") && c->argc >= 2) {
        addReplyHelp(c, help);
    } else {
        addReplySubcommandSyntaxError(c);
    }
    return;

nodataerr:
    /* Common error when the user asks for an event we have no latency
     * information about. */
    addReplyErrorFormat(c,
        "No samples available for event '%s'", (char*) c->argv[2]->ptr);
}