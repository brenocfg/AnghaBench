#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct redisCommand {int flags; } ;
typedef  int /*<<< orphan*/  robj ;
struct TYPE_19__ {int cmd_flags; int count; TYPE_1__* commands; } ;
struct TYPE_21__ {int flags; size_t resp; int argc; int /*<<< orphan*/ ** argv; TYPE_3__* db; struct redisCommand* cmd; TYPE_2__ mstate; } ;
typedef  TYPE_4__ client ;
struct TYPE_23__ {int /*<<< orphan*/  monitors; scalar_t__ loading; scalar_t__ repl_backlog; int /*<<< orphan*/  dirty; int /*<<< orphan*/ * masterhost; scalar_t__ repl_slave_ro; } ;
struct TYPE_22__ {int /*<<< orphan*/ * nullarray; int /*<<< orphan*/  execaborterr; } ;
struct TYPE_20__ {int /*<<< orphan*/  id; } ;
struct TYPE_18__ {int argc; struct redisCommand* cmd; int /*<<< orphan*/ ** argv; } ;

/* Variables and functions */
 int ACLCheckCommandPerm (TYPE_4__*) ; 
 int ACL_DENIED_CMD ; 
 int ACL_OK ; 
 int CLIENT_DIRTY_CAS ; 
 int CLIENT_DIRTY_EXEC ; 
 int CLIENT_MASTER ; 
 int CLIENT_MULTI ; 
 int CMD_ADMIN ; 
 int /*<<< orphan*/  CMD_CALL_FULL ; 
 int /*<<< orphan*/  CMD_CALL_NONE ; 
 int CMD_READONLY ; 
 int CMD_WRITE ; 
 int /*<<< orphan*/  addReply (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyArrayLen (TYPE_4__*,int) ; 
 int /*<<< orphan*/  addReplyError (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  addReplyErrorFormat (TYPE_4__*,char*,char*) ; 
 int /*<<< orphan*/  call (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  discardTransaction (TYPE_4__*) ; 
 int /*<<< orphan*/  execCommandPropagateMulti (TYPE_4__*) ; 
 int /*<<< orphan*/  feedReplicationBacklog (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ listLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  replicationFeedMonitors (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int) ; 
 TYPE_7__ server ; 
 TYPE_6__ shared ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  unwatchAllKeys (TYPE_4__*) ; 

void execCommand(client *c) {
    int j;
    robj **orig_argv;
    int orig_argc;
    struct redisCommand *orig_cmd;
    int must_propagate = 0; /* Need to propagate MULTI/EXEC to AOF / slaves? */
    int was_master = server.masterhost == NULL;

    if (!(c->flags & CLIENT_MULTI)) {
        addReplyError(c,"EXEC without MULTI");
        return;
    }

    /* Check if we need to abort the EXEC because:
     * 1) Some WATCHed key was touched.
     * 2) There was a previous error while queueing commands.
     * A failed EXEC in the first case returns a multi bulk nil object
     * (technically it is not an error but a special behavior), while
     * in the second an EXECABORT error is returned. */
    if (c->flags & (CLIENT_DIRTY_CAS|CLIENT_DIRTY_EXEC)) {
        addReply(c, c->flags & CLIENT_DIRTY_EXEC ? shared.execaborterr :
                                                   shared.nullarray[c->resp]);
        discardTransaction(c);
        goto handle_monitor;
    }

    /* If there are write commands inside the transaction, and this is a read
     * only slave, we want to send an error. This happens when the transaction
     * was initiated when the instance was a master or a writable replica and
     * then the configuration changed (for example instance was turned into
     * a replica). */
    if (!server.loading && server.masterhost && server.repl_slave_ro &&
        !(c->flags & CLIENT_MASTER) && c->mstate.cmd_flags & CMD_WRITE)
    {
        addReplyError(c,
            "Transaction contains write commands but instance "
            "is now a read-only replica. EXEC aborted.");
        discardTransaction(c);
        goto handle_monitor;
    }

    /* Exec all the queued commands */
    unwatchAllKeys(c); /* Unwatch ASAP otherwise we'll waste CPU cycles */
    orig_argv = c->argv;
    orig_argc = c->argc;
    orig_cmd = c->cmd;
    addReplyArrayLen(c,c->mstate.count);
    for (j = 0; j < c->mstate.count; j++) {
        c->argc = c->mstate.commands[j].argc;
        c->argv = c->mstate.commands[j].argv;
        c->cmd = c->mstate.commands[j].cmd;

        /* Propagate a MULTI request once we encounter the first command which
         * is not readonly nor an administrative one.
         * This way we'll deliver the MULTI/..../EXEC block as a whole and
         * both the AOF and the replication link will have the same consistency
         * and atomicity guarantees. */
        if (!must_propagate && !(c->cmd->flags & (CMD_READONLY|CMD_ADMIN))) {
            execCommandPropagateMulti(c);
            must_propagate = 1;
        }

        int acl_retval = ACLCheckCommandPerm(c);
        if (acl_retval != ACL_OK) {
            addReplyErrorFormat(c,
                "-NOPERM ACLs rules changed between the moment the "
                "transaction was accumulated and the EXEC call. "
                "This command is no longer allowed for the "
                "following reason: %s",
                (acl_retval == ACL_DENIED_CMD) ?
                "no permission to execute the command or subcommand" :
                "no permission to touch the specified keys");
        } else {
            call(c,server.loading ? CMD_CALL_NONE : CMD_CALL_FULL);
        }

        /* Commands may alter argc/argv, restore mstate. */
        c->mstate.commands[j].argc = c->argc;
        c->mstate.commands[j].argv = c->argv;
        c->mstate.commands[j].cmd = c->cmd;
    }
    c->argv = orig_argv;
    c->argc = orig_argc;
    c->cmd = orig_cmd;
    discardTransaction(c);

    /* Make sure the EXEC command will be propagated as well if MULTI
     * was already propagated. */
    if (must_propagate) {
        int is_master = server.masterhost == NULL;
        server.dirty++;
        /* If inside the MULTI/EXEC block this instance was suddenly
         * switched from master to slave (using the SLAVEOF command), the
         * initial MULTI was propagated into the replication backlog, but the
         * rest was not. We need to make sure to at least terminate the
         * backlog with the final EXEC. */
        if (server.repl_backlog && was_master && !is_master) {
            char *execcmd = "*1\r\n$4\r\nEXEC\r\n";
            feedReplicationBacklog(execcmd,strlen(execcmd));
        }
    }

handle_monitor:
    /* Send EXEC to clients waiting data from MONITOR. We do it here
     * since the natural order of commands execution is actually:
     * MUTLI, EXEC, ... commands inside transaction ...
     * Instead EXEC is flagged as CMD_SKIP_MONITOR in the command
     * table, and we do it here with correct ordering. */
    if (listLength(server.monitors) && !server.loading)
        replicationFeedMonitors(c,server.monitors,c->db->id,c->argv,c->argc);
}