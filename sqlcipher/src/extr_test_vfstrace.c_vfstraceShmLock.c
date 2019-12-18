#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zLck ;
struct TYPE_8__ {int /*<<< orphan*/  zVfsName; } ;
typedef  TYPE_2__ vfstrace_info ;
struct TYPE_9__ {TYPE_6__* pReal; int /*<<< orphan*/  zFName; TYPE_2__* pInfo; } ;
typedef  TYPE_3__ vfstrace_file ;
typedef  int /*<<< orphan*/  sqlite3_file ;
struct TYPE_10__ {TYPE_1__* pMethods; } ;
struct TYPE_7__ {int (* xShmLock ) (TYPE_6__*,int,int,int) ;} ;

/* Variables and functions */
 int SQLITE_SHM_EXCLUSIVE ; 
 int SQLITE_SHM_LOCK ; 
 int SQLITE_SHM_SHARED ; 
 int SQLITE_SHM_UNLOCK ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  sqlite3_snprintf (int,char*,char*,int) ; 
 int /*<<< orphan*/  strappend (char*,int*,char*) ; 
 int stub1 (TYPE_6__*,int,int,int) ; 
 int /*<<< orphan*/  vfstrace_print_errcode (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  vfstrace_printf (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,char*) ; 

__attribute__((used)) static int vfstraceShmLock(sqlite3_file *pFile, int ofst, int n, int flags){
  vfstrace_file *p = (vfstrace_file *)pFile;
  vfstrace_info *pInfo = p->pInfo;
  int rc;
  char zLck[100];
  int i = 0;
  memcpy(zLck, "|0", 3);
  if( flags & SQLITE_SHM_UNLOCK )    strappend(zLck, &i, "|UNLOCK");
  if( flags & SQLITE_SHM_LOCK )      strappend(zLck, &i, "|LOCK");
  if( flags & SQLITE_SHM_SHARED )    strappend(zLck, &i, "|SHARED");
  if( flags & SQLITE_SHM_EXCLUSIVE ) strappend(zLck, &i, "|EXCLUSIVE");
  if( flags & ~(0xf) ){
     sqlite3_snprintf(sizeof(zLck)-i, &zLck[i], "|0x%x", flags);
  }
  vfstrace_printf(pInfo, "%s.xShmLock(%s,ofst=%d,n=%d,%s)",
                  pInfo->zVfsName, p->zFName, ofst, n, &zLck[1]);
  rc = p->pReal->pMethods->xShmLock(p->pReal, ofst, n, flags);
  vfstrace_print_errcode(pInfo, " -> %s\n", rc);
  return rc;
}