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
typedef  int /*<<< orphan*/  sqlite3_file ;
struct TYPE_5__ {TYPE_3__* pReal; } ;
typedef  TYPE_2__ VfslogFile ;
struct TYPE_6__ {TYPE_1__* pMethods; } ;
struct TYPE_4__ {int (* xFileControl ) (TYPE_3__*,int,void*) ;} ;

/* Variables and functions */
 int SQLITE_FCNTL_VFSNAME ; 
 int SQLITE_OK ; 
 char* sqlite3_mprintf (char*,char*) ; 
 int stub1 (TYPE_3__*,int,void*) ; 

__attribute__((used)) static int vfslogFileControl(sqlite3_file *pFile, int op, void *pArg){
  VfslogFile *p = (VfslogFile *)pFile;
  int rc = p->pReal->pMethods->xFileControl(p->pReal, op, pArg);
  if( op==SQLITE_FCNTL_VFSNAME && rc==SQLITE_OK ){
    *(char**)pArg = sqlite3_mprintf("vfslog/%z", *(char**)pArg);
  }
  return rc;
}