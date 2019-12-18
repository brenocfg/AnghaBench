#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int sqlite3_int64 ;
struct TYPE_9__ {TYPE_1__* pMethods; } ;
struct TYPE_8__ {scalar_t__ rcErr; scalar_t__ szPage; TYPE_3__* pSrc; } ;
struct TYPE_7__ {int (* xRead ) (TYPE_3__*,int /*<<< orphan*/ *,scalar_t__,int) ;} ;
typedef  TYPE_2__ ScrubState ;

/* Variables and functions */
 scalar_t__ SQLITE_IOERR ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/ * scrubBackupAllocPage (TYPE_2__*) ; 
 int /*<<< orphan*/  scrubBackupErr (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  sqlite3_free (int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_3__*,int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static u8 *scrubBackupRead(ScrubState *p, int pgno, u8 *pBuf){
  int rc;
  sqlite3_int64 iOff;
  u8 *pOut = pBuf;
  if( p->rcErr ) return 0;
  if( pOut==0 ){
    pOut = scrubBackupAllocPage(p);
    if( pOut==0 ) return 0;
  }
  iOff = (pgno-1)*(sqlite3_int64)p->szPage;
  rc = p->pSrc->pMethods->xRead(p->pSrc, pOut, p->szPage, iOff);
  if( rc!=SQLITE_OK ){
    if( pBuf==0 ) sqlite3_free(pOut);
    pOut = 0;
    scrubBackupErr(p, "read failed for page %d", pgno);
    p->rcErr = SQLITE_IOERR;
  }
  return pOut;  
}