#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* pMethods; } ;
typedef  TYPE_2__ sqlite3_file ;
struct TYPE_7__ {int (* xFileControl ) (TYPE_2__*,int,void*) ;} ;

/* Variables and functions */
 int SQLITE_FCNTL_VFSNAME ; 
 int SQLITE_OK ; 
 TYPE_2__* quotaSubOpen (TYPE_2__*) ; 
 char* sqlite3_mprintf (char*,char*) ; 
 int stub1 (TYPE_2__*,int,void*) ; 

__attribute__((used)) static int quotaFileControl(sqlite3_file *pConn, int op, void *pArg){
  sqlite3_file *pSubOpen = quotaSubOpen(pConn);
  int rc = pSubOpen->pMethods->xFileControl(pSubOpen, op, pArg);
#if defined(SQLITE_FCNTL_VFSNAME)
  if( op==SQLITE_FCNTL_VFSNAME && rc==SQLITE_OK ){
    *(char**)pArg = sqlite3_mprintf("quota/%z", *(char**)pArg);
  }
#endif
  return rc;
}