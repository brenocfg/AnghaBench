#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct RowSetEntry {scalar_t__ v; struct RowSetEntry* pRight; } ;
typedef  scalar_t__ i64 ;
struct TYPE_4__ {int rsFlags; struct RowSetEntry* pLast; struct RowSetEntry* pEntry; } ;
typedef  TYPE_1__ RowSet ;

/* Variables and functions */
 int ROWSET_NEXT ; 
 int ROWSET_SORTED ; 
 int /*<<< orphan*/  assert (int) ; 
 struct RowSetEntry* rowSetEntryAlloc (TYPE_1__*) ; 

void sqlite3RowSetInsert(RowSet *p, i64 rowid){
  struct RowSetEntry *pEntry;  /* The new entry */
  struct RowSetEntry *pLast;   /* The last prior entry */

  /* This routine is never called after sqlite3RowSetNext() */
  assert( p!=0 && (p->rsFlags & ROWSET_NEXT)==0 );

  pEntry = rowSetEntryAlloc(p);
  if( pEntry==0 ) return;
  pEntry->v = rowid;
  pEntry->pRight = 0;
  pLast = p->pLast;
  if( pLast ){
    if( rowid<=pLast->v ){  /*OPTIMIZATION-IF-FALSE*/
      /* Avoid unnecessary sorts by preserving the ROWSET_SORTED flags
      ** where possible */
      p->rsFlags &= ~ROWSET_SORTED;
    }
    pLast->pRight = pEntry;
  }else{
    p->pEntry = pEntry;
  }
  p->pLast = pEntry;
}