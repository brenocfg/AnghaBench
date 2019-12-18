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
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vfs ;
struct TYPE_7__ {TYPE_1__* pMethods; } ;
typedef  TYPE_2__ sqlite3_file ;
struct TYPE_8__ {TYPE_4__* pFileList; } ;
typedef  TYPE_3__ fs_vfs_t ;
struct TYPE_9__ {scalar_t__ nJournal; scalar_t__ nBlob; TYPE_2__* pFile; struct TYPE_9__* pNext; int /*<<< orphan*/  zName; } ;
typedef  TYPE_4__ fs_real_file ;
struct TYPE_6__ {int (* xWrite ) (TYPE_2__*,char*,int,scalar_t__) ;} ;

/* Variables and functions */
 scalar_t__ BLOCKSIZE ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char const*,int) ; 
 int stub1 (TYPE_2__*,char*,int,scalar_t__) ; 

__attribute__((used)) static int fsDelete(sqlite3_vfs *pVfs, const char *zPath, int dirSync){
  int rc = SQLITE_OK;
  fs_vfs_t *pFsVfs = (fs_vfs_t *)pVfs;
  fs_real_file *pReal;
  sqlite3_file *pF;
  int nName = (int)strlen(zPath) - 8;

  assert(strlen("-journal")==8);
  assert(strcmp("-journal", &zPath[nName])==0);

  pReal = pFsVfs->pFileList; 
  for(; pReal && strncmp(pReal->zName, zPath, nName); pReal=pReal->pNext);
  if( pReal ){
    pF = pReal->pFile;
    rc = pF->pMethods->xWrite(pF, "\0\0\0\0", 4, pReal->nBlob-BLOCKSIZE);
    if( rc==SQLITE_OK ){
      pReal->nJournal = 0;
    }
  }
  return rc;
}