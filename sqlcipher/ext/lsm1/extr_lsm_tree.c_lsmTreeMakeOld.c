#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int iTransId; scalar_t__ nByte; scalar_t__ nHeight; scalar_t__ iRoot; } ;
struct TYPE_10__ {int /*<<< orphan*/  cksum1; int /*<<< orphan*/  cksum0; TYPE_1__* aRegion; } ;
struct TYPE_11__ {scalar_t__ iOldShmid; int iOldLog; scalar_t__ iNextShmid; TYPE_6__ root; int /*<<< orphan*/  oldroot; TYPE_3__ log; int /*<<< orphan*/  oldcksum1; int /*<<< orphan*/  oldcksum0; } ;
struct TYPE_12__ {scalar_t__ iReader; TYPE_4__ treehdr; TYPE_2__* pClient; } ;
typedef  TYPE_5__ lsm_db ;
typedef  int i64 ;
typedef  int /*<<< orphan*/  TreeRoot ;
struct TYPE_9__ {int iLogOff; } ;
struct TYPE_8__ {int iEnd; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_6__*,int) ; 

void lsmTreeMakeOld(lsm_db *pDb){

  /* A write transaction must be open. Otherwise the code below that
  ** assumes (pDb->pClient->iLogOff) is current may malfunction. 
  **
  ** Update: currently this assert fails due to lsm_flush(), which does
  ** not set nTransOpen.
  */
  assert( /* pDb->nTransOpen>0 && */ pDb->iReader>=0 );

  if( pDb->treehdr.iOldShmid==0 ){
    pDb->treehdr.iOldLog = (pDb->treehdr.log.aRegion[2].iEnd << 1);
    pDb->treehdr.iOldLog |= (~(pDb->pClient->iLogOff) & (i64)0x0001);

    pDb->treehdr.oldcksum0 = pDb->treehdr.log.cksum0;
    pDb->treehdr.oldcksum1 = pDb->treehdr.log.cksum1;
    pDb->treehdr.iOldShmid = pDb->treehdr.iNextShmid-1;
    memcpy(&pDb->treehdr.oldroot, &pDb->treehdr.root, sizeof(TreeRoot));

    pDb->treehdr.root.iTransId = 1;
    pDb->treehdr.root.iRoot = 0;
    pDb->treehdr.root.nHeight = 0;
    pDb->treehdr.root.nByte = 0;
  }
}