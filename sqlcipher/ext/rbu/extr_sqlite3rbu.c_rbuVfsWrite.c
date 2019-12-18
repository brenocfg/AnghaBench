#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ sqlite_int64 ;
struct TYPE_8__ {scalar_t__ eStage; scalar_t__ iOalSz; } ;
typedef  TYPE_2__ sqlite3rbu ;
typedef  int /*<<< orphan*/  sqlite3_file ;
struct TYPE_9__ {int openFlags; scalar_t__ sz; int /*<<< orphan*/  iWriteVer; int /*<<< orphan*/  iCookie; TYPE_4__* pReal; TYPE_2__* pRbu; } ;
typedef  TYPE_3__ rbu_file ;
typedef  scalar_t__ i64 ;
struct TYPE_10__ {TYPE_1__* pMethods; } ;
struct TYPE_7__ {int (* xWrite ) (TYPE_4__*,void const*,int,scalar_t__) ;} ;

/* Variables and functions */
 scalar_t__ RBU_STAGE_CAPTURE ; 
 scalar_t__ RBU_STAGE_OAL ; 
 int SQLITE_OK ; 
 int SQLITE_OPEN_DELETEONCLOSE ; 
 int SQLITE_OPEN_MAIN_DB ; 
 int SQLITE_OPEN_WAL ; 
 int /*<<< orphan*/  assert (int) ; 
 int rbuCaptureDbWrite (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  rbuGetU32 (int /*<<< orphan*/ *) ; 
 int rbuUpdateTempSize (TYPE_3__*,scalar_t__) ; 
 int stub1 (TYPE_4__*,void const*,int,scalar_t__) ; 

__attribute__((used)) static int rbuVfsWrite(
  sqlite3_file *pFile, 
  const void *zBuf, 
  int iAmt, 
  sqlite_int64 iOfst
){
  rbu_file *p = (rbu_file*)pFile;
  sqlite3rbu *pRbu = p->pRbu;
  int rc;

  if( pRbu && pRbu->eStage==RBU_STAGE_CAPTURE ){
    assert( p->openFlags & SQLITE_OPEN_MAIN_DB );
    rc = rbuCaptureDbWrite(p->pRbu, iOfst);
  }else{
    if( pRbu ){
      if( pRbu->eStage==RBU_STAGE_OAL 
       && (p->openFlags & SQLITE_OPEN_WAL) 
       && iOfst>=pRbu->iOalSz
      ){
        pRbu->iOalSz = iAmt + iOfst;
      }else if( p->openFlags & SQLITE_OPEN_DELETEONCLOSE ){
        i64 szNew = iAmt+iOfst;
        if( szNew>p->sz ){
          rc = rbuUpdateTempSize(p, szNew);
          if( rc!=SQLITE_OK ) return rc;
        }
      }
    }
    rc = p->pReal->pMethods->xWrite(p->pReal, zBuf, iAmt, iOfst);
    if( rc==SQLITE_OK && iOfst==0 && (p->openFlags & SQLITE_OPEN_MAIN_DB) ){
      /* These look like magic numbers. But they are stable, as they are part
      ** of the definition of the SQLite file format, which may not change. */
      u8 *pBuf = (u8*)zBuf;
      p->iCookie = rbuGetU32(&pBuf[24]);
      p->iWriteVer = pBuf[19];
    }
  }
  return rc;
}