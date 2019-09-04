#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vfs ;
typedef  scalar_t__ sqlite3_uint64 ;
typedef  int /*<<< orphan*/  VLogLog ;
struct TYPE_3__ {int (* xDelete ) (TYPE_1__*,char const*,int) ;} ;

/* Variables and functions */
 TYPE_1__* REALVFS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VLOG_OP_DELETE ; 
 int stub1 (TYPE_1__*,char const*,int) ; 
 int /*<<< orphan*/  vlogLogClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlogLogOpen (char const*) ; 
 int /*<<< orphan*/  vlogLogPrint (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ vlog_time () ; 

__attribute__((used)) static int vlogDelete(sqlite3_vfs *pVfs, const char *zPath, int dirSync)
{
    int rc;
    sqlite3_uint64 tStart, tElapse;
    VLogLog *pLog;
    tStart = vlog_time();
    rc = REALVFS(pVfs)->xDelete(REALVFS(pVfs), zPath, dirSync);
    tElapse = vlog_time() - tStart;
    pLog = vlogLogOpen(zPath);
    vlogLogPrint(pLog, tStart, tElapse, VLOG_OP_DELETE, dirSync, -1, 0, rc);
    vlogLogClose(pLog);
    return rc;
}