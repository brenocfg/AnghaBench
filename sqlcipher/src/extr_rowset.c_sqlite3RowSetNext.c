#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  i64 ;
struct TYPE_7__ {struct TYPE_7__* pRight; int /*<<< orphan*/  v; } ;
struct TYPE_6__ {scalar_t__ pForest; int rsFlags; TYPE_4__* pEntry; } ;
typedef  TYPE_1__ RowSet ;

/* Variables and functions */
 int ROWSET_NEXT ; 
 int ROWSET_SORTED ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_4__* rowSetEntrySort (TYPE_4__*) ; 
 int /*<<< orphan*/  sqlite3RowSetClear (TYPE_1__*) ; 

int sqlite3RowSetNext(RowSet *p, i64 *pRowid){
  assert( p!=0 );
  assert( p->pForest==0 );  /* Cannot be used with sqlite3RowSetText() */

  /* Merge the forest into a single sorted list on first call */
  if( (p->rsFlags & ROWSET_NEXT)==0 ){  /*OPTIMIZATION-IF-FALSE*/
    if( (p->rsFlags & ROWSET_SORTED)==0 ){  /*OPTIMIZATION-IF-FALSE*/
      p->pEntry = rowSetEntrySort(p->pEntry);
    }
    p->rsFlags |= ROWSET_SORTED|ROWSET_NEXT;
  }

  /* Return the next entry on the list */
  if( p->pEntry ){
    *pRowid = p->pEntry->v;
    p->pEntry = p->pEntry->pRight;
    if( p->pEntry==0 ){ /*OPTIMIZATION-IF-TRUE*/
      /* Free memory immediately, rather than waiting on sqlite3_finalize() */
      sqlite3RowSetClear(p);
    }
    return 1;
  }else{
    return 0;
  }
}