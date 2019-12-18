#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int szSlot; int nSlot; int nFreeSlot; int nReserve; void* pEnd; TYPE_1__* pFree; scalar_t__ bUnderPressure; void* pStart; scalar_t__ isInit; } ;
struct TYPE_3__ {struct TYPE_3__* pNext; } ;
typedef  TYPE_1__ PgFreeslot ;

/* Variables and functions */
 int ROUNDDOWN8 (int) ; 
 TYPE_2__ pcache1 ; 

void sqlite3PCacheBufferSetup(void *pBuf, int sz, int n){
  if( pcache1.isInit ){
    PgFreeslot *p;
    if( pBuf==0 ) sz = n = 0;
    if( n==0 ) sz = 0;
    sz = ROUNDDOWN8(sz);
    pcache1.szSlot = sz;
    pcache1.nSlot = pcache1.nFreeSlot = n;
    pcache1.nReserve = n>90 ? 10 : (n/10 + 1);
    pcache1.pStart = pBuf;
    pcache1.pFree = 0;
    pcache1.bUnderPressure = 0;
    while( n-- ){
      p = (PgFreeslot*)pBuf;
      p->pNext = pcache1.pFree;
      pcache1.pFree = p;
      pBuf = (void*)&((char*)pBuf)[sz];
    }
    pcache1.pEnd = pBuf;
  }
}