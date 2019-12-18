#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sds ;
typedef  int /*<<< orphan*/  conninfo ;
struct TYPE_13__ {int count; } ;
struct TYPE_16__ {int flags; TYPE_5__* user; TYPE_4__* lastcmd; int /*<<< orphan*/  reply; scalar_t__ bufpos; int /*<<< orphan*/  querybuf; TYPE_3__ mstate; int /*<<< orphan*/  pubsub_patterns; int /*<<< orphan*/  pubsub_channels; TYPE_2__* db; scalar_t__ lastinteraction; scalar_t__ ctime; TYPE_1__* name; scalar_t__ conn; scalar_t__ id; } ;
typedef  TYPE_6__ client ;
struct TYPE_17__ {scalar_t__ unixtime; } ;
struct TYPE_15__ {char* name; } ;
struct TYPE_14__ {char* name; } ;
struct TYPE_12__ {int /*<<< orphan*/  id; } ;
struct TYPE_11__ {scalar_t__ ptr; } ;

/* Variables and functions */
 int CLIENT_BLOCKED ; 
 int CLIENT_CLOSE_AFTER_REPLY ; 
 int CLIENT_CLOSE_ASAP ; 
 int CLIENT_DIRTY_CAS ; 
 int CLIENT_MASTER ; 
 int CLIENT_MONITOR ; 
 int CLIENT_MULTI ; 
 int CLIENT_PUBSUB ; 
 int CLIENT_READONLY ; 
 int CLIENT_SLAVE ; 
 int CLIENT_TRACKING ; 
 int CLIENT_TRACKING_BROKEN_REDIR ; 
 int CLIENT_UNBLOCKED ; 
 int CLIENT_UNIX_SOCKET ; 
 int CONN_INFO_LEN ; 
 int /*<<< orphan*/  connGetInfo (scalar_t__,char*,int) ; 
 scalar_t__ connHasReadHandler (scalar_t__) ; 
 scalar_t__ connHasWriteHandler (scalar_t__) ; 
 scalar_t__ dictSize (int /*<<< orphan*/ ) ; 
 scalar_t__ getClientOutputBufferMemoryUsage (TYPE_6__*) ; 
 int /*<<< orphan*/  getClientPeerId (TYPE_6__*) ; 
 scalar_t__ listLength (int /*<<< orphan*/ ) ; 
 scalar_t__ sdsavail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdscatfmt (int /*<<< orphan*/ ,char*,unsigned long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,long long,long long,char*,int /*<<< orphan*/ ,int,int,int,unsigned long long,unsigned long long,unsigned long long,unsigned long long,unsigned long long,char*,char*,char*) ; 
 scalar_t__ sdslen (int /*<<< orphan*/ ) ; 
 TYPE_7__ server ; 

sds catClientInfoString(sds s, client *client) {
    char flags[16], events[3], conninfo[CONN_INFO_LEN], *p;

    p = flags;
    if (client->flags & CLIENT_SLAVE) {
        if (client->flags & CLIENT_MONITOR)
            *p++ = 'O';
        else
            *p++ = 'S';
    }
    if (client->flags & CLIENT_MASTER) *p++ = 'M';
    if (client->flags & CLIENT_PUBSUB) *p++ = 'P';
    if (client->flags & CLIENT_MULTI) *p++ = 'x';
    if (client->flags & CLIENT_BLOCKED) *p++ = 'b';
    if (client->flags & CLIENT_TRACKING) *p++ = 't';
    if (client->flags & CLIENT_TRACKING_BROKEN_REDIR) *p++ = 'R';
    if (client->flags & CLIENT_DIRTY_CAS) *p++ = 'd';
    if (client->flags & CLIENT_CLOSE_AFTER_REPLY) *p++ = 'c';
    if (client->flags & CLIENT_UNBLOCKED) *p++ = 'u';
    if (client->flags & CLIENT_CLOSE_ASAP) *p++ = 'A';
    if (client->flags & CLIENT_UNIX_SOCKET) *p++ = 'U';
    if (client->flags & CLIENT_READONLY) *p++ = 'r';
    if (p == flags) *p++ = 'N';
    *p++ = '\0';

    p = events;
    if (client->conn) {
        if (connHasReadHandler(client->conn)) *p++ = 'r';
        if (connHasWriteHandler(client->conn)) *p++ = 'w';
    }
    *p = '\0';
    return sdscatfmt(s,
        "id=%U addr=%s %s name=%s age=%I idle=%I flags=%s db=%i sub=%i psub=%i multi=%i qbuf=%U qbuf-free=%U obl=%U oll=%U omem=%U events=%s cmd=%s user=%s",
        (unsigned long long) client->id,
        getClientPeerId(client),
        connGetInfo(client->conn, conninfo, sizeof(conninfo)),
        client->name ? (char*)client->name->ptr : "",
        (long long)(server.unixtime - client->ctime),
        (long long)(server.unixtime - client->lastinteraction),
        flags,
        client->db->id,
        (int) dictSize(client->pubsub_channels),
        (int) listLength(client->pubsub_patterns),
        (client->flags & CLIENT_MULTI) ? client->mstate.count : -1,
        (unsigned long long) sdslen(client->querybuf),
        (unsigned long long) sdsavail(client->querybuf),
        (unsigned long long) client->bufpos,
        (unsigned long long) listLength(client->reply),
        (unsigned long long) getClientOutputBufferMemoryUsage(client),
        events,
        client->lastcmd ? client->lastcmd->name : "NULL",
        client->user ? client->user->name : "(superuser)");
}