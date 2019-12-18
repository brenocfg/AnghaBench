#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int ustime_t ;
struct redisCommand {int flags; int /*<<< orphan*/  calls; int /*<<< orphan*/  microseconds; int /*<<< orphan*/  (* proc ) (TYPE_4__*) ;} ;
struct TYPE_14__ {int numops; TYPE_3__* ops; } ;
typedef  TYPE_2__ redisOpArray ;
struct TYPE_15__ {int target; int /*<<< orphan*/  argc; int /*<<< orphan*/  argv; int /*<<< orphan*/  dbid; struct redisCommand* cmd; } ;
typedef  TYPE_3__ redisOp ;
struct TYPE_16__ {int flags; struct redisCommand* cmd; int /*<<< orphan*/  argc; int /*<<< orphan*/  argv; TYPE_1__* db; } ;
typedef  TYPE_4__ client ;
struct TYPE_17__ {long long dirty; int ustime; int /*<<< orphan*/  stat_numcommands; int /*<<< orphan*/  call_depth; TYPE_4__* lua_caller; TYPE_2__ also_propagate; scalar_t__ loading; int /*<<< orphan*/  monitors; } ;
struct TYPE_13__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int CLIENT_FORCE_AOF ; 
 int CLIENT_FORCE_REPL ; 
 int CLIENT_LUA ; 
 int CLIENT_PREVENT_AOF_PROP ; 
 int CLIENT_PREVENT_PROP ; 
 int CLIENT_PREVENT_REPL_PROP ; 
 int CLIENT_TRACKING ; 
 int CMD_ADMIN ; 
 int CMD_CALL_PROPAGATE ; 
 int CMD_CALL_PROPAGATE_AOF ; 
 int CMD_CALL_PROPAGATE_REPL ; 
 int CMD_CALL_SLOWLOG ; 
 int CMD_CALL_STATS ; 
 int CMD_FAST ; 
 int CMD_MODULE ; 
 int CMD_READONLY ; 
 int CMD_SKIP_MONITOR ; 
 int CMD_SKIP_SLOWLOG ; 
 int PROPAGATE_AOF ; 
 int PROPAGATE_NONE ; 
 int PROPAGATE_REPL ; 
 int /*<<< orphan*/  latencyAddSampleIfNeeded (char*,int) ; 
 scalar_t__ listLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  propagate (struct redisCommand*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  redisOpArrayFree (TYPE_2__*) ; 
 int /*<<< orphan*/  redisOpArrayInit (TYPE_2__*) ; 
 int /*<<< orphan*/  replicationFeedMonitors (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_8__ server ; 
 int /*<<< orphan*/  slowlogPushEntryIfNeeded (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 
 int /*<<< orphan*/  trackingRememberKeys (TYPE_4__*) ; 
 int /*<<< orphan*/  updateCachedTime (int /*<<< orphan*/ ) ; 
 int ustime () ; 

void call(client *c, int flags) {
    long long dirty;
    ustime_t start, duration;
    int client_old_flags = c->flags;
    struct redisCommand *real_cmd = c->cmd;

    server.call_depth++;

    /* Sent the command to clients in MONITOR mode, only if the commands are
     * not generated from reading an AOF. */
    if (listLength(server.monitors) &&
        !server.loading &&
        !(c->cmd->flags & (CMD_SKIP_MONITOR|CMD_ADMIN)))
    {
        replicationFeedMonitors(c,server.monitors,c->db->id,c->argv,c->argc);
    }

    /* Initialization: clear the flags that must be set by the command on
     * demand, and initialize the array for additional commands propagation. */
    c->flags &= ~(CLIENT_FORCE_AOF|CLIENT_FORCE_REPL|CLIENT_PREVENT_PROP);
    redisOpArray prev_also_propagate = server.also_propagate;
    redisOpArrayInit(&server.also_propagate);

    /* Call the command. */
    dirty = server.dirty;
    updateCachedTime(0);
    start = server.ustime;
    c->cmd->proc(c);
    duration = ustime()-start;
    dirty = server.dirty-dirty;
    if (dirty < 0) dirty = 0;

    /* When EVAL is called loading the AOF we don't want commands called
     * from Lua to go into the slowlog or to populate statistics. */
    if (server.loading && c->flags & CLIENT_LUA)
        flags &= ~(CMD_CALL_SLOWLOG | CMD_CALL_STATS);

    /* If the caller is Lua, we want to force the EVAL caller to propagate
     * the script if the command flag or client flag are forcing the
     * propagation. */
    if (c->flags & CLIENT_LUA && server.lua_caller) {
        if (c->flags & CLIENT_FORCE_REPL)
            server.lua_caller->flags |= CLIENT_FORCE_REPL;
        if (c->flags & CLIENT_FORCE_AOF)
            server.lua_caller->flags |= CLIENT_FORCE_AOF;
    }

    /* Log the command into the Slow log if needed, and populate the
     * per-command statistics that we show in INFO commandstats. */
    if (flags & CMD_CALL_SLOWLOG && !(c->cmd->flags & CMD_SKIP_SLOWLOG)) {
        char *latency_event = (c->cmd->flags & CMD_FAST) ?
                              "fast-command" : "command";
        latencyAddSampleIfNeeded(latency_event,duration/1000);
        slowlogPushEntryIfNeeded(c,c->argv,c->argc,duration);
    }

    if (flags & CMD_CALL_STATS) {
        /* use the real command that was executed (cmd and lastamc) may be
         * different, in case of MULTI-EXEC or re-written commands such as
         * EXPIRE, GEOADD, etc. */
        real_cmd->microseconds += duration;
        real_cmd->calls++;
    }

    /* Propagate the command into the AOF and replication link */
    if (flags & CMD_CALL_PROPAGATE &&
        (c->flags & CLIENT_PREVENT_PROP) != CLIENT_PREVENT_PROP)
    {
        int propagate_flags = PROPAGATE_NONE;

        /* Check if the command operated changes in the data set. If so
         * set for replication / AOF propagation. */
        if (dirty) propagate_flags |= (PROPAGATE_AOF|PROPAGATE_REPL);

        /* If the client forced AOF / replication of the command, set
         * the flags regardless of the command effects on the data set. */
        if (c->flags & CLIENT_FORCE_REPL) propagate_flags |= PROPAGATE_REPL;
        if (c->flags & CLIENT_FORCE_AOF) propagate_flags |= PROPAGATE_AOF;

        /* However prevent AOF / replication propagation if the command
         * implementations called preventCommandPropagation() or similar,
         * or if we don't have the call() flags to do so. */
        if (c->flags & CLIENT_PREVENT_REPL_PROP ||
            !(flags & CMD_CALL_PROPAGATE_REPL))
                propagate_flags &= ~PROPAGATE_REPL;
        if (c->flags & CLIENT_PREVENT_AOF_PROP ||
            !(flags & CMD_CALL_PROPAGATE_AOF))
                propagate_flags &= ~PROPAGATE_AOF;

        /* Call propagate() only if at least one of AOF / replication
         * propagation is needed. Note that modules commands handle replication
         * in an explicit way, so we never replicate them automatically. */
        if (propagate_flags != PROPAGATE_NONE && !(c->cmd->flags & CMD_MODULE))
            propagate(c->cmd,c->db->id,c->argv,c->argc,propagate_flags);
    }

    /* Restore the old replication flags, since call() can be executed
     * recursively. */
    c->flags &= ~(CLIENT_FORCE_AOF|CLIENT_FORCE_REPL|CLIENT_PREVENT_PROP);
    c->flags |= client_old_flags &
        (CLIENT_FORCE_AOF|CLIENT_FORCE_REPL|CLIENT_PREVENT_PROP);

    /* Handle the alsoPropagate() API to handle commands that want to propagate
     * multiple separated commands. Note that alsoPropagate() is not affected
     * by CLIENT_PREVENT_PROP flag. */
    if (server.also_propagate.numops) {
        int j;
        redisOp *rop;

        if (flags & CMD_CALL_PROPAGATE) {
            for (j = 0; j < server.also_propagate.numops; j++) {
                rop = &server.also_propagate.ops[j];
                int target = rop->target;
                /* Whatever the command wish is, we honor the call() flags. */
                if (!(flags&CMD_CALL_PROPAGATE_AOF)) target &= ~PROPAGATE_AOF;
                if (!(flags&CMD_CALL_PROPAGATE_REPL)) target &= ~PROPAGATE_REPL;
                if (target)
                    propagate(rop->cmd,rop->dbid,rop->argv,rop->argc,target);
            }
        }
        redisOpArrayFree(&server.also_propagate);
    }
    server.also_propagate = prev_also_propagate;

    /* If the client has keys tracking enabled for client side caching,
     * make sure to remember the keys it fetched via this command. */
    if (c->cmd->flags & CMD_READONLY) {
        client *caller = (c->flags & CLIENT_LUA && server.lua_caller) ?
                            server.lua_caller : c;
        if (caller->flags & CLIENT_TRACKING)
            trackingRememberKeys(caller);
    }

    server.call_depth--;
    server.stat_numcommands++;
}