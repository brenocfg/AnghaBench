#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ iForeGuard; size_t nByte; TYPE_1__* pAgg; struct TYPE_13__* pPrev; struct TYPE_13__* pNext; } ;
typedef  TYPE_2__ u8 ;
struct TYPE_14__ {int /*<<< orphan*/  (* xFree ) (TYPE_2__*) ;TYPE_2__* pFirst; } ;
typedef  TYPE_3__ TmGlobal ;
typedef  TYPE_2__ TmBlockHdr ;
struct TYPE_12__ {size_t nOutByte; int /*<<< orphan*/  nOutAlloc; } ;

/* Variables and functions */
 TYPE_2__* BLOCK_HDR_SIZE ; 
 scalar_t__ FOREGUARD ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ memcmp (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  rearguard ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  tmEnterMutex (TYPE_3__*) ; 
 int /*<<< orphan*/  tmLeaveMutex (TYPE_3__*) ; 

__attribute__((used)) static void tmFree(TmGlobal *pTm, void *p){
  if( p ){
    TmBlockHdr *pHdr;
    u8 *pUser = (u8 *)p;

    tmEnterMutex(pTm);
    pHdr = (TmBlockHdr *)(pUser - BLOCK_HDR_SIZE);
    assert( pHdr->iForeGuard==FOREGUARD );
    assert( 0==memcmp(&pUser[pHdr->nByte], &rearguard, 4) );

    if( pHdr->pPrev ){
      assert( pHdr->pPrev->pNext==pHdr );
      pHdr->pPrev->pNext = pHdr->pNext;
    }else{
      assert( pHdr==pTm->pFirst );
      pTm->pFirst = pHdr->pNext;
    }
    if( pHdr->pNext ){
      assert( pHdr->pNext->pPrev==pHdr );
      pHdr->pNext->pPrev = pHdr->pPrev;
    }

#ifdef TM_BACKTRACE
    pHdr->pAgg->nOutAlloc--;
    pHdr->pAgg->nOutByte -= pHdr->nByte;
#endif

    tmLeaveMutex(pTm);
    memset(pUser, 0x58, pHdr->nByte);
    memset(pHdr, 0x57, sizeof(TmBlockHdr));
    pTm->xFree(pHdr);
  }
}