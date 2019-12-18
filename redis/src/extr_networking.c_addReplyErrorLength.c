#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int flags; TYPE_1__* lastcmd; } ;
typedef  TYPE_2__ client ;
struct TYPE_5__ {char* name; } ;

/* Variables and functions */
 int CLIENT_MASTER ; 
 int CLIENT_MONITOR ; 
 int CLIENT_SLAVE ; 
 int /*<<< orphan*/  LL_WARNING ; 
 int /*<<< orphan*/  addReplyProto (TYPE_2__*,char const*,int) ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,char*,char*,char const*,char*) ; 

void addReplyErrorLength(client *c, const char *s, size_t len) {
    /* If the string already starts with "-..." then the error code
     * is provided by the caller. Otherwise we use "-ERR". */
    if (!len || s[0] != '-') addReplyProto(c,"-ERR ",5);
    addReplyProto(c,s,len);
    addReplyProto(c,"\r\n",2);

    /* Sometimes it could be normal that a slave replies to a master with
     * an error and this function gets called. Actually the error will never
     * be sent because addReply*() against master clients has no effect...
     * A notable example is:
     *
     *    EVAL 'redis.call("incr",KEYS[1]); redis.call("nonexisting")' 1 x
     *
     * Where the master must propagate the first change even if the second
     * will produce an error. However it is useful to log such events since
     * they are rare and may hint at errors in a script or a bug in Redis. */
    if (c->flags & (CLIENT_MASTER|CLIENT_SLAVE) && !(c->flags & CLIENT_MONITOR)) {
        char* to = c->flags & CLIENT_MASTER? "master": "replica";
        char* from = c->flags & CLIENT_MASTER? "replica": "master";
        char *cmdname = c->lastcmd ? c->lastcmd->name : "<unknown>";
        serverLog(LL_WARNING,"== CRITICAL == This %s is sending an error "
                             "to its %s: '%s' after processing the command "
                             "'%s'", from, to, s, cmdname);
    }
}