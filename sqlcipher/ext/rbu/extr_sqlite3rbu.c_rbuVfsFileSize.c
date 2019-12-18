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
typedef  int sqlite_int64 ;
typedef  int /*<<< orphan*/  sqlite3_file ;
struct TYPE_5__ {int openFlags; scalar_t__ pRbu; TYPE_3__* pReal; } ;
typedef  TYPE_2__ rbu_file ;
struct TYPE_6__ {TYPE_1__* pMethods; } ;
struct TYPE_4__ {int (* xFileSize ) (TYPE_3__*,int*) ;} ;

/* Variables and functions */
 int SQLITE_OK ; 
 int SQLITE_OPEN_MAIN_DB ; 
 scalar_t__ rbuIsVacuum (scalar_t__) ; 
 int stub1 (TYPE_3__*,int*) ; 

__attribute__((used)) static int rbuVfsFileSize(sqlite3_file *pFile, sqlite_int64 *pSize){
  rbu_file *p = (rbu_file *)pFile;
  int rc;
  rc = p->pReal->pMethods->xFileSize(p->pReal, pSize);

  /* If this is an RBU vacuum operation and this is the target database,
  ** pretend that it has at least one page. Otherwise, SQLite will not
  ** check for the existance of a *-wal file. rbuVfsRead() contains 
  ** similar logic.  */
  if( rc==SQLITE_OK && *pSize==0 
   && p->pRbu && rbuIsVacuum(p->pRbu) 
   && (p->openFlags & SQLITE_OPEN_MAIN_DB)
  ){
    *pSize = 1024;
  }
  return rc;
}