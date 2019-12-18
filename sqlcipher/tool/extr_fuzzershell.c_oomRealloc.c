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
struct TYPE_3__ {void* (* xRealloc ) (void*,int) ;} ;
struct TYPE_4__ {int iOomCntdown; scalar_t__ nOomFault; TYPE_1__ sOrigMem; int /*<<< orphan*/  bOomOnce; scalar_t__ bOomEnable; } ;

/* Variables and functions */
 TYPE_2__ g ; 
 int /*<<< orphan*/  oomFault () ; 
 void* stub1 (void*,int) ; 

__attribute__((used)) static void *oomRealloc(void *pOld, int nByte){
  if( nByte>0 && g.bOomEnable && g.iOomCntdown>0 ){
    g.iOomCntdown--;
    if( g.iOomCntdown==0 ){
      if( g.nOomFault==0 ) oomFault();
      g.nOomFault++;
      if( !g.bOomOnce ) g.iOomCntdown = 1;
      return 0;
    }
  }
  return g.sOrigMem.xRealloc(pOld, nByte);
}