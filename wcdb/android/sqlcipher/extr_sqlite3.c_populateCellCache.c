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
struct TYPE_6__ {scalar_t__ (* xCellSize ) (TYPE_2__*,scalar_t__) ;} ;
struct TYPE_5__ {int nCell; scalar_t__* apCell; scalar_t__* szCell; TYPE_2__* pRef; } ;
typedef  TYPE_1__ CellArray ;

/* Variables and functions */
 scalar_t__ CORRUPT_DB ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ stub1 (TYPE_2__*,scalar_t__) ; 
 scalar_t__ stub2 (TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static void populateCellCache(CellArray *p, int idx, int N){
  assert( idx>=0 && idx+N<=p->nCell );
  while( N>0 ){
    assert( p->apCell[idx]!=0 );
    if( p->szCell[idx]==0 ){
      p->szCell[idx] = p->pRef->xCellSize(p->pRef, p->apCell[idx]);
    }else{
      assert( CORRUPT_DB ||
              p->szCell[idx]==p->pRef->xCellSize(p->pRef, p->apCell[idx]) );
    }
    idx++;
    N--;
  }
}