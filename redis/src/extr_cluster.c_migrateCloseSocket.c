#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sds ;
struct TYPE_8__ {char* ptr; } ;
typedef  TYPE_1__ robj ;
struct TYPE_9__ {int /*<<< orphan*/  conn; } ;
typedef  TYPE_2__ migrateCachedSocket ;
struct TYPE_10__ {int /*<<< orphan*/  migrate_cached_sockets; } ;

/* Variables and functions */
 int /*<<< orphan*/  connClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dictDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* dictFetchValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdscatlen (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sdsempty () ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 
 int sdslen (char*) ; 
 TYPE_4__ server ; 
 int /*<<< orphan*/  zfree (TYPE_2__*) ; 

void migrateCloseSocket(robj *host, robj *port) {
    sds name = sdsempty();
    migrateCachedSocket *cs;

    name = sdscatlen(name,host->ptr,sdslen(host->ptr));
    name = sdscatlen(name,":",1);
    name = sdscatlen(name,port->ptr,sdslen(port->ptr));
    cs = dictFetchValue(server.migrate_cached_sockets,name);
    if (!cs) {
        sdsfree(name);
        return;
    }

    connClose(cs->conn);
    zfree(cs);
    dictDelete(server.migrate_cached_sockets,name);
    sdsfree(name);
}