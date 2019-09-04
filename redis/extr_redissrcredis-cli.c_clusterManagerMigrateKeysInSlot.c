#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
struct TYPE_25__ {scalar_t__ type; int len; char* str; size_t elements; } ;
typedef  TYPE_2__ redisReply ;
struct TYPE_26__ {char* value; } ;
typedef  TYPE_3__ listNode ;
typedef  int /*<<< orphan*/  listIter ;
typedef  int /*<<< orphan*/  list ;
struct TYPE_27__ {int /*<<< orphan*/  port; int /*<<< orphan*/  ip; } ;
typedef  TYPE_4__ clusterManagerNode ;
struct TYPE_24__ {int flags; } ;
struct TYPE_28__ {TYPE_1__ cluster_manager_command; } ;

/* Variables and functions */
 int CLUSTER_MANAGER_CMD_FLAG_FIX ; 
 int CLUSTER_MANAGER_CMD_FLAG_REPLACE ; 
 TYPE_2__* CLUSTER_MANAGER_COMMAND (TYPE_4__*,char*,int,int) ; 
 int /*<<< orphan*/  CLUSTER_MANAGER_PRINT_REPLY_ERROR (TYPE_4__*,char*) ; 
 scalar_t__ REDIS_REPLY_ARRAY ; 
 scalar_t__ REDIS_REPLY_ERROR ; 
 int /*<<< orphan*/  assert (int) ; 
 int clusterManagerCompareKeysValues (TYPE_4__*,TYPE_4__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_4__* clusterManagerGetSlotOwner (TYPE_4__*,int,char**) ; 
 int /*<<< orphan*/  clusterManagerLogErr (char*,...) ; 
 int /*<<< orphan*/  clusterManagerLogWarn (char*,...) ; 
 TYPE_2__* clusterManagerMigrateKeysInReply (TYPE_4__*,TYPE_4__*,TYPE_2__*,int,int,char*) ; 
 int /*<<< orphan*/  clusterManagerSetSlot (TYPE_4__*,TYPE_4__*,int,char*,int /*<<< orphan*/ *) ; 
 TYPE_7__ config ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freeReplyObject (TYPE_2__*) ; 
 int /*<<< orphan*/ * listCreate () ; 
 scalar_t__ listLength (int /*<<< orphan*/ *) ; 
 TYPE_3__* listNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRewind (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/ * strstr (char*,char*) ; 
 int /*<<< orphan*/  zfree (char*) ; 
 char* zmalloc (int) ; 

__attribute__((used)) static int clusterManagerMigrateKeysInSlot(clusterManagerNode *source,
                                           clusterManagerNode *target,
                                           int slot, int timeout,
                                           int pipeline, int verbose,
                                           char **err)
{
    int success = 1;
    int do_fix = config.cluster_manager_command.flags &
                 CLUSTER_MANAGER_CMD_FLAG_FIX;
    int do_replace = config.cluster_manager_command.flags &
                     CLUSTER_MANAGER_CMD_FLAG_REPLACE;
    while (1) {
        char *dots = NULL;
        redisReply *reply = NULL, *migrate_reply = NULL;
        reply = CLUSTER_MANAGER_COMMAND(source, "CLUSTER "
                                        "GETKEYSINSLOT %d %d", slot,
                                        pipeline);
        success = (reply != NULL);
        if (!success) return 0;
        if (reply->type == REDIS_REPLY_ERROR) {
            success = 0;
            if (err != NULL) {
                *err = zmalloc((reply->len + 1) * sizeof(char));
                strcpy(*err, reply->str);
                CLUSTER_MANAGER_PRINT_REPLY_ERROR(source, *err);
            }
            goto next;
        }
        assert(reply->type == REDIS_REPLY_ARRAY);
        size_t count = reply->elements;
        if (count == 0) {
            freeReplyObject(reply);
            break;
        }
        if (verbose) dots = zmalloc((count+1) * sizeof(char));
        /* Calling MIGRATE command. */
        migrate_reply = clusterManagerMigrateKeysInReply(source, target,
                                                         reply, 0, timeout,
                                                         dots);
        if (migrate_reply == NULL) goto next;
        if (migrate_reply->type == REDIS_REPLY_ERROR) {
            int is_busy = strstr(migrate_reply->str, "BUSYKEY") != NULL;
            int not_served = 0;
            if (!is_busy) {
                /* Check if the slot is unassigned (not served) in the
                 * source node's configuration. */
                char *get_owner_err = NULL;
                clusterManagerNode *served_by =
                    clusterManagerGetSlotOwner(source, slot, &get_owner_err);
                if (!served_by) {
                    if (get_owner_err == NULL) not_served = 1;
                    else {
                        CLUSTER_MANAGER_PRINT_REPLY_ERROR(source,
                                                          get_owner_err);
                        zfree(get_owner_err);
                    }
                }
            }
            /* Try to handle errors. */
            if (is_busy || not_served) {
                /* If the key's slot is not served, try to assign slot
                 * to the target node. */
                if (do_fix && not_served) {
                    clusterManagerLogWarn("*** Slot was not served, setting "
                                          "owner to node %s:%d.\n",
                                          target->ip, target->port);
                    clusterManagerSetSlot(source, target, slot, "node", NULL);
                }
                /* If the key already exists in the target node (BUSYKEY),
                 * check whether its value is the same in both nodes.
                 * In case of equal values, retry migration with the
                 * REPLACE option.
                 * In case of different values:
                 *  - If the migration is requested by the fix command, stop
                 *    and warn the user.
                 *  - In other cases (ie. reshard), proceed only if the user
                 *    launched the command with the --cluster-replace option.*/
                if (is_busy) {
                    clusterManagerLogWarn("\n*** Target key exists\n");
                    if (!do_replace) {
                        clusterManagerLogWarn("*** Checking key values on "
                                              "both nodes...\n");
                        list *diffs = listCreate();
                        success = clusterManagerCompareKeysValues(source,
                            target, reply, diffs);
                        if (!success) {
                            clusterManagerLogErr("*** Value check failed!\n");
                            listRelease(diffs);
                            goto next;
                        }
                        if (listLength(diffs) > 0) {
                            success = 0;
                            clusterManagerLogErr(
                                "*** Found %d key(s) in both source node and "
                                "target node having different values.\n"
                                "    Source node: %s:%d\n"
                                "    Target node: %s:%d\n"
                                "    Keys(s):\n",
                                listLength(diffs),
                                source->ip, source->port,
                                target->ip, target->port);
                            listIter dli;
                            listNode *dln;
                            listRewind(diffs, &dli);
                            while((dln = listNext(&dli)) != NULL) {
                                char *k = dln->value;
                                clusterManagerLogErr("    - %s\n", k);
                            }
                            clusterManagerLogErr("Please fix the above key(s) "
                                                 "manually and try again "
                                                 "or relaunch the command \n"
                                                 "with --cluster-replace "
                                                 "option to force key "
                                                 "overriding.\n");
                            listRelease(diffs);
                            goto next;
                        }
                        listRelease(diffs);
                    }
                    clusterManagerLogWarn("*** Replacing target keys...\n");
                }
                freeReplyObject(migrate_reply);
                migrate_reply = clusterManagerMigrateKeysInReply(source,
                                                                 target,
                                                                 reply,
                                                                 is_busy,
                                                                 timeout,
                                                                 NULL);
                success = (migrate_reply != NULL &&
                           migrate_reply->type != REDIS_REPLY_ERROR);
            } else success = 0;
            if (!success) {
                if (migrate_reply != NULL) {
                    if (err) {
                        *err = zmalloc((migrate_reply->len + 1) * sizeof(char));
                        strcpy(*err, migrate_reply->str);
                    }
                    printf("\n");
                    CLUSTER_MANAGER_PRINT_REPLY_ERROR(source,
                                                      migrate_reply->str);
                }
                goto next;
            }
        }
        if (verbose) {
            printf("%s", dots);
            fflush(stdout);
        }
next:
        if (reply != NULL) freeReplyObject(reply);
        if (migrate_reply != NULL) freeReplyObject(migrate_reply);
        if (dots) zfree(dots);
        if (!success) break;
    }
    return success;
}