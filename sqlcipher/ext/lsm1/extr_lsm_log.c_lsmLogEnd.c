#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_2__* aRegion; int /*<<< orphan*/  cksum1; int /*<<< orphan*/  cksum0; } ;
struct TYPE_7__ {TYPE_5__ log; } ;
struct TYPE_9__ {TYPE_1__ treehdr; TYPE_4__* pLogWriter; } ;
typedef  TYPE_3__ lsm_db ;
struct TYPE_10__ {scalar_t__ iOff; scalar_t__ iRegion1End; scalar_t__ iRegion2Start; int /*<<< orphan*/  cksum1; int /*<<< orphan*/  cksum0; } ;
struct TYPE_8__ {scalar_t__ iEnd; scalar_t__ iStart; } ;
typedef  TYPE_4__ LogWriter ;
typedef  TYPE_5__ DbLog ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

void lsmLogEnd(lsm_db *pDb, int bCommit){
  DbLog *pLog;
  LogWriter *p;
  p = pDb->pLogWriter;

  if( p==0 ) return;
  pLog = &pDb->treehdr.log;

  if( bCommit ){
    pLog->aRegion[2].iEnd = p->iOff;
    pLog->cksum0 = p->cksum0;
    pLog->cksum1 = p->cksum1;
    if( p->iRegion1End ){
      /* This happens when the transaction had to jump over some other
      ** part of the log.  */
      assert( pLog->aRegion[1].iEnd==0 );
      assert( pLog->aRegion[2].iStart<p->iRegion1End );
      pLog->aRegion[1].iStart = pLog->aRegion[2].iStart;
      pLog->aRegion[1].iEnd = p->iRegion1End;
      pLog->aRegion[2].iStart = p->iRegion2Start;
    }
  }
}