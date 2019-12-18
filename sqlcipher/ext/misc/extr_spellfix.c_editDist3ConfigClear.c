#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int nLang; TYPE_1__* a; } ;
struct TYPE_6__ {struct TYPE_6__* pNext; struct TYPE_6__* pCost; } ;
typedef  TYPE_1__ EditDist3Cost ;
typedef  TYPE_2__ EditDist3Config ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_1__*) ; 

__attribute__((used)) static void editDist3ConfigClear(EditDist3Config *p){
  int i;
  if( p==0 ) return;
  for(i=0; i<p->nLang; i++){
    EditDist3Cost *pCost, *pNext;
    pCost = p->a[i].pCost;
    while( pCost ){
      pNext = pCost->pNext;
      sqlite3_free(pCost);
      pCost = pNext;
    }
  }
  sqlite3_free(p->a);
  memset(p, 0, sizeof(*p));
}