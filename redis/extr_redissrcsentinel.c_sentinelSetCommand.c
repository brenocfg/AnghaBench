#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_11__ ;

/* Type definitions */
struct TYPE_17__ {long long down_after_period; long long failover_timeout; long long parallel_syncs; long long quorum; int /*<<< orphan*/  renamed_commands; int /*<<< orphan*/ * auth_pass; int /*<<< orphan*/ * client_reconfig_script; int /*<<< orphan*/ * notification_script; } ;
typedef  TYPE_1__ sentinelRedisInstance ;
typedef  char* sds ;
struct TYPE_18__ {char* ptr; } ;
typedef  TYPE_2__ robj ;
struct TYPE_19__ {int argc; TYPE_2__** argv; } ;
typedef  TYPE_3__ client ;
struct TYPE_20__ {int /*<<< orphan*/  ok; } ;
struct TYPE_16__ {scalar_t__ deny_scripts_reconfig; } ;

/* Variables and functions */
 scalar_t__ C_ERR ; 
 int /*<<< orphan*/  LL_WARNING ; 
 int /*<<< orphan*/  X_OK ; 
 int access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReply (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyError (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  addReplyErrorFormat (TYPE_3__*,char*,char*,...) ; 
 int /*<<< orphan*/  dictAdd (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  dictDelete (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dictSdsKeyCaseCompare (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ getLongLongFromObject (TYPE_2__*,long long*) ; 
 char* sdsdup (char*) ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ *) ; 
 scalar_t__ sdslen (char*) ; 
 int /*<<< orphan*/ * sdsnew (char*) ; 
 TYPE_11__ sentinel ; 
 int /*<<< orphan*/  sentinelEvent (int /*<<< orphan*/ ,char*,TYPE_1__*,char*,char*,...) ; 
 int /*<<< orphan*/  sentinelFlushConfig () ; 
 TYPE_1__* sentinelGetMasterByNameOrReplyError (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  sentinelPropagateDownAfterPeriod (TYPE_1__*) ; 
 TYPE_4__ shared ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

void sentinelSetCommand(client *c) {
    sentinelRedisInstance *ri;
    int j, changes = 0;
    int badarg = 0; /* Bad argument position for error reporting. */
    char *option;

    if ((ri = sentinelGetMasterByNameOrReplyError(c,c->argv[2]))
        == NULL) return;

    /* Process option - value pairs. */
    for (j = 3; j < c->argc; j++) {
        int moreargs = (c->argc-1) - j;
        option = c->argv[j]->ptr;
        long long ll;
        int old_j = j; /* Used to know what to log as an event. */

        if (!strcasecmp(option,"down-after-milliseconds") && moreargs > 0) {
            /* down-after-millisecodns <milliseconds> */
            robj *o = c->argv[++j];
            if (getLongLongFromObject(o,&ll) == C_ERR || ll <= 0) {
                badarg = j;
                goto badfmt;
            }
            ri->down_after_period = ll;
            sentinelPropagateDownAfterPeriod(ri);
            changes++;
        } else if (!strcasecmp(option,"failover-timeout") && moreargs > 0) {
            /* failover-timeout <milliseconds> */
            robj *o = c->argv[++j];
            if (getLongLongFromObject(o,&ll) == C_ERR || ll <= 0) {
                badarg = j;
                goto badfmt;
            }
            ri->failover_timeout = ll;
            changes++;
        } else if (!strcasecmp(option,"parallel-syncs") && moreargs > 0) {
            /* parallel-syncs <milliseconds> */
            robj *o = c->argv[++j];
            if (getLongLongFromObject(o,&ll) == C_ERR || ll <= 0) {
                badarg = j;
                goto badfmt;
            }
            ri->parallel_syncs = ll;
            changes++;
        } else if (!strcasecmp(option,"notification-script") && moreargs > 0) {
            /* notification-script <path> */
            char *value = c->argv[++j]->ptr;
            if (sentinel.deny_scripts_reconfig) {
                addReplyError(c,
                    "Reconfiguration of scripts path is denied for "
                    "security reasons. Check the deny-scripts-reconfig "
                    "configuration directive in your Sentinel configuration");
                return;
            }

            if (strlen(value) && access(value,X_OK) == -1) {
                addReplyError(c,
                    "Notification script seems non existing or non executable");
                if (changes) sentinelFlushConfig();
                return;
            }
            sdsfree(ri->notification_script);
            ri->notification_script = strlen(value) ? sdsnew(value) : NULL;
            changes++;
        } else if (!strcasecmp(option,"client-reconfig-script") && moreargs > 0) {
            /* client-reconfig-script <path> */
            char *value = c->argv[++j]->ptr;
            if (sentinel.deny_scripts_reconfig) {
                addReplyError(c,
                    "Reconfiguration of scripts path is denied for "
                    "security reasons. Check the deny-scripts-reconfig "
                    "configuration directive in your Sentinel configuration");
                return;
            }

            if (strlen(value) && access(value,X_OK) == -1) {
                addReplyError(c,
                    "Client reconfiguration script seems non existing or "
                    "non executable");
                if (changes) sentinelFlushConfig();
                return;
            }
            sdsfree(ri->client_reconfig_script);
            ri->client_reconfig_script = strlen(value) ? sdsnew(value) : NULL;
            changes++;
        } else if (!strcasecmp(option,"auth-pass") && moreargs > 0) {
            /* auth-pass <password> */
            char *value = c->argv[++j]->ptr;
            sdsfree(ri->auth_pass);
            ri->auth_pass = strlen(value) ? sdsnew(value) : NULL;
            changes++;
        } else if (!strcasecmp(option,"quorum") && moreargs > 0) {
            /* quorum <count> */
            robj *o = c->argv[++j];
            if (getLongLongFromObject(o,&ll) == C_ERR || ll <= 0) {
                badarg = j;
                goto badfmt;
            }
            ri->quorum = ll;
            changes++;
        } else if (!strcasecmp(option,"rename-command") && moreargs > 1) {
            /* rename-command <oldname> <newname> */
            sds oldname = c->argv[++j]->ptr;
            sds newname = c->argv[++j]->ptr;

            if ((sdslen(oldname) == 0) || (sdslen(newname) == 0)) {
                badarg = sdslen(newname) ? j-1 : j;
                goto badfmt;
            }

            /* Remove any older renaming for this command. */
            dictDelete(ri->renamed_commands,oldname);

            /* If the target name is the same as the source name there
             * is no need to add an entry mapping to itself. */
            if (!dictSdsKeyCaseCompare(NULL,oldname,newname)) {
                oldname = sdsdup(oldname);
                newname = sdsdup(newname);
                dictAdd(ri->renamed_commands,oldname,newname);
            }
            changes++;
        } else {
            addReplyErrorFormat(c,"Unknown option or number of arguments for "
                                  "SENTINEL SET '%s'", option);
            if (changes) sentinelFlushConfig();
            return;
        }

        /* Log the event. */
        int numargs = j-old_j+1;
        switch(numargs) {
        case 2:
            sentinelEvent(LL_WARNING,"+set",ri,"%@ %s %s",c->argv[old_j]->ptr,
                                                          c->argv[old_j+1]->ptr);
            break;
        case 3:
            sentinelEvent(LL_WARNING,"+set",ri,"%@ %s %s %s",c->argv[old_j]->ptr,
                                                             c->argv[old_j+1]->ptr,
                                                             c->argv[old_j+2]->ptr);
            break;
        default:
            sentinelEvent(LL_WARNING,"+set",ri,"%@ %s",c->argv[old_j]->ptr);
            break;
        }
    }

    if (changes) sentinelFlushConfig();
    addReply(c,shared.ok);
    return;

badfmt: /* Bad format errors */
    if (changes) sentinelFlushConfig();
    addReplyErrorFormat(c,"Invalid argument '%s' for SENTINEL SET '%s'",
        (char*)c->argv[badarg]->ptr,option);
}