#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  zVfsName; TYPE_3__* pRootVfs; } ;
typedef  TYPE_1__ vfstrace_info ;
struct TYPE_15__ {char* zFName; TYPE_5__* pReal; TYPE_1__* pInfo; } ;
typedef  TYPE_2__ vfstrace_file ;
struct TYPE_16__ {int (* xOpen ) (TYPE_3__*,char const*,TYPE_5__*,int,int*) ;scalar_t__ pAppData; } ;
typedef  TYPE_3__ sqlite3_vfs ;
struct TYPE_17__ {int iVersion; scalar_t__ xShmUnmap; scalar_t__ xShmBarrier; scalar_t__ xShmLock; scalar_t__ xShmMap; int /*<<< orphan*/  xDeviceCharacteristics; int /*<<< orphan*/  xSectorSize; int /*<<< orphan*/  xFileControl; int /*<<< orphan*/  xCheckReservedLock; int /*<<< orphan*/  xUnlock; int /*<<< orphan*/  xLock; int /*<<< orphan*/  xFileSize; int /*<<< orphan*/  xSync; int /*<<< orphan*/  xTruncate; int /*<<< orphan*/  xWrite; int /*<<< orphan*/  xRead; int /*<<< orphan*/  xClose; } ;
typedef  TYPE_4__ sqlite3_io_methods ;
struct TYPE_18__ {TYPE_4__* pMethods; } ;
typedef  TYPE_5__ sqlite3_file ;

/* Variables and functions */
 char* fileTail (char const*) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 TYPE_4__* sqlite3_malloc (int) ; 
 int stub1 (TYPE_3__*,char const*,TYPE_5__*,int,int*) ; 
 int /*<<< orphan*/  vfstraceCheckReservedLock ; 
 int /*<<< orphan*/  vfstraceClose ; 
 int /*<<< orphan*/  vfstraceDeviceCharacteristics ; 
 int /*<<< orphan*/  vfstraceFileControl ; 
 int /*<<< orphan*/  vfstraceFileSize ; 
 int /*<<< orphan*/  vfstraceLock ; 
 int /*<<< orphan*/  vfstraceRead ; 
 int /*<<< orphan*/  vfstraceSectorSize ; 
 scalar_t__ vfstraceShmBarrier ; 
 scalar_t__ vfstraceShmLock ; 
 scalar_t__ vfstraceShmMap ; 
 scalar_t__ vfstraceShmUnmap ; 
 int /*<<< orphan*/  vfstraceSync ; 
 int /*<<< orphan*/  vfstraceTruncate ; 
 int /*<<< orphan*/  vfstraceUnlock ; 
 int /*<<< orphan*/  vfstraceWrite ; 
 int /*<<< orphan*/  vfstrace_print_errcode (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  vfstrace_printf (TYPE_1__*,char*,...) ; 

__attribute__((used)) static int vfstraceOpen(
  sqlite3_vfs *pVfs,
  const char *zName,
  sqlite3_file *pFile,
  int flags,
  int *pOutFlags
){
  int rc;
  vfstrace_file *p = (vfstrace_file *)pFile;
  vfstrace_info *pInfo = (vfstrace_info*)pVfs->pAppData;
  sqlite3_vfs *pRoot = pInfo->pRootVfs;
  p->pInfo = pInfo;
  p->zFName = zName ? fileTail(zName) : "<temp>";
  p->pReal = (sqlite3_file *)&p[1];
  rc = pRoot->xOpen(pRoot, zName, p->pReal, flags, pOutFlags);
  vfstrace_printf(pInfo, "%s.xOpen(%s,flags=0x%x)",
                  pInfo->zVfsName, p->zFName, flags);
  if( p->pReal->pMethods ){
    sqlite3_io_methods *pNew = sqlite3_malloc( sizeof(*pNew) );
    const sqlite3_io_methods *pSub = p->pReal->pMethods;
    memset(pNew, 0, sizeof(*pNew));
    pNew->iVersion = pSub->iVersion;
    pNew->xClose = vfstraceClose;
    pNew->xRead = vfstraceRead;
    pNew->xWrite = vfstraceWrite;
    pNew->xTruncate = vfstraceTruncate;
    pNew->xSync = vfstraceSync;
    pNew->xFileSize = vfstraceFileSize;
    pNew->xLock = vfstraceLock;
    pNew->xUnlock = vfstraceUnlock;
    pNew->xCheckReservedLock = vfstraceCheckReservedLock;
    pNew->xFileControl = vfstraceFileControl;
    pNew->xSectorSize = vfstraceSectorSize;
    pNew->xDeviceCharacteristics = vfstraceDeviceCharacteristics;
    if( pNew->iVersion>=2 ){
      pNew->xShmMap = pSub->xShmMap ? vfstraceShmMap : 0;
      pNew->xShmLock = pSub->xShmLock ? vfstraceShmLock : 0;
      pNew->xShmBarrier = pSub->xShmBarrier ? vfstraceShmBarrier : 0;
      pNew->xShmUnmap = pSub->xShmUnmap ? vfstraceShmUnmap : 0;
    }
    pFile->pMethods = pNew;
  }
  vfstrace_print_errcode(pInfo, " -> %s", rc);
  if( pOutFlags ){
    vfstrace_printf(pInfo, ", outFlags=0x%x\n", *pOutFlags);
  }else{
    vfstrace_printf(pInfo, "\n");
  }
  return rc;
}