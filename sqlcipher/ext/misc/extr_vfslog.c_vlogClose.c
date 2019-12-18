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
typedef  scalar_t__ sqlite3_uint64 ;
typedef  int /*<<< orphan*/  sqlite3_file ;
struct TYPE_5__ {int /*<<< orphan*/  pLog; TYPE_3__* pReal; } ;
typedef  TYPE_2__ VLogFile ;
struct TYPE_6__ {TYPE_1__* pMethods; } ;
struct TYPE_4__ {int (* xClose ) (TYPE_3__*) ;} ;

/* Variables and functions */
 int SQLITE_OK ; 
 int stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  vlogLogClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlogLogPrint (int /*<<< orphan*/ ,scalar_t__,scalar_t__,char*,int,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ vlog_time () ; 

__attribute__((used)) static int vlogClose(sqlite3_file *pFile){
  sqlite3_uint64 tStart, tElapse;
  int rc = SQLITE_OK;
  VLogFile *p = (VLogFile *)pFile;

  tStart = vlog_time();
  if( p->pReal->pMethods ){
    rc = p->pReal->pMethods->xClose(p->pReal);
  }
  tElapse = vlog_time() - tStart;
  vlogLogPrint(p->pLog, tStart, tElapse, "CLOSE", -1, -1, 0, rc);
  vlogLogClose(p->pLog);
  return rc;
}