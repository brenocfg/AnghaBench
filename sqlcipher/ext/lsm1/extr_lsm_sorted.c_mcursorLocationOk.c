#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int nRight; scalar_t__ iSplitTopic; void* pSplitKey; int nSplitKey; int /*<<< orphan*/  lhs; } ;
struct TYPE_10__ {int /*<<< orphan*/  nData; int /*<<< orphan*/  pData; } ;
struct TYPE_12__ {int eType; int flags; int nPtr; int* aTree; TYPE_2__ key; TYPE_1__* pDb; TYPE_3__* aPtr; } ;
struct TYPE_11__ {scalar_t__ pPg; int eType; int /*<<< orphan*/  nKey; int /*<<< orphan*/  pKey; int /*<<< orphan*/ * pSeg; TYPE_5__* pLevel; } ;
struct TYPE_9__ {int /*<<< orphan*/  xCmp; } ;
typedef  TYPE_3__ SegmentPtr ;
typedef  TYPE_4__ MultiCursor ;
typedef  TYPE_5__ Level ;

/* Variables and functions */
 int CURSOR_IGNORE_DELETE ; 
 int CURSOR_IGNORE_SYSTEM ; 
 int CURSOR_NEXT_OK ; 
 int CURSOR_PREV_OK ; 
 int LSM_END_DELETE ; 
 int LSM_INSERT ; 
 int LSM_START_DELETE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assertCursorTree (TYPE_4__*) ; 
 int /*<<< orphan*/  multiCursorGetKey (TYPE_4__*,int,int*,void**,int*) ; 
 scalar_t__ rtTopic (int) ; 
 scalar_t__ sortedKeyCompare (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,void*,int) ; 

__attribute__((used)) static int mcursorLocationOk(MultiCursor *pCsr, int bDeleteOk){
  int eType = pCsr->eType;
  int iKey;
  int i;
  int rdmask;
  
  assert( pCsr->flags & (CURSOR_NEXT_OK|CURSOR_PREV_OK) );
  assertCursorTree(pCsr);

  rdmask = (pCsr->flags & CURSOR_NEXT_OK) ? LSM_END_DELETE : LSM_START_DELETE;

  /* If the cursor does not currently point to an actual database key (i.e.
  ** it points to a delete key, or the start or end of a range-delete), and
  ** the CURSOR_IGNORE_DELETE flag is set, skip past this entry.  */
  if( (pCsr->flags & CURSOR_IGNORE_DELETE) && bDeleteOk==0 ){
    if( (eType & LSM_INSERT)==0 ) return 0;
  }

  /* If the cursor points to a system key (free-list entry), and the
  ** CURSOR_IGNORE_SYSTEM flag is set, skip thie entry.  */
  if( (pCsr->flags & CURSOR_IGNORE_SYSTEM) && rtTopic(eType)!=0 ){
    return 0;
  }

#ifndef NDEBUG
  /* This block fires assert() statements to check one of the assumptions
  ** in the comment below - that if the lhs sub-cursor of a level undergoing
  ** a merge is valid, then all the rhs sub-cursors must be at EOF. 
  **
  ** Also assert that all rhs sub-cursors are either at EOF or point to
  ** a key that is not less than the level split-key.  */
  for(i=0; i<pCsr->nPtr; i++){
    SegmentPtr *pPtr = &pCsr->aPtr[i];
    Level *pLvl = pPtr->pLevel;
    if( pLvl->nRight && pPtr->pPg ){
      if( pPtr->pSeg==&pLvl->lhs ){
        int j;
        for(j=0; j<pLvl->nRight; j++) assert( pPtr[j+1].pPg==0 );
      }else{
        int res = sortedKeyCompare(pCsr->pDb->xCmp, 
            rtTopic(pPtr->eType), pPtr->pKey, pPtr->nKey,
            pLvl->iSplitTopic, pLvl->pSplitKey, pLvl->nSplitKey
        );
        assert( res>=0 );
      }
    }
  }
#endif

  /* Now check if this key has already been deleted by a range-delete. If 
  ** so, skip past it.
  **
  ** Assume, for the moment, that the tree contains no levels currently 
  ** undergoing incremental merge, and that this cursor is iterating forwards
  ** through the database keys. The cursor currently points to a key in
  ** level L. This key has already been deleted if any of the sub-cursors
  ** that point to levels newer than L (or to the in-memory tree) point to
  ** a key greater than the current key with the LSM_END_DELETE flag set.
  **
  ** Or, if the cursor is iterating backwards through data keys, if any
  ** such sub-cursor points to a key smaller than the current key with the
  ** LSM_START_DELETE flag set.
  **
  ** Why it works with levels undergoing a merge too:
  **
  ** When a cursor iterates forwards, the sub-cursors for the rhs of a 
  ** level are only activated once the lhs reaches EOF. So when iterating
  ** forwards, the keys visited are the same as if the level was completely
  ** merged.
  **
  ** If the cursor is iterating backwards, then the lhs sub-cursor is not 
  ** initialized until the last of the rhs sub-cursors has reached EOF.
  ** Additionally, if the START_DELETE flag is set on the last entry (in
  ** reverse order - so the entry with the smallest key) of a rhs sub-cursor,
  ** then a pseudo-key equal to the levels split-key with the END_DELETE
  ** flag set is visited by the sub-cursor.
  */ 
  iKey = pCsr->aTree[1];
  for(i=0; i<iKey; i++){
    int csrflags;
    multiCursorGetKey(pCsr, i, &csrflags, 0, 0);
    if( (rdmask & csrflags) ){
      const int SD_ED = (LSM_START_DELETE|LSM_END_DELETE);
      if( (csrflags & SD_ED)==SD_ED 
       || (pCsr->flags & CURSOR_IGNORE_DELETE)==0
      ){
        void *pKey; int nKey;
        multiCursorGetKey(pCsr, i, 0, &pKey, &nKey);
        if( 0==sortedKeyCompare(pCsr->pDb->xCmp,
              rtTopic(eType), pCsr->key.pData, pCsr->key.nData,
              rtTopic(csrflags), pKey, nKey
        )){
          continue;
        }
      }
      return 0;
    }
  }

  /* The current cursor position is one this cursor should visit. Return 1. */
  return 1;
}