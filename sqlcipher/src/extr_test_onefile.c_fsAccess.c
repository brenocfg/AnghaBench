#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int (* xAccess ) (TYPE_1__*,char const*,int,int*) ;} ;
typedef  TYPE_1__ sqlite3_vfs ;
struct TYPE_7__ {TYPE_3__* pFileList; TYPE_1__* pParent; } ;
typedef  TYPE_2__ fs_vfs_t ;
struct TYPE_8__ {scalar_t__ nJournal; struct TYPE_8__* pNext; int /*<<< orphan*/  zName; } ;
typedef  TYPE_3__ fs_real_file ;

/* Variables and functions */
 int SQLITE_ACCESS_EXISTS ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char const*,int) ; 
 int stub1 (TYPE_1__*,char const*,int,int*) ; 

__attribute__((used)) static int fsAccess(
  sqlite3_vfs *pVfs, 
  const char *zPath, 
  int flags, 
  int *pResOut
){
  fs_vfs_t *pFsVfs = (fs_vfs_t *)pVfs;
  fs_real_file *pReal;
  int isJournal = 0;
  int nName = (int)strlen(zPath);

  if( flags!=SQLITE_ACCESS_EXISTS ){
    sqlite3_vfs *pParent = ((fs_vfs_t *)pVfs)->pParent;
    return pParent->xAccess(pParent, zPath, flags, pResOut);
  }

  assert(strlen("-journal")==8);
  if( nName>8 && strcmp("-journal", &zPath[nName-8])==0 ){
    nName -= 8;
    isJournal = 1;
  }

  pReal = pFsVfs->pFileList; 
  for(; pReal && strncmp(pReal->zName, zPath, nName); pReal=pReal->pNext);

  *pResOut = (pReal && (!isJournal || pReal->nJournal>0));
  return SQLITE_OK;
}