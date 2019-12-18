#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_uint64 ;
typedef  int /*<<< orphan*/  sqlite3_file ;
struct TYPE_5__ {TYPE_3__* pReal; int /*<<< orphan*/  pLog; } ;
typedef  TYPE_2__ VLogFile ;
struct TYPE_6__ {TYPE_1__* pMethods; } ;
struct TYPE_4__ {int (* xUnlock ) (TYPE_3__*,int) ;} ;

/* Variables and functions */
 int stub1 (TYPE_3__*,int) ; 
 int /*<<< orphan*/  vlogLogPrint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlog_time () ; 

__attribute__((used)) static int vlogUnlock(sqlite3_file *pFile, int eLock){
  int rc;
  sqlite3_uint64 tStart;
  VLogFile *p = (VLogFile *)pFile;
  tStart = vlog_time();
  vlogLogPrint(p->pLog, tStart, 0, "UNLOCK", eLock, -1, 0, 0);
  rc = p->pReal->pMethods->xUnlock(p->pReal, eLock);
  return rc;
}