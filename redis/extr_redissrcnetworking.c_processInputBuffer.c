#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {size_t qb_pos; char* querybuf; int flags; scalar_t__ reqtype; int argc; size_t reploff; size_t read_reploff; scalar_t__ btype; TYPE_1__** argv; } ;
typedef  TYPE_2__ client ;
struct TYPE_12__ {TYPE_2__* current_client; scalar_t__ gopher_enabled; scalar_t__ lua_timedout; } ;
struct TYPE_10__ {scalar_t__ ptr; } ;

/* Variables and functions */
 scalar_t__ BLOCKED_MODULE ; 
 int CLIENT_BLOCKED ; 
 int CLIENT_CLOSE_AFTER_REPLY ; 
 int CLIENT_CLOSE_ASAP ; 
 int CLIENT_MASTER ; 
 int CLIENT_MULTI ; 
 int CLIENT_SLAVE ; 
 scalar_t__ C_OK ; 
 scalar_t__ PROTO_REQ_INLINE ; 
 scalar_t__ PROTO_REQ_MULTIBULK ; 
 scalar_t__ clientsArePaused () ; 
 scalar_t__ processCommand (TYPE_2__*) ; 
 int /*<<< orphan*/  processGopherRequest (TYPE_2__*) ; 
 scalar_t__ processInlineBuffer (TYPE_2__*) ; 
 scalar_t__ processMultibulkBuffer (TYPE_2__*) ; 
 int /*<<< orphan*/  resetClient (TYPE_2__*) ; 
 size_t sdslen (char*) ; 
 int /*<<< orphan*/  sdsrange (char*,size_t,int) ; 
 TYPE_3__ server ; 
 int /*<<< orphan*/  serverPanic (char*) ; 

void processInputBuffer(client *c) {
    server.current_client = c;

    /* Keep processing while there is something in the input buffer */
    while(c->qb_pos < sdslen(c->querybuf)) {
        /* Return if clients are paused. */
        if (!(c->flags & CLIENT_SLAVE) && clientsArePaused()) break;

        /* Immediately abort if the client is in the middle of something. */
        if (c->flags & CLIENT_BLOCKED) break;

        /* Don't process input from the master while there is a busy script
         * condition on the slave. We want just to accumulate the replication
         * stream (instead of replying -BUSY like we do with other clients) and
         * later resume the processing. */
        if (server.lua_timedout && c->flags & CLIENT_MASTER) break;

        /* CLIENT_CLOSE_AFTER_REPLY closes the connection once the reply is
         * written to the client. Make sure to not let the reply grow after
         * this flag has been set (i.e. don't process more commands).
         *
         * The same applies for clients we want to terminate ASAP. */
        if (c->flags & (CLIENT_CLOSE_AFTER_REPLY|CLIENT_CLOSE_ASAP)) break;

        /* Determine request type when unknown. */
        if (!c->reqtype) {
            if (c->querybuf[c->qb_pos] == '*') {
                c->reqtype = PROTO_REQ_MULTIBULK;
            } else {
                c->reqtype = PROTO_REQ_INLINE;
            }
        }

        if (c->reqtype == PROTO_REQ_INLINE) {
            if (processInlineBuffer(c) != C_OK) break;
            /* If the Gopher mode and we got zero or one argument, process
             * the request in Gopher mode. */
            if (server.gopher_enabled &&
                ((c->argc == 1 && ((char*)(c->argv[0]->ptr))[0] == '/') ||
                  c->argc == 0))
            {
                processGopherRequest(c);
                resetClient(c);
                c->flags |= CLIENT_CLOSE_AFTER_REPLY;
                break;
            }
        } else if (c->reqtype == PROTO_REQ_MULTIBULK) {
            if (processMultibulkBuffer(c) != C_OK) break;
        } else {
            serverPanic("Unknown request type");
        }

        /* Multibulk processing could see a <= 0 length. */
        if (c->argc == 0) {
            resetClient(c);
        } else {
            /* Only reset the client when the command was executed. */
            if (processCommand(c) == C_OK) {
                if (c->flags & CLIENT_MASTER && !(c->flags & CLIENT_MULTI)) {
                    /* Update the applied replication offset of our master. */
                    c->reploff = c->read_reploff - sdslen(c->querybuf) + c->qb_pos;
                }

                /* Don't reset the client structure for clients blocked in a
                 * module blocking command, so that the reply callback will
                 * still be able to access the client argv and argc field.
                 * The client will be reset in unblockClientFromModule(). */
                if (!(c->flags & CLIENT_BLOCKED) || c->btype != BLOCKED_MODULE)
                    resetClient(c);
            }
            /* freeMemoryIfNeeded may flush slave output buffers. This may
             * result into a slave, that may be the active client, to be
             * freed. */
            if (server.current_client == NULL) break;
        }
    }

    /* Trim to pos */
    if (server.current_client != NULL && c->qb_pos) {
        sdsrange(c->querybuf,c->qb_pos,-1);
        c->qb_pos = 0;
    }

    server.current_client = NULL;
}