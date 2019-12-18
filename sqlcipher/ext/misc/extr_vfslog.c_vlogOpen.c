#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vfs ;
typedef  scalar_t__ sqlite3_uint64 ;
typedef  int sqlite3_int64 ;
struct TYPE_7__ {int /*<<< orphan*/ * pMethods; } ;
typedef  TYPE_1__ sqlite3_file ;
struct TYPE_8__ {scalar_t__ pLog; TYPE_1__* pReal; } ;
typedef  TYPE_2__ VLogFile ;
struct TYPE_9__ {int (* xOpen ) (TYPE_4__*,char const*,TYPE_1__*,int,int*) ;} ;

/* Variables and functions */
 TYPE_4__* REALVFS (int /*<<< orphan*/ *) ; 
 int SQLITE_OK ; 
 int SQLITE_OPEN_MAIN_DB ; 
 int SQLITE_OPEN_MAIN_JOURNAL ; 
 int stub1 (TYPE_4__*,char const*,TYPE_1__*,int,int*) ; 
 int /*<<< orphan*/  vlogLogClose (scalar_t__) ; 
 scalar_t__ vlogLogOpen (char const*) ; 
 int /*<<< orphan*/  vlogLogPrint (scalar_t__,scalar_t__,scalar_t__,char*,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vlog_io_methods ; 
 scalar_t__ vlog_time () ; 

__attribute__((used)) static int vlogOpen(
  sqlite3_vfs *pVfs,
  const char *zName,
  sqlite3_file *pFile,
  int flags,
  int *pOutFlags
){
  int rc;
  sqlite3_uint64 tStart, tElapse;
  sqlite3_int64 iArg2;
  VLogFile *p = (VLogFile*)pFile;

  p->pReal = (sqlite3_file*)&p[1];
  if( (flags & (SQLITE_OPEN_MAIN_DB|SQLITE_OPEN_MAIN_JOURNAL))!=0 ){
    p->pLog = vlogLogOpen(zName);
  }else{
    p->pLog = 0;
  }
  tStart = vlog_time();
  rc = REALVFS(pVfs)->xOpen(REALVFS(pVfs), zName, p->pReal, flags, pOutFlags);
  tElapse = vlog_time() - tStart;
  iArg2 = pOutFlags ? *pOutFlags : -1;
  vlogLogPrint(p->pLog, tStart, tElapse, "OPEN", flags, iArg2, 0, rc);
  if( rc==SQLITE_OK ){
    pFile->pMethods = &vlog_io_methods;
  }else{
    if( p->pLog ) vlogLogClose(p->pLog);
    p->pLog = 0;
  }
  return rc;
}