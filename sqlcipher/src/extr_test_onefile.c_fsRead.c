#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ sqlite_int64 ;
struct TYPE_9__ {TYPE_1__* pMethods; } ;
typedef  TYPE_2__ sqlite3_file ;
struct TYPE_10__ {scalar_t__ nDatabase; scalar_t__ nJournal; int nBlob; TYPE_2__* pFile; } ;
typedef  TYPE_3__ fs_real_file ;
struct TYPE_11__ {scalar_t__ eType; TYPE_3__* pReal; } ;
typedef  TYPE_4__ fs_file ;
struct TYPE_8__ {int (* xRead ) (TYPE_2__*,void*,int,scalar_t__) ;} ;

/* Variables and functions */
 int BLOCKSIZE ; 
 scalar_t__ DATABASE_FILE ; 
 scalar_t__ JOURNAL_FILE ; 
 int MIN (int,int) ; 
 int SQLITE_IOERR_SHORT_READ ; 
 int SQLITE_OK ; 
 int stub1 (TYPE_2__*,void*,int,scalar_t__) ; 
 int stub2 (TYPE_2__*,char*,int,int) ; 

__attribute__((used)) static int fsRead(
  sqlite3_file *pFile, 
  void *zBuf, 
  int iAmt, 
  sqlite_int64 iOfst
){
  int rc = SQLITE_OK;
  fs_file *p = (fs_file *)pFile;
  fs_real_file *pReal = p->pReal;
  sqlite3_file *pF = pReal->pFile;

  if( (p->eType==DATABASE_FILE && (iAmt+iOfst)>pReal->nDatabase)
   || (p->eType==JOURNAL_FILE && (iAmt+iOfst)>pReal->nJournal)
  ){
    rc = SQLITE_IOERR_SHORT_READ;
  }else if( p->eType==DATABASE_FILE ){
    rc = pF->pMethods->xRead(pF, zBuf, iAmt, iOfst+BLOCKSIZE);
  }else{
    /* Journal file. */
    int iRem = iAmt;
    int iBuf = 0;
    int ii = (int)iOfst;
    while( iRem>0 && rc==SQLITE_OK ){
      int iRealOff = pReal->nBlob - BLOCKSIZE*((ii/BLOCKSIZE)+1) + ii%BLOCKSIZE;
      int iRealAmt = MIN(iRem, BLOCKSIZE - (iRealOff%BLOCKSIZE));

      rc = pF->pMethods->xRead(pF, &((char *)zBuf)[iBuf], iRealAmt, iRealOff);
      ii += iRealAmt;
      iBuf += iRealAmt;
      iRem -= iRealAmt;
    }
  }

  return rc;
}