#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  expires; int /*<<< orphan*/  dict; } ;
typedef  TYPE_1__ redisDb ;
struct TYPE_7__ {int dbnum; TYPE_1__* db; } ;

/* Variables and functions */
 int /*<<< orphan*/  dictRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emptyDbGeneric (TYPE_1__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  replicationEmptyDbCallback ; 
 TYPE_3__ server ; 
 int /*<<< orphan*/  zfree (TYPE_1__*) ; 

void disklessLoadRestoreBackups(redisDb *backup, int restore, int empty_db_flags)
{
    if (restore) {
        /* Restore. */
        emptyDbGeneric(server.db,-1,empty_db_flags,replicationEmptyDbCallback);
        for (int i=0; i<server.dbnum; i++) {
            dictRelease(server.db[i].dict);
            dictRelease(server.db[i].expires);
            server.db[i] = backup[i];
        }
    } else {
        /* Delete. */
        emptyDbGeneric(backup,-1,empty_db_flags,replicationEmptyDbCallback);
        for (int i=0; i<server.dbnum; i++) {
            dictRelease(backup[i].dict);
            dictRelease(backup[i].expires);
        }
    }
    zfree(backup);
}