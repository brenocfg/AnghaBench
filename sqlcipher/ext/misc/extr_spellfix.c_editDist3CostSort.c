#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* pNext; } ;
typedef  TYPE_1__ EditDist3Cost ;

/* Variables and functions */
 TYPE_1__* editDist3CostMerge (TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static EditDist3Cost *editDist3CostSort(EditDist3Cost *pList){
  EditDist3Cost *ap[60], *p;
  int i;
  int mx = 0;
  ap[0] = 0;
  ap[1] = 0;
  while( pList ){
    p = pList;
    pList = p->pNext;
    p->pNext = 0;
    for(i=0; ap[i]; i++){
      p = editDist3CostMerge(ap[i],p);
      ap[i] = 0;
    }
    ap[i] = p;
    if( i>mx ){
      mx = i;
      ap[i+1] = 0;
    }
  }
  p = 0;
  for(i=0; i<=mx; i++){
    if( ap[i] ) p = editDist3CostMerge(p,ap[i]);
  }
  return p;
}