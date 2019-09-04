#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sds ;
struct TYPE_18__ {char* ptr; } ;
typedef  TYPE_2__ robj ;
struct TYPE_19__ {int fd; int last_dbid; int /*<<< orphan*/  last_use_time; } ;
typedef  TYPE_3__ migrateCachedSocket ;
typedef  int /*<<< orphan*/  dictEntry ;
struct TYPE_20__ {TYPE_1__** argv; } ;
typedef  TYPE_4__ client ;
struct TYPE_21__ {int /*<<< orphan*/  migrate_cached_sockets; int /*<<< orphan*/  unixtime; int /*<<< orphan*/  neterr; } ;
struct TYPE_17__ {int /*<<< orphan*/  ptr; } ;

/* Variables and functions */
 int AE_WRITABLE ; 
 scalar_t__ MIGRATE_SOCKET_CACHE_ITEMS ; 
 int /*<<< orphan*/  addReplyErrorFormat (TYPE_4__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplySds (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int aeWait (int,int,long) ; 
 int /*<<< orphan*/  anetEnableTcpNoDelay (int /*<<< orphan*/ ,int) ; 
 int anetTcpNonBlockConnect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
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
    int fd;
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
        close(cs->fd);
        zfree(cs);
        dictDelete(server.migrate_cached_sockets,dictGetKey(de));
    }

    /* Create the socket */
    fd = anetTcpNonBlockConnect(server.neterr,c->argv[1]->ptr,
                                atoi(c->argv[2]->ptr));
    if (fd == -1) {
        sdsfree(name);
        addReplyErrorFormat(c,"Can't connect to target node: %s",
            server.neterr);
        return NULL;
    }
    anetEnableTcpNoDelay(server.neterr,fd);

    /* Check if it connects within the specified timeout. */
    if ((aeWait(fd,AE_WRITABLE,timeout) & AE_WRITABLE) == 0) {
        sdsfree(name);
        addReplySds(c,
            sdsnew("-IOERR error or timeout connecting to the client\r\n"));
        close(fd);
        return NULL;
    }

    /* Add to the cache and return it to the caller. */
    cs = zmalloc(sizeof(*cs));
    cs->fd = fd;
    cs->last_dbid = -1;
    cs->last_use_time = server.unixtime;
    dictAdd(server.migrate_cached_sockets,name,cs);
    return cs;
}