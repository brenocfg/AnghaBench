#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* pLruLast; TYPE_1__* pLruFirst; } ;
struct TYPE_5__ {scalar_t__ pLruNext; struct TYPE_5__* pLruPrev; } ;
typedef  TYPE_1__ Page ;
typedef  TYPE_2__ FileSystem ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void fsPageAddToLru(FileSystem *pFS, Page *pPg){
  assert( pPg->pLruNext==0 && pPg->pLruPrev==0 );
  pPg->pLruPrev = pFS->pLruLast;
  if( pPg->pLruPrev ){
    pPg->pLruPrev->pLruNext = pPg;
  }else{
    pFS->pLruFirst = pPg;
  }
  pFS->pLruLast = pPg;
}