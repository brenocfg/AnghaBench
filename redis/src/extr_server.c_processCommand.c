#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_21__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_12__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sds ;
typedef  int /*<<< orphan*/  clusterNode ;
struct TYPE_27__ {int flags; int argc; int resp; int /*<<< orphan*/  woff; TYPE_9__* cmd; TYPE_12__** argv; int /*<<< orphan*/  authenticated; TYPE_9__* lastcmd; } ;
typedef  TYPE_3__ client ;
struct TYPE_30__ {int arity; scalar_t__ proc; scalar_t__ firstkey; int flags; int /*<<< orphan*/ * getkeys_proc; int /*<<< orphan*/  name; } ;
struct TYPE_29__ {scalar_t__ repl_min_slaves_to_write; scalar_t__ repl_good_slaves_count; scalar_t__ repl_state; scalar_t__ repl_serve_stale_data; int /*<<< orphan*/  ready_keys; int /*<<< orphan*/  master_repl_offset; scalar_t__ lua_timedout; scalar_t__ loading; int /*<<< orphan*/ * masterhost; scalar_t__ repl_slave_ro; scalar_t__ repl_min_slaves_max_lag; int /*<<< orphan*/  aof_last_write_errno; scalar_t__ tracking_clients; int /*<<< orphan*/ * current_client; scalar_t__ maxmemory; TYPE_2__* cluster; TYPE_1__* lua_caller; scalar_t__ cluster_enabled; } ;
struct TYPE_28__ {int /*<<< orphan*/  queued; int /*<<< orphan*/  slowscripterr; int /*<<< orphan*/  loadingerr; int /*<<< orphan*/  masterdownerr; int /*<<< orphan*/  roslaveerr; int /*<<< orphan*/  noreplicaserr; int /*<<< orphan*/  bgsaveerr; int /*<<< orphan*/  oomerr; int /*<<< orphan*/  noautherr; int /*<<< orphan*/  ok; } ;
struct TYPE_26__ {int /*<<< orphan*/ * myself; } ;
struct TYPE_25__ {int flags; } ;
struct TYPE_24__ {int flags; } ;
struct TYPE_23__ {scalar_t__ ptr; } ;

