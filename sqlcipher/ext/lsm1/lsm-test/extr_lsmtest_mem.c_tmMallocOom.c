#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int nCountdown; int bPersist; void (* xHook ) (void*) ;int bEnable; void* pHookCtx; } ;
typedef  TYPE_1__ TmGlobal ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void tmMallocOom(
  TmGlobal *pTm, 
  int nCountdown, 
  int bPersist,
  void (*xHook)(void *),
  void *pHookCtx
){
  assert( nCountdown>=0 );
  assert( bPersist==0 || bPersist==1 );
  pTm->nCountdown = nCountdown;
  pTm->bPersist = bPersist;
  pTm->xHook = xHook;
  pTm->pHookCtx = pHookCtx;
  pTm->bEnable = 1;
}