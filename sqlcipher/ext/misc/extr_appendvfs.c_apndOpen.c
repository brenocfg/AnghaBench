#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
struct TYPE_26__ {int (* xOpen ) (TYPE_3__*,char const*,TYPE_4__*,int,int*) ;int /*<<< orphan*/  szOsFile; } ;
typedef  TYPE_3__ sqlite3_vfs ;
typedef  int sqlite3_int64 ;
struct TYPE_27__ {TYPE_2__* pMethods; } ;
typedef  TYPE_4__ sqlite3_file ;
struct TYPE_24__ {int /*<<< orphan*/ * pMethods; } ;
struct TYPE_28__ {int iPgOne; scalar_t__ iMark; TYPE_1__ base; } ;
struct TYPE_25__ {int (* xFileSize ) (TYPE_4__*,int*) ;int /*<<< orphan*/  (* xClose ) (TYPE_4__*) ;} ;
typedef  TYPE_5__ ApndFile ;

/* Variables and functions */
 TYPE_4__* ORIGFILE (TYPE_4__*) ; 
 TYPE_3__* ORIGVFS (TYPE_3__*) ; 
 int SQLITE_CANTOPEN ; 
 int SQLITE_OK ; 
 int SQLITE_OPEN_CREATE ; 
 int SQLITE_OPEN_MAIN_DB ; 
 scalar_t__ apndIsOrdinaryDatabaseFile (int,TYPE_4__*) ; 
 int apndReadMark (int,TYPE_4__*) ; 
 int /*<<< orphan*/  apnd_io_methods ; 
 int /*<<< orphan*/  memmove (TYPE_4__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int stub1 (TYPE_3__*,char const*,TYPE_4__*,int,int*) ; 
 int stub2 (TYPE_3__*,char const*,TYPE_4__*,int,int*) ; 
 int stub3 (TYPE_4__*,int*) ; 
 int /*<<< orphan*/  stub4 (TYPE_4__*) ; 
 int /*<<< orphan*/  stub5 (TYPE_4__*) ; 

__attribute__((used)) static int apndOpen(
  sqlite3_vfs *pVfs,
  const char *zName,
  sqlite3_file *pFile,
  int flags,
  int *pOutFlags
){
  ApndFile *p;
  sqlite3_file *pSubFile;
  sqlite3_vfs *pSubVfs;
  int rc;
  sqlite3_int64 sz;
  pSubVfs = ORIGVFS(pVfs);
  if( (flags & SQLITE_OPEN_MAIN_DB)==0 ){
    return pSubVfs->xOpen(pSubVfs, zName, pFile, flags, pOutFlags);
  }
  p = (ApndFile*)pFile;
  memset(p, 0, sizeof(*p));
  pSubFile = ORIGFILE(pFile);
  p->base.pMethods = &apnd_io_methods;
  rc = pSubVfs->xOpen(pSubVfs, zName, pSubFile, flags, pOutFlags);
  if( rc ) goto apnd_open_done;
  rc = pSubFile->pMethods->xFileSize(pSubFile, &sz);
  if( rc ){
    pSubFile->pMethods->xClose(pSubFile);
    goto apnd_open_done;
  }
  if( apndIsOrdinaryDatabaseFile(sz, pSubFile) ){
    memmove(pFile, pSubFile, pSubVfs->szOsFile);
    return SQLITE_OK;
  }
  p->iMark = 0;
  p->iPgOne = apndReadMark(sz, pFile);
  if( p->iPgOne>0 ){
    return SQLITE_OK;
  }
  if( (flags & SQLITE_OPEN_CREATE)==0 ){
    pSubFile->pMethods->xClose(pSubFile);
    rc = SQLITE_CANTOPEN;
  }
  p->iPgOne = (sz+0xfff) & ~(sqlite3_int64)0xfff;
apnd_open_done:
  if( rc ) pFile->pMethods = 0;
  return rc;
}