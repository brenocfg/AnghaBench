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
struct TYPE_8__ {size_t iPg; TYPE_1__* aPg; } ;
struct TYPE_7__ {int iCell; void* iPg; } ;
struct TYPE_6__ {int iCell; int /*<<< orphan*/  pPage; } ;
typedef  TYPE_2__ MergeInput ;
typedef  TYPE_3__ BtreeCursor ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 void* lsmFsPageNumber (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void btreeCursorSplitkey(BtreeCursor *pCsr, MergeInput *p){
  int iCell = pCsr->aPg[pCsr->iPg].iCell;
  if( iCell>=0 ){
    p->iCell = iCell;
    p->iPg = lsmFsPageNumber(pCsr->aPg[pCsr->iPg].pPage);
  }else{
    int i;
    for(i=pCsr->iPg-1; i>=0; i--){
      if( pCsr->aPg[i].iCell>0 ) break;
    }
    assert( i>=0 );
    p->iCell = pCsr->aPg[i].iCell-1;
    p->iPg = lsmFsPageNumber(pCsr->aPg[i].pPage);
  }
}