#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_47__   TYPE_8__ ;
typedef  struct TYPE_46__   TYPE_5__ ;
typedef  struct TYPE_45__   TYPE_4__ ;
typedef  struct TYPE_44__   TYPE_3__ ;
typedef  struct TYPE_43__   TYPE_2__ ;
typedef  struct TYPE_42__   TYPE_24__ ;
typedef  struct TYPE_41__   TYPE_21__ ;
typedef  struct TYPE_40__   TYPE_20__ ;
typedef  struct TYPE_39__   TYPE_1__ ;

/* Type definitions */
struct TYPE_39__ {scalar_t__ seq; scalar_t__ ms; } ;
typedef  TYPE_1__ streamID ;
struct TYPE_43__ {TYPE_1__ last_id; } ;
typedef  TYPE_2__ streamCG ;
struct TYPE_44__ {int /*<<< orphan*/  cgroups; TYPE_1__ last_id; } ;
typedef  TYPE_3__ stream ;
typedef  char* sds ;
struct TYPE_45__ {TYPE_3__* ptr; } ;
typedef  TYPE_4__ robj ;
struct TYPE_46__ {int argc; TYPE_24__* db; TYPE_8__** argv; } ;
typedef  TYPE_5__ client ;
struct TYPE_47__ {char* ptr; } ;
struct TYPE_42__ {int /*<<< orphan*/  id; } ;
struct TYPE_41__ {int /*<<< orphan*/  dirty; } ;
struct TYPE_40__ {int /*<<< orphan*/  czero; int /*<<< orphan*/  cone; int /*<<< orphan*/  ok; } ;

