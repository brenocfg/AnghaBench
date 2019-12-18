#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sds ;
struct TYPE_17__ {char* ptr; } ;
typedef  TYPE_2__ robj ;
struct TYPE_18__ {int last_dbid; int /*<<< orphan*/  last_use_time; int /*<<< orphan*/ * conn; } ;
typedef  TYPE_3__ migrateCachedSocket ;
typedef  int /*<<< orphan*/  dictEntry ;
typedef  int /*<<< orphan*/  connection ;
struct TYPE_19__ {TYPE_1__** argv; } ;
typedef  TYPE_4__ client ;
struct TYPE_20__ {int /*<<< orphan*/  migrate_cached_sockets; int /*<<< orphan*/  unixtime; scalar_t__ tls_cluster; } ;
struct TYPE_16__ {int /*<<< orphan*/  ptr; } ;

/* Variables and functions */
 scalar_t__ C_OK ; 
 scalar_t__ MIGRATE_SOCKET_CACHE_ITEMS ; 
 int /*<<< orphan*/  addReplySds (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atoi (int /*<<< orphan*/ ) ; 
 scalar_t__ connBlockingConnect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  connClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * connCreateSocket () ; 
 int /*<<< orphan*/ * connCreateTLS () ; 
 int /*<<< orphan*/  connEnableTcpNoDelay (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictAdd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  dictDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* dictFetchValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dictGetKey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictGetRandomKey (int /*<<< orphan*/ ) ; 
 TYPE_3__* dictGetVal (int /*<<< orphan*/ *) ; 
 scalar_t__ dictSize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdscatlen (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sdsempty () ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 
 int sdslen (char*) ; 
 int /*<<< orphan*/  sdsnew (char*) ; 
 TYPE_7__ server ; 
 int /*<<< orphan*/  zfree (TYPE_3__*) ; 
 TYPE_3__* zmalloc (int) ; 

migrateCachedSocket* migrateGetSocket(client *c, robj *host, robj *port, long timeout) {
    connection *conn;
    sds name = sdsempty();
    migrateCachedSocket *cs;

    /* Check if we have an already cached socket for this ip:port pair. */
    name = sdscatlen(name,host->ptr,sdslen(host->ptr));
    name = sdscatlen(name,":",1);
    name = sdscatlen(name,port->ptr,sdslen(port->ptr));
    cs = dictFetchValue(server.migrate_cached_sockets,name);
    if (cs) {
        sdsfree(name);
        cs->last_use_time = server.unixtime;
        return cs;
    }

    /* No cached socket, create one. */
    if (dictSize(server.migrate_cached_sockets) == MIGRATE_SOCKET_CACHE_ITEMS) {
        /* Too many items, drop one at random. */
        dictEntry *de = dictGetRandomKey(server.migrate_cached_sockets);
        cs = dictGetVal(de);
        connClose(cs->conn);
        zfree(cs);
        dictDelete(server.migrate_cached_sockets,dictGetKey(de));
    }

    /* Create the socket */
    conn = server.tls_cluster ? connCreateTLS() : connCreateSocket();
    if (connBlockingConnect(conn, c->argv[1]->ptr, atoi(c->argv[2]->ptr), timeout)
            != C_OK) {
        addReplySds(c,
            sdsnew("-IOERR error or timeout connecting to the client\r\n"));
        connClose(conn);
        sdsfree(name);
        return NULL;
    }
    connEnableTcpNoDelay(conn);

    /* Add to the cache and return it to the caller. */
    cs = zmalloc(sizeof(*cs));
    cs->conn = conn;

    cs->last_dbid = -1;
    cs->last_use_time = server.unixtime;
    dictAdd(server.migrate_cached_sockets,name,cs);
    return cs;
}