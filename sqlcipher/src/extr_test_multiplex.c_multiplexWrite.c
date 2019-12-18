#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int sqlite3_int64 ;
struct TYPE_11__ {TYPE_1__* pMethods; } ;
typedef  TYPE_2__ sqlite3_file ;
struct TYPE_12__ {int szChunk; int /*<<< orphan*/  bEnabled; } ;
typedef  TYPE_3__ multiplexGroup ;
struct TYPE_13__ {TYPE_3__* pGroup; } ;
typedef  TYPE_4__ multiplexConn ;
struct TYPE_10__ {int (* xWrite ) (TYPE_2__*,void const*,int,int) ;} ;

/* Variables and functions */
 int SQLITE_IOERR_WRITE ; 
 int SQLITE_OK ; 
 TYPE_2__* multiplexSubOpen (TYPE_3__*,int,int*,int /*<<< orphan*/ *,int) ; 
 int stub1 (TYPE_2__*,void const*,int,int) ; 
 int stub2 (TYPE_2__*,void const*,int,int) ; 

__attribute__((used)) static int multiplexWrite(
  sqlite3_file *pConn,
  const void *pBuf,
  int iAmt,
  sqlite3_int64 iOfst
){
  multiplexConn *p = (multiplexConn*)pConn;
  multiplexGroup *pGroup = p->pGroup;
  int rc = SQLITE_OK;
  if( !pGroup->bEnabled ){
    sqlite3_file *pSubOpen = multiplexSubOpen(pGroup, 0, &rc, NULL, 0);
    if( pSubOpen==0 ){
      rc = SQLITE_IOERR_WRITE;
    }else{
      rc = pSubOpen->pMethods->xWrite(pSubOpen, pBuf, iAmt, iOfst);
    }
  }else{
    while( rc==SQLITE_OK && iAmt>0 ){
      int i = (int)(iOfst / pGroup->szChunk);
      sqlite3_file *pSubOpen = multiplexSubOpen(pGroup, i, &rc, NULL, 1);
      if( pSubOpen ){
        int extra = ((int)(iOfst % pGroup->szChunk) + iAmt) -
                    pGroup->szChunk;
        if( extra<0 ) extra = 0;
        iAmt -= extra;
        rc = pSubOpen->pMethods->xWrite(pSubOpen, pBuf, iAmt,
                                        iOfst % pGroup->szChunk);
        pBuf = (char *)pBuf + iAmt;
        iOfst += iAmt;
        iAmt = extra;
      }
    }
  }
  return rc;
}