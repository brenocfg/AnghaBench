#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_6__ {int nCol; TYPE_3__* pIndex; int /*<<< orphan*/  tabFlags; TYPE_4__* aCol; } ;
typedef  TYPE_1__ Table ;
struct TYPE_9__ {int colFlags; scalar_t__ notNull; } ;
struct TYPE_8__ {int nKeyCol; scalar_t__ onError; int* aiColumn; int uniqNotNull; struct TYPE_8__* pNext; } ;
struct TYPE_7__ {TYPE_1__* pNewTable; } ;
typedef  TYPE_2__ Parse ;
typedef  TYPE_3__ Index ;
typedef  TYPE_4__ Column ;

/* Variables and functions */
 int COLFLAG_UNIQUE ; 
 scalar_t__ NEVER (int) ; 
 scalar_t__ OE_None ; 
 int /*<<< orphan*/  TF_HasNotNull ; 
 int /*<<< orphan*/  assert (int) ; 

void sqlite3AddNotNull(Parse *pParse, int onError){
  Table *p;
  Column *pCol;
  p = pParse->pNewTable;
  if( p==0 || NEVER(p->nCol<1) ) return;
  pCol = &p->aCol[p->nCol-1];
  pCol->notNull = (u8)onError;
  p->tabFlags |= TF_HasNotNull;

  /* Set the uniqNotNull flag on any UNIQUE or PK indexes already created
  ** on this column.  */
  if( pCol->colFlags & COLFLAG_UNIQUE ){
    Index *pIdx;
    for(pIdx=p->pIndex; pIdx; pIdx=pIdx->pNext){
      assert( pIdx->nKeyCol==1 && pIdx->onError!=OE_None );
      if( pIdx->aiColumn[0]==p->nCol-1 ){
        pIdx->uniqNotNull = 1;
      }
    }
  }
}