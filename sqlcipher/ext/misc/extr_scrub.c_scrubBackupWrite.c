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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int sqlite3_int64 ;
struct TYPE_8__ {TYPE_1__* pMethods; } ;
struct TYPE_7__ {int iLastPage; scalar_t__ rcErr; scalar_t__ szPage; TYPE_3__* pDest; } ;
struct TYPE_6__ {int (* xWrite ) (TYPE_3__*,int /*<<< orphan*/  const*,scalar_t__,int) ;} ;
typedef  TYPE_2__ ScrubState ;

/* Variables and functions */
 scalar_t__ SQLITE_IOERR ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  scrubBackupErr (TYPE_2__*,char*,int) ; 
 int stub1 (TYPE_3__*,int /*<<< orphan*/  const*,scalar_t__,int) ; 

__attribute__((used)) static void scrubBackupWrite(ScrubState *p, int pgno, const u8 *pData){
  int rc;
  sqlite3_int64 iOff;
  if( p->rcErr ) return;
  iOff = (pgno-1)*(sqlite3_int64)p->szPage;
  rc = p->pDest->pMethods->xWrite(p->pDest, pData, p->szPage, iOff);
  if( rc!=SQLITE_OK ){
    scrubBackupErr(p, "write failed for page %d", pgno);
    p->rcErr = SQLITE_IOERR;
  }
  if( (u32)pgno>p->iLastPage ) p->iLastPage = pgno;
}