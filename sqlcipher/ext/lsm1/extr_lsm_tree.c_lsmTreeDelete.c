#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_7__ ;
typedef  struct TYPE_35__   TYPE_6__ ;
typedef  struct TYPE_34__   TYPE_5__ ;
typedef  struct TYPE_33__   TYPE_4__ ;
typedef  struct TYPE_32__   TYPE_3__ ;
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_33__ {int nHeight; } ;
struct TYPE_30__ {TYPE_4__ root; } ;
struct TYPE_32__ {TYPE_1__ treehdr; } ;
typedef  TYPE_3__ lsm_db ;
typedef  TYPE_4__ TreeRoot ;
struct TYPE_34__ {int nKey; } ;
typedef  TYPE_5__ TreeKey ;
struct TYPE_36__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_35__ {int iNode; size_t* aiCell; TYPE_7__ blob; TYPE_2__** apTreeNode; } ;
typedef  TYPE_6__ TreeCursor ;
typedef  TYPE_7__ TreeBlob ;
struct TYPE_31__ {int* aiKeyPtr; } ;

/* Variables and functions */
 int /*<<< orphan*/  LSM_END_DELETE ; 
 int LSM_OK ; 
 int /*<<< orphan*/  LSM_START_DELETE ; 
 void* TKV_KEY (TYPE_5__*) ; 
 int /*<<< orphan*/  TKV_LOADKEY ; 
 int /*<<< orphan*/  assert (int) ; 
 int assert_delete_ranges_match (TYPE_3__*) ; 
 int /*<<< orphan*/  dump_tree_contents (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  lsmTreeCursorKey (TYPE_6__*,int /*<<< orphan*/ ,void**,int*) ; 
 int lsmTreeCursorNext (TYPE_6__*) ; 
 int /*<<< orphan*/  lsmTreeCursorPrev (TYPE_6__*) ; 
 int lsmTreeCursorSeek (TYPE_6__*,void*,int,int*) ; 
 scalar_t__ lsmTreeCursorValid (TYPE_6__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  tblobFree (TYPE_3__*,TYPE_7__*) ; 
 int treeCountEntries (TYPE_3__*) ; 
 int /*<<< orphan*/  treeCursorInit (TYPE_3__*,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int treeDeleteEntry (TYPE_3__*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int treeInsertEntry (TYPE_3__*,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ treeKeycmp (void*,int,void*,int) ; 
 int /*<<< orphan*/  treeOverwriteKey (TYPE_3__*,TYPE_6__*,int,int*) ; 
 TYPE_5__* treeShmkey (TYPE_3__*,int,int /*<<< orphan*/ ,TYPE_7__*,int*) ; 

int lsmTreeDelete(
  lsm_db *db,
  void *pKey1, int nKey1,         /* Start of range */
  void *pKey2, int nKey2          /* End of range */
){
  int rc = LSM_OK;
  int bDone = 0;
  TreeRoot *p = &db->treehdr.root;
  TreeBlob blob = {0, 0};

  /* The range must be sensible - that (key1 < key2). */
  assert( treeKeycmp(pKey1, nKey1, pKey2, nKey2)<0 );
  assert( assert_delete_ranges_match(db) );

#if 0
  static int nCall = 0;
  printf("\n");
  nCall++;
  printf("%d delete %s .. %s\n", nCall, (char *)pKey1, (char *)pKey2);
  dump_tree_contents(db, "before delete");
#endif

  /* Step 1. This loop runs until the tree contains no keys within the
  ** range being deleted. Or until an error occurs. */
  while( bDone==0 && rc==LSM_OK ){
    int res;
    TreeCursor csr;               /* Cursor to seek to first key in range */
    void *pDel; int nDel;         /* Key to (possibly) delete this iteration */
#ifndef NDEBUG
    int nEntry = treeCountEntries(db);
#endif

    /* Seek the cursor to the first entry in the tree greater than pKey1. */
    treeCursorInit(db, 0, &csr);
    lsmTreeCursorSeek(&csr, pKey1, nKey1, &res);
    if( res<=0 && lsmTreeCursorValid(&csr) ) lsmTreeCursorNext(&csr);

    /* If there is no such entry, or if it is greater than pKey2, then the
    ** tree now contains no keys in the range being deleted. In this case
    ** break out of the loop.  */
    bDone = 1;
    if( lsmTreeCursorValid(&csr) ){
      lsmTreeCursorKey(&csr, 0, &pDel, &nDel);
      if( treeKeycmp(pDel, nDel, pKey2, nKey2)<0 ) bDone = 0;
    }

    if( bDone==0 ){
      if( (u32)csr.iNode==(p->nHeight-1) ){
        /* The element to delete already lies on a leaf node */
        rc = treeDeleteEntry(db, &csr, 0);
      }else{
        /* 1. Overwrite the current key with a copy of the next key in the 
        **    tree (key N).
        **
        ** 2. Seek to key N (cursor will stop at the internal node copy of
        **    N). Move to the next key (original copy of N). Delete
        **    this entry. 
        */
        u32 iKey;
        TreeKey *pKey;
        int iNode = csr.iNode;
        lsmTreeCursorNext(&csr);
        assert( (u32)csr.iNode==(p->nHeight-1) );

        iKey = csr.apTreeNode[csr.iNode]->aiKeyPtr[csr.aiCell[csr.iNode]];
        lsmTreeCursorPrev(&csr);

        treeOverwriteKey(db, &csr, iKey, &rc);
        pKey = treeShmkey(db, iKey, TKV_LOADKEY, &blob, &rc);
        if( pKey ){
          rc = lsmTreeCursorSeek(&csr, TKV_KEY(pKey), pKey->nKey, &res);
        }
        if( rc==LSM_OK ){
          assert( res==0 && csr.iNode==iNode );
          rc = lsmTreeCursorNext(&csr);
          if( rc==LSM_OK ){
            rc = treeDeleteEntry(db, &csr, 0);
          }
        }
      }
    }

    /* Clean up any memory allocated by the cursor. */
    tblobFree(db, &csr.blob);
#if 0
    dump_tree_contents(db, "ddd delete");
#endif
    assert( bDone || treeCountEntries(db)==(nEntry-1) );
  }

#if 0
  dump_tree_contents(db, "during delete");
#endif

  /* Now insert the START_DELETE and END_DELETE keys. */
  if( rc==LSM_OK ){
    rc = treeInsertEntry(db, LSM_START_DELETE, pKey1, nKey1, 0, -1);
  }
#if 0
  dump_tree_contents(db, "during delete 2");
#endif
  if( rc==LSM_OK ){
    rc = treeInsertEntry(db, LSM_END_DELETE, pKey2, nKey2, 0, -1);
  }

#if 0
  dump_tree_contents(db, "after delete");
#endif

  tblobFree(db, &blob);
  assert( assert_delete_ranges_match(db) );
  return rc;
}