#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* pClosable; TYPE_2__* aSrc; scalar_t__ bSwarm; } ;
typedef  TYPE_1__ UnionTab ;
struct TYPE_5__ {scalar_t__ nUser; struct TYPE_5__* pNextClosable; scalar_t__ db; } ;
typedef  TYPE_2__ UnionSrc ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void unionIncrRefcount(UnionTab *pTab, int iTab){
  if( pTab->bSwarm ){
    UnionSrc *pSrc = &pTab->aSrc[iTab];
    assert( pSrc->nUser>=0 && pSrc->db );
    if( pSrc->nUser==0 ){
      UnionSrc **pp;
      for(pp=&pTab->pClosable; *pp!=pSrc; pp=&(*pp)->pNextClosable);
      *pp = pSrc->pNextClosable;
      pSrc->pNextClosable = 0;
    }
    pSrc->nUser++;
  }
}