/* Variables and functions */
 int ACLCheckCommandPerm (TYPE_3__*) ; 
 int ACL_DENIED_CMD ; 
 int ACL_OK ; 
 int CLIENT_CLOSE_AFTER_REPLY ; 
 int CLIENT_LUA ; 
 int CLIENT_MASTER ; 
 int CLIENT_MULTI ; 
 int CLIENT_PUBSUB ; 
 int /*<<< orphan*/  CMD_CALL_FULL ; 
 int CMD_DENYOOM ; 
 int CMD_LOADING ; 
 int CMD_STALE ; 
 int CMD_WRITE ; 
 int C_ERR ; 
 int C_OK ; 
 int DISK_ERROR_TYPE_NONE ; 
 int DISK_ERROR_TYPE_RDB ; 
 TYPE_21__* DefaultUser ; 
 scalar_t__ REPL_STATE_CONNECTED ; 
 int USER_FLAG_DISABLED ; 
 int USER_FLAG_NOPASS ; 
 int /*<<< orphan*/  addReply (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyError (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  addReplyErrorFormat (TYPE_3__*,char*,...) ; 
 int /*<<< orphan*/  addReplySds (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ authCommand ; 
 int /*<<< orphan*/  call (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clusterRedirectClient (TYPE_3__*,int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ discardCommand ; 
 int /*<<< orphan*/  discardTransaction (TYPE_3__*) ; 
 scalar_t__ execCommand ; 
 int /*<<< orphan*/  flagTransaction (TYPE_3__*) ; 
 int freeMemoryIfNeededAndSafe () ; 
 int /*<<< orphan*/ * getNodeByQuery (TYPE_3__*,TYPE_9__*,TYPE_12__**,int,int*,int*) ; 
 int /*<<< orphan*/  handleClientsBlockedOnKeys () ; 
 scalar_t__ helloCommand ; 
 scalar_t__ listLength (int /*<<< orphan*/ ) ; 
 TYPE_9__* lookupCommand (scalar_t__) ; 
 int /*<<< orphan*/  moduleCallCommandFilters (TYPE_3__*) ; 
 scalar_t__ multiCommand ; 
 scalar_t__ pingCommand ; 
 scalar_t__ psubscribeCommand ; 
 scalar_t__ punsubscribeCommand ; 
 int /*<<< orphan*/  queueMultiCommand (TYPE_3__*) ; 
 scalar_t__ replconfCommand ; 
 scalar_t__ scriptCommand ; 
 int /*<<< orphan*/  sdscatprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  sdsempty () ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 
 int sdslen (int /*<<< orphan*/ ) ; 
 TYPE_5__ server ; 
 TYPE_4__ shared ; 
 scalar_t__ shutdownCommand ; 
 int /*<<< orphan*/  strcasecmp (scalar_t__,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ subscribeCommand ; 
 char tolower (char) ; 
 int /*<<< orphan*/  trackingLimitUsedSlots () ; 
 scalar_t__ unsubscribeCommand ; 
 scalar_t__ watchCommand ; 
 int writeCommandsDeniedByDiskError () ; 

int processCommand(client *c) {
    moduleCallCommandFilters(c);

    /* The QUIT command is handled separately. Normal command procs will
     * go through checking for replication and QUIT will cause trouble
     * when FORCE_REPLICATION is enabled and would be implemented in
     * a regular command proc. */
    if (!strcasecmp(c->argv[0]->ptr,"quit")) {
        addReply(c,shared.ok);
        c->flags |= CLIENT_CLOSE_AFTER_REPLY;
        return C_ERR;
    }

    /* Now lookup the command and check ASAP about trivial error conditions
     * such as wrong arity, bad command name and so forth. */
    c->cmd = c->lastcmd = lookupCommand(c->argv[0]->ptr);
    if (!c->cmd) {
        flagTransaction(c);
        sds args = sdsempty();
        int i;
        for (i=1; i < c->argc && sdslen(args) < 128; i++)
            args = sdscatprintf(args, "`%.*s`, ", 128-(int)sdslen(args), (char*)c->argv[i]->ptr);
        addReplyErrorFormat(c,"unknown command `%s`, with args beginning with: %s",
            (char*)c->argv[0]->ptr, args);
        sdsfree(args);
        return C_OK;
    } else if ((c->cmd->arity > 0 && c->cmd->arity != c->argc) ||
               (c->argc < -c->cmd->arity)) {
        flagTransaction(c);
        addReplyErrorFormat(c,"wrong number of arguments for '%s' command",
            c->cmd->name);
        return C_OK;
    }

    /* Check if the user is authenticated. This check is skipped in case
     * the default user is flagged as "nopass" and is active. */
    int auth_required = (!(DefaultUser->flags & USER_FLAG_NOPASS) ||
                           DefaultUser->flags & USER_FLAG_DISABLED) &&
                        !c->authenticated;
    if (auth_required) {
        /* AUTH and HELLO are valid even in non authenticated state. */
        if (c->cmd->proc != authCommand && c->cmd->proc != helloCommand) {
            flagTransaction(c);
            addReply(c,shared.noautherr);
            return C_OK;
        }
    }

    /* Check if the user can run this command according to the current
     * ACLs. */
    int acl_retval = ACLCheckCommandPerm(c);
    if (acl_retval != ACL_OK) {
        flagTransaction(c);
        if (acl_retval == ACL_DENIED_CMD)
            addReplyErrorFormat(c,
                "-NOPERM this user has no permissions to run "
                "the '%s' command or its subcommand", c->cmd->name);
        else
            addReplyErrorFormat(c,
                "-NOPERM this user has no permissions to access "
                "one of the keys used as arguments");
        return C_OK;
    }

    /* If cluster is enabled perform the cluster redirection here.
     * However we don't perform the redirection if:
     * 1) The sender of this command is our master.
     * 2) The command has no key arguments. */
    if (server.cluster_enabled &&
        !(c->flags & CLIENT_MASTER) &&
        !(c->flags & CLIENT_LUA &&
          server.lua_caller->flags & CLIENT_MASTER) &&
        !(c->cmd->getkeys_proc == NULL && c->cmd->firstkey == 0 &&
          c->cmd->proc != execCommand))
    {
        int hashslot;
        int error_code;
        clusterNode *n = getNodeByQuery(c,c->cmd,c->argv,c->argc,
                                        &hashslot,&error_code);
        if (n == NULL || n != server.cluster->myself) {
            if (c->cmd->proc == execCommand) {
                discardTransaction(c);
            } else {
                flagTransaction(c);
            }
            clusterRedirectClient(c,n,hashslot,error_code);
            return C_OK;
        }
    }

    /* Handle the maxmemory directive.
     *
     * Note that we do not want to reclaim memory if we are here re-entering
     * the event loop since there is a busy Lua script running in timeout
     * condition, to avoid mixing the propagation of scripts with the
     * propagation of DELs due to eviction. */
    if (server.maxmemory && !server.lua_timedout) {
        int out_of_memory = freeMemoryIfNeededAndSafe() == C_ERR;
        /* freeMemoryIfNeeded may flush slave output buffers. This may result
         * into a slave, that may be the active client, to be freed. */
        if (server.current_client == NULL) return C_ERR;

        /* It was impossible to free enough memory, and the command the client
         * is trying to execute is denied during OOM conditions or the client
         * is in MULTI/EXEC context? Error. */
        if (out_of_memory &&
            (c->cmd->flags & CMD_DENYOOM ||
             (c->flags & CLIENT_MULTI &&
              c->cmd->proc != execCommand &&
              c->cmd->proc != discardCommand)))
        {
            flagTransaction(c);
            addReply(c, shared.oomerr);
            return C_OK;
        }
    }

    /* Make sure to use a reasonable amount of memory for client side
     * caching metadata. */
    if (server.tracking_clients) trackingLimitUsedSlots();

    /* Don't accept write commands if there are problems persisting on disk
     * and if this is a master instance. */
    int deny_write_type = writeCommandsDeniedByDiskError();
    if (deny_write_type != DISK_ERROR_TYPE_NONE &&
        server.masterhost == NULL &&
        (c->cmd->flags & CMD_WRITE ||
         c->cmd->proc == pingCommand))
    {
        flagTransaction(c);
        if (deny_write_type == DISK_ERROR_TYPE_RDB)
            addReply(c, shared.bgsaveerr);
        else
            addReplySds(c,
                sdscatprintf(sdsempty(),
                "-MISCONF Errors writing to the AOF file: %s\r\n",
                strerror(server.aof_last_write_errno)));
        return C_OK;
    }

    /* Don't accept write commands if there are not enough good slaves and
     * user configured the min-slaves-to-write option. */
    if (server.masterhost == NULL &&
        server.repl_min_slaves_to_write &&
        server.repl_min_slaves_max_lag &&
        c->cmd->flags & CMD_WRITE &&
        server.repl_good_slaves_count < server.repl_min_slaves_to_write)
    {
        flagTransaction(c);
        addReply(c, shared.noreplicaserr);
        return C_OK;
    }

    /* Don't accept write commands if this is a read only slave. But
     * accept write commands if this is our master. */
    if (server.masterhost && server.repl_slave_ro &&
        !(c->flags & CLIENT_MASTER) &&
        c->cmd->flags & CMD_WRITE)
    {
        addReply(c, shared.roslaveerr);
        return C_OK;
    }

    /* Only allow a subset of commands in the context of Pub/Sub if the
     * connection is in RESP2 mode. With RESP3 there are no limits. */
    if ((c->flags & CLIENT_PUBSUB && c->resp == 2) &&
        c->cmd->proc != pingCommand &&
        c->cmd->proc != subscribeCommand &&
        c->cmd->proc != unsubscribeCommand &&
        c->cmd->proc != psubscribeCommand &&
        c->cmd->proc != punsubscribeCommand) {
        addReplyError(c,"only (P)SUBSCRIBE / (P)UNSUBSCRIBE / PING / QUIT allowed in this context");
        return C_OK;
    }

    /* Only allow commands with flag "t", such as INFO, SLAVEOF and so on,
     * when slave-serve-stale-data is no and we are a slave with a broken
     * link with master. */
    if (server.masterhost && server.repl_state != REPL_STATE_CONNECTED &&
        server.repl_serve_stale_data == 0 &&
        !(c->cmd->flags & CMD_STALE))
    {
        flagTransaction(c);
        addReply(c, shared.masterdownerr);
        return C_OK;
    }

    /* Loading DB? Return an error if the command has not the
     * CMD_LOADING flag. */
    if (server.loading && !(c->cmd->flags & CMD_LOADING)) {
        addReply(c, shared.loadingerr);
        return C_OK;
    }

    /* Lua script too slow? Only allow a limited number of commands. */
    if (server.lua_timedout &&
          c->cmd->proc != authCommand &&
          c->cmd->proc != helloCommand &&
          c->cmd->proc != replconfCommand &&
        !(c->cmd->proc == shutdownCommand &&
          c->argc == 2 &&
          tolower(((char*)c->argv[1]->ptr)[0]) == 'n') &&
        !(c->cmd->proc == scriptCommand &&
          c->argc == 2 &&
          tolower(((char*)c->argv[1]->ptr)[0]) == 'k'))
    {
        flagTransaction(c);
        addReply(c, shared.slowscripterr);
        return C_OK;
    }

    /* Exec the command */
    if (c->flags & CLIENT_MULTI &&
        c->cmd->proc != execCommand && c->cmd->proc != discardCommand &&
        c->cmd->proc != multiCommand && c->cmd->proc != watchCommand)
    {
        queueMultiCommand(c);
        addReply(c,shared.queued);
    } else {
        call(c,CMD_CALL_FULL);
        c->woff = server.master_repl_offset;
        if (listLength(server.ready_keys))
            handleClientsBlockedOnKeys();
    }
    return C_OK;
}