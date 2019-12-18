#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int /*<<< orphan*/ * pMethods; } ;
struct TYPE_24__ {char const* zName; int nBlob; unsigned char nDatabase; int nJournal; TYPE_6__* pFile; int /*<<< orphan*/  nRef; struct TYPE_24__** ppThis; struct TYPE_24__* pNext; TYPE_1__ base; } ;
typedef  TYPE_4__ tmp_file ;
struct TYPE_25__ {int szOsFile; int (* xOpen ) (TYPE_5__*,char const*,TYPE_6__*,int,int*) ;} ;
typedef  TYPE_5__ sqlite3_vfs ;
typedef  scalar_t__ sqlite3_int64 ;
struct TYPE_26__ {TYPE_3__* pMethods; } ;
typedef  TYPE_6__ sqlite3_file ;
struct TYPE_27__ {TYPE_4__* pFileList; TYPE_5__* pParent; } ;
typedef  TYPE_7__ fs_vfs_t ;
typedef  TYPE_4__ fs_real_file ;
struct TYPE_22__ {int /*<<< orphan*/ * pMethods; } ;
struct TYPE_28__ {int eType; TYPE_4__* pReal; TYPE_2__ base; } ;
typedef  TYPE_9__ fs_file ;
struct TYPE_23__ {int (* xFileSize ) (TYPE_6__*,scalar_t__*) ;int (* xWrite ) (TYPE_6__*,char*,int,int) ;int (* xRead ) (TYPE_6__*,unsigned char*,int,int) ;int /*<<< orphan*/  (* xClose ) (TYPE_6__*) ;} ;

/* Variables and functions */
 int BLOBSIZE ; 
 int DATABASE_FILE ; 
 int JOURNAL_FILE ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int SQLITE_OPEN_MAIN_DB ; 
 int SQLITE_OPEN_MAIN_JOURNAL ; 
 int SQLITE_OPEN_TEMP_DB ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fs_io_methods ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_4__*) ; 
 scalar_t__ sqlite3_malloc (int) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,int) ; 
 int stub1 (TYPE_5__*,char const*,TYPE_6__*,int,int*) ; 
 int stub2 (TYPE_6__*,scalar_t__*) ; 
 int stub3 (TYPE_6__*,char*,int,int) ; 
 int stub4 (TYPE_6__*,unsigned char*,int,int) ; 
 int stub5 (TYPE_6__*,unsigned char*,int,int) ; 
 int /*<<< orphan*/  stub6 (TYPE_6__*) ; 
 int /*<<< orphan*/  tmp_io_methods ; 

__attribute__((used)) static int fsOpen(
  sqlite3_vfs *pVfs,
  const char *zName,
  sqlite3_file *pFile,
  int flags,
  int *pOutFlags
){
  fs_vfs_t *pFsVfs = (fs_vfs_t *)pVfs;
  fs_file *p = (fs_file *)pFile;
  fs_real_file *pReal = 0;
  int eType;
  int nName;
  int rc = SQLITE_OK;

  if( 0==(flags&(SQLITE_OPEN_MAIN_DB|SQLITE_OPEN_MAIN_JOURNAL)) ){
    tmp_file *p2 = (tmp_file *)pFile;
    memset(p2, 0, sizeof(*p2));
    p2->base.pMethods = &tmp_io_methods;
    return SQLITE_OK;
  }

  eType = ((flags&(SQLITE_OPEN_MAIN_DB))?DATABASE_FILE:JOURNAL_FILE);
  p->base.pMethods = &fs_io_methods;
  p->eType = eType;

  assert(strlen("-journal")==8);
  nName = (int)strlen(zName)-((eType==JOURNAL_FILE)?8:0);
  pReal=pFsVfs->pFileList; 
  for(; pReal && strncmp(pReal->zName, zName, nName); pReal=pReal->pNext);

  if( !pReal ){
    int real_flags = (flags&~(SQLITE_OPEN_MAIN_DB))|SQLITE_OPEN_TEMP_DB;
    sqlite3_int64 size;
    sqlite3_file *pRealFile;
    sqlite3_vfs *pParent = pFsVfs->pParent;
    assert(eType==DATABASE_FILE);

    pReal = (fs_real_file *)sqlite3_malloc(sizeof(*pReal)+pParent->szOsFile);
    if( !pReal ){
      rc = SQLITE_NOMEM;
      goto open_out;
    }
    memset(pReal, 0, sizeof(*pReal)+pParent->szOsFile);
    pReal->zName = zName;
    pReal->pFile = (sqlite3_file *)(&pReal[1]);

    rc = pParent->xOpen(pParent, zName, pReal->pFile, real_flags, pOutFlags);
    if( rc!=SQLITE_OK ){
      goto open_out;
    }
    pRealFile = pReal->pFile;

    rc = pRealFile->pMethods->xFileSize(pRealFile, &size);
    if( rc!=SQLITE_OK ){
      goto open_out;
    }
    if( size==0 ){
      rc = pRealFile->pMethods->xWrite(pRealFile, "\0", 1, BLOBSIZE-1);
      pReal->nBlob = BLOBSIZE;
    }else{
      unsigned char zS[4];
      pReal->nBlob = (int)size;
      rc = pRealFile->pMethods->xRead(pRealFile, zS, 4, 0);
      pReal->nDatabase = (zS[0]<<24)+(zS[1]<<16)+(zS[2]<<8)+zS[3];
      if( rc==SQLITE_OK ){
        rc = pRealFile->pMethods->xRead(pRealFile, zS, 4, pReal->nBlob-4);
        if( zS[0] || zS[1] || zS[2] || zS[3] ){
          pReal->nJournal = pReal->nBlob;
        }
      }
    }

    if( rc==SQLITE_OK ){
      pReal->pNext = pFsVfs->pFileList;
      if( pReal->pNext ){
        pReal->pNext->ppThis = &pReal->pNext;
      }
      pReal->ppThis = &pFsVfs->pFileList;
      pFsVfs->pFileList = pReal;
    }
  }

open_out:
  if( pReal ){
    if( rc==SQLITE_OK ){
      p->pReal = pReal;
      pReal->nRef++;
    }else{
      if( pReal->pFile->pMethods ){
        pReal->pFile->pMethods->xClose(pReal->pFile);
      }
      sqlite3_free(pReal);
    }
  }
  return rc;
}