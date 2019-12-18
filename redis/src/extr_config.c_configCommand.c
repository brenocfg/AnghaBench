#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int argc; TYPE_1__** argv; } ;
typedef  TYPE_2__ client ;
struct TYPE_16__ {int /*<<< orphan*/ * configfile; scalar_t__ loading; } ;
struct TYPE_15__ {int /*<<< orphan*/  ok; } ;
struct TYPE_13__ {int /*<<< orphan*/  ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  LL_WARNING ; 
 int /*<<< orphan*/  addReply (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyError (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  addReplyErrorFormat (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyHelp (TYPE_2__*,char const**) ; 
 int /*<<< orphan*/  addReplySubcommandSyntaxError (TYPE_2__*) ; 
 int /*<<< orphan*/  configGetCommand (TYPE_2__*) ; 
 int /*<<< orphan*/  configSetCommand (TYPE_2__*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  resetCommandTableStats () ; 
 int /*<<< orphan*/  resetServerStats () ; 
 int rewriteConfig (int /*<<< orphan*/ *) ; 
 TYPE_4__ server ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_3__ shared ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

void configCommand(client *c) {
    /* Only allow CONFIG GET while loading. */
    if (server.loading && strcasecmp(c->argv[1]->ptr,"get")) {
        addReplyError(c,"Only CONFIG GET is allowed during loading");
        return;
    }

    if (c->argc == 2 && !strcasecmp(c->argv[1]->ptr,"help")) {
        const char *help[] = {
"GET <pattern> -- Return parameters matching the glob-like <pattern> and their values.",
"SET <parameter> <value> -- Set parameter to value.",
"RESETSTAT -- Reset statistics reported by INFO.",
"REWRITE -- Rewrite the configuration file.",
NULL
        };
        addReplyHelp(c, help);
    } else if (!strcasecmp(c->argv[1]->ptr,"set") && c->argc == 4) {
        configSetCommand(c);
    } else if (!strcasecmp(c->argv[1]->ptr,"get") && c->argc == 3) {
        configGetCommand(c);
    } else if (!strcasecmp(c->argv[1]->ptr,"resetstat") && c->argc == 2) {
        resetServerStats();
        resetCommandTableStats();
        addReply(c,shared.ok);
    } else if (!strcasecmp(c->argv[1]->ptr,"rewrite") && c->argc == 2) {
        if (server.configfile == NULL) {
            addReplyError(c,"The server is running without a config file");
            return;
        }
        if (rewriteConfig(server.configfile) == -1) {
            serverLog(LL_WARNING,"CONFIG REWRITE failed: %s", strerror(errno));
            addReplyErrorFormat(c,"Rewriting config file: %s", strerror(errno));
        } else {
            serverLog(LL_WARNING,"CONFIG REWRITE executed with success.");
            addReply(c,shared.ok);
        }
    } else {
        addReplySubcommandSyntaxError(c);
        return;
    }
}