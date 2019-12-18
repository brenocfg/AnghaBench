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
struct RowSetEntry {scalar_t__ v; struct RowSetEntry* pLeft; struct RowSetEntry* pRight; } ;
typedef  scalar_t__ sqlite3_int64 ;
struct TYPE_4__ {int rsFlags; int iBatch; struct RowSetEntry* pForest; scalar_t__ pLast; struct RowSetEntry* pEntry; } ;
typedef  TYPE_1__ RowSet ;

/* Variables and functions */
 int ROWSET_NEXT ; 
 int ROWSET_SORTED ; 
 int /*<<< orphan*/  assert (int) ; 
 struct RowSetEntry* rowSetEntryAlloc (TYPE_1__*) ; 
 struct RowSetEntry* rowSetEntryMerge (struct RowSetEntry*,struct RowSetEntry*) ; 
 struct RowSetEntry* rowSetEntrySort (struct RowSetEntry*) ; 
 void* rowSetListToTree (struct RowSetEntry*) ; 
 int /*<<< orphan*/  rowSetTreeToList (struct RowSetEntry*,struct RowSetEntry**,struct RowSetEntry**) ; 

int sqlite3RowSetTest(RowSet *pRowSet, int iBatch, sqlite3_int64 iRowid){
  struct RowSetEntry *p, *pTree;

  /* This routine is never called after sqlite3RowSetNext() */
  assert( pRowSet!=0 && (pRowSet->rsFlags & ROWSET_NEXT)==0 );

  /* Sort entries into the forest on the first test of a new batch.
  ** To save unnecessary work, only do this when the batch number changes.
  */
  if( iBatch!=pRowSet->iBatch ){  /*OPTIMIZATION-IF-FALSE*/
    p = pRowSet->pEntry;
    if( p ){
      struct RowSetEntry **ppPrevTree = &pRowSet->pForest;
      if( (pRowSet->rsFlags & ROWSET_SORTED)==0 ){ /*OPTIMIZATION-IF-FALSE*/
        /* Only sort the current set of entiries if they need it */
        p = rowSetEntrySort(p);
      }
      for(pTree = pRowSet->pForest; pTree; pTree=pTree->pRight){
        ppPrevTree = &pTree->pRight;
        if( pTree->pLeft==0 ){
          pTree->pLeft = rowSetListToTree(p);
          break;
        }else{
          struct RowSetEntry *pAux, *pTail;
          rowSetTreeToList(pTree->pLeft, &pAux, &pTail);
          pTree->pLeft = 0;
          p = rowSetEntryMerge(pAux, p);
        }
      }
      if( pTree==0 ){
        *ppPrevTree = pTree = rowSetEntryAlloc(pRowSet);
        if( pTree ){
          pTree->v = 0;
          pTree->pRight = 0;
          pTree->pLeft = rowSetListToTree(p);
        }
      }
      pRowSet->pEntry = 0;
      pRowSet->pLast = 0;
      pRowSet->rsFlags |= ROWSET_SORTED;
    }
    pRowSet->iBatch = iBatch;
  }

  /* Test to see if the iRowid value appears anywhere in the forest.
  ** Return 1 if it does and 0 if not.
  */
  for(pTree = pRowSet->pForest; pTree; pTree=pTree->pRight){
    p = pTree->pLeft;
    while( p ){
      if( p->v<iRowid ){
        p = p->pRight;
      }else if( p->v>iRowid ){
        p = p->pLeft;
      }else{
        return 1;
      }
    }
  }
  return 0;
}