/* Variables and functions */
 scalar_t__ C_OK ; 
 int /*<<< orphan*/  NOTIFY_STREAM ; 
 int /*<<< orphan*/  OBJ_STREAM ; 
 int /*<<< orphan*/  addReply (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyError (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  addReplyErrorFormat (TYPE_5__*,char*,char*,char*) ; 
 int /*<<< orphan*/  addReplyHelp (TYPE_5__*,char const**) ; 
 int /*<<< orphan*/  addReplyLongLong (TYPE_5__*,long long) ; 
 int /*<<< orphan*/  addReplySds (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplySubcommandSyntaxError (TYPE_5__*) ; 
 scalar_t__ checkType (TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* createStreamObject () ; 
 int /*<<< orphan*/  dbAdd (TYPE_24__*,TYPE_8__*,TYPE_4__*) ; 
 TYPE_4__* lookupKeyWrite (TYPE_24__*,TYPE_8__*) ; 
 int /*<<< orphan*/  notifyKeyspaceEvent (int /*<<< orphan*/ ,char*,TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raxRemove (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdslen (char*) ; 
 int /*<<< orphan*/  sdsnew (char*) ; 
 TYPE_21__ server ; 
 int /*<<< orphan*/  serverAssert (int) ; 
 TYPE_20__ shared ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 TYPE_2__* streamCreateCG (TYPE_3__*,char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 long long streamDelConsumer (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  streamFreeCG (TYPE_2__*) ; 
 TYPE_2__* streamLookupCG (TYPE_3__*,char*) ; 
 scalar_t__ streamParseIDOrReply (TYPE_5__*,TYPE_8__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ streamParseStrictIDOrReply (TYPE_5__*,TYPE_8__*,TYPE_1__*,int /*<<< orphan*/ ) ; 

void xgroupCommand(client *c) {
    const char *help[] = {
"CREATE      <key> <groupname> <id or $> [opt] -- Create a new consumer group.",
"            option MKSTREAM: create the empty stream if it does not exist.",
"SETID       <key> <groupname> <id or $>  -- Set the current group ID.",
"DESTROY     <key> <groupname>            -- Remove the specified group.",
"DELCONSUMER <key> <groupname> <consumer> -- Remove the specified consumer.",
"HELP                                     -- Prints this help.",
NULL
    };
    stream *s = NULL;
    sds grpname = NULL;
    streamCG *cg = NULL;
    char *opt = c->argv[1]->ptr; /* Subcommand name. */
    int mkstream = 0;
    robj *o;

    /* CREATE has an MKSTREAM option that creates the stream if it
     * does not exist. */
    if (c->argc == 6 && !strcasecmp(opt,"CREATE")) {
        if (strcasecmp(c->argv[5]->ptr,"MKSTREAM")) {
            addReplySubcommandSyntaxError(c);
            return;
        }
        mkstream = 1;
        grpname = c->argv[3]->ptr;
    }

    /* Everything but the "HELP" option requires a key and group name. */
    if (c->argc >= 4) {
        o = lookupKeyWrite(c->db,c->argv[2]);
        if (o) {
            if (checkType(c,o,OBJ_STREAM)) return;
            s = o->ptr;
        }
        grpname = c->argv[3]->ptr;
    }

    /* Check for missing key/group. */
    if (c->argc >= 4 && !mkstream) {
        /* At this point key must exist, or there is an error. */
        if (s == NULL) {
            addReplyError(c,
                "The XGROUP subcommand requires the key to exist. "
                "Note that for CREATE you may want to use the MKSTREAM "
                "option to create an empty stream automatically.");
            return;
        }

        /* Certain subcommands require the group to exist. */
        if ((cg = streamLookupCG(s,grpname)) == NULL &&
            (!strcasecmp(opt,"SETID") ||
             !strcasecmp(opt,"DELCONSUMER")))
        {
            addReplyErrorFormat(c, "-NOGROUP No such consumer group '%s' "
                                   "for key name '%s'",
                                   (char*)grpname, (char*)c->argv[2]->ptr);
            return;
        }
    }

    /* Dispatch the different subcommands. */
    if (!strcasecmp(opt,"CREATE") && (c->argc == 5 || c->argc == 6)) {
        streamID id;
        if (!strcmp(c->argv[4]->ptr,"$")) {
            if (s) {
                id = s->last_id;
            } else {
                id.ms = 0;
                id.seq = 0;
            }
        } else if (streamParseStrictIDOrReply(c,c->argv[4],&id,0) != C_OK) {
            return;
        }

        /* Handle the MKSTREAM option now that the command can no longer fail. */
        if (s == NULL) {
            serverAssert(mkstream);
            o = createStreamObject();
            dbAdd(c->db,c->argv[2],o);
            s = o->ptr;
        }

        streamCG *cg = streamCreateCG(s,grpname,sdslen(grpname),&id);
        if (cg) {
            addReply(c,shared.ok);
            server.dirty++;
            notifyKeyspaceEvent(NOTIFY_STREAM,"xgroup-create",
                                c->argv[2],c->db->id);
        } else {
            addReplySds(c,
                sdsnew("-BUSYGROUP Consumer Group name already exists\r\n"));
        }
    } else if (!strcasecmp(opt,"SETID") && c->argc == 5) {
        streamID id;
        if (!strcmp(c->argv[4]->ptr,"$")) {
            id = s->last_id;
        } else if (streamParseIDOrReply(c,c->argv[4],&id,0) != C_OK) {
            return;
        }
        cg->last_id = id;
        addReply(c,shared.ok);
        server.dirty++;
        notifyKeyspaceEvent(NOTIFY_STREAM,"xgroup-setid",c->argv[2],c->db->id);
    } else if (!strcasecmp(opt,"DESTROY") && c->argc == 4) {
        if (cg) {
            raxRemove(s->cgroups,(unsigned char*)grpname,sdslen(grpname),NULL);
            streamFreeCG(cg);
            addReply(c,shared.cone);
            server.dirty++;
            notifyKeyspaceEvent(NOTIFY_STREAM,"xgroup-destroy",
                                c->argv[2],c->db->id);
        } else {
            addReply(c,shared.czero);
        }
    } else if (!strcasecmp(opt,"DELCONSUMER") && c->argc == 5) {
        /* Delete the consumer and returns the number of pending messages
         * that were yet associated with such a consumer. */
        long long pending = streamDelConsumer(cg,c->argv[4]->ptr);
        addReplyLongLong(c,pending);
        server.dirty++;
        notifyKeyspaceEvent(NOTIFY_STREAM,"xgroup-delconsumer",
                            c->argv[2],c->db->id);
    } else if (!strcasecmp(opt,"HELP")) {
        addReplyHelp(c, help);
    } else {
        addReplySubcommandSyntaxError(c);
    }
}