#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ n; scalar_t__ nAlloc; int* a; } ;
struct TYPE_9__ {scalar_t__ bNoLeafData; int /*<<< orphan*/  nLeafData; int /*<<< orphan*/  iEnd; TYPE_2__* aNodeWriter; int /*<<< orphan*/  iStart; int /*<<< orphan*/  iIdx; scalar_t__ iAbsLevel; } ;
struct TYPE_7__ {scalar_t__ nAlloc; int* a; } ;
struct TYPE_8__ {TYPE_1__ key; TYPE_4__ block; int /*<<< orphan*/  iBlock; } ;
typedef  TYPE_2__ NodeWriter ;
typedef  TYPE_3__ IncrmergeWriter ;
typedef  int /*<<< orphan*/  Fts3Table ;
typedef  TYPE_4__ Blob ;

/* Variables and functions */
 scalar_t__ FTS3_VARINT_MAX ; 
 int FTS_MAX_APPENDABLE_HEIGHT ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  blobGrowBuffer (TYPE_4__*,scalar_t__,int*) ; 
 int fts3WriteSegdir (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,scalar_t__) ; 
 int fts3WriteSegment (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,scalar_t__) ; 
 scalar_t__ sqlite3Fts3PutVarint (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (int*) ; 

__attribute__((used)) static void fts3IncrmergeRelease(
  Fts3Table *p,                   /* FTS3 table handle */
  IncrmergeWriter *pWriter,       /* Merge-writer object */
  int *pRc                        /* IN/OUT: Error code */
){
  int i;                          /* Used to iterate through non-root layers */
  int iRoot;                      /* Index of root in pWriter->aNodeWriter */
  NodeWriter *pRoot;              /* NodeWriter for root node */
  int rc = *pRc;                  /* Error code */

  /* Set iRoot to the index in pWriter->aNodeWriter[] of the output segment 
  ** root node. If the segment fits entirely on a single leaf node, iRoot
  ** will be set to 0. If the root node is the parent of the leaves, iRoot
  ** will be 1. And so on.  */
  for(iRoot=FTS_MAX_APPENDABLE_HEIGHT-1; iRoot>=0; iRoot--){
    NodeWriter *pNode = &pWriter->aNodeWriter[iRoot];
    if( pNode->block.n>0 ) break;
    assert( *pRc || pNode->block.nAlloc==0 );
    assert( *pRc || pNode->key.nAlloc==0 );
    sqlite3_free(pNode->block.a);
    sqlite3_free(pNode->key.a);
  }

  /* Empty output segment. This is a no-op. */
  if( iRoot<0 ) return;

  /* The entire output segment fits on a single node. Normally, this means
  ** the node would be stored as a blob in the "root" column of the %_segdir
  ** table. However, this is not permitted in this case. The problem is that 
  ** space has already been reserved in the %_segments table, and so the 
  ** start_block and end_block fields of the %_segdir table must be populated. 
  ** And, by design or by accident, released versions of FTS cannot handle 
  ** segments that fit entirely on the root node with start_block!=0.
  **
  ** Instead, create a synthetic root node that contains nothing but a 
  ** pointer to the single content node. So that the segment consists of a
  ** single leaf and a single interior (root) node.
  **
  ** Todo: Better might be to defer allocating space in the %_segments 
  ** table until we are sure it is needed.
  */
  if( iRoot==0 ){
    Blob *pBlock = &pWriter->aNodeWriter[1].block;
    blobGrowBuffer(pBlock, 1 + FTS3_VARINT_MAX, &rc);
    if( rc==SQLITE_OK ){
      pBlock->a[0] = 0x01;
      pBlock->n = 1 + sqlite3Fts3PutVarint(
          &pBlock->a[1], pWriter->aNodeWriter[0].iBlock
      );
    }
    iRoot = 1;
  }
  pRoot = &pWriter->aNodeWriter[iRoot];

  /* Flush all currently outstanding nodes to disk. */
  for(i=0; i<iRoot; i++){
    NodeWriter *pNode = &pWriter->aNodeWriter[i];
    if( pNode->block.n>0 && rc==SQLITE_OK ){
      rc = fts3WriteSegment(p, pNode->iBlock, pNode->block.a, pNode->block.n);
    }
    sqlite3_free(pNode->block.a);
    sqlite3_free(pNode->key.a);
  }

  /* Write the %_segdir record. */
  if( rc==SQLITE_OK ){
    rc = fts3WriteSegdir(p, 
        pWriter->iAbsLevel+1,               /* level */
        pWriter->iIdx,                      /* idx */
        pWriter->iStart,                    /* start_block */
        pWriter->aNodeWriter[0].iBlock,     /* leaves_end_block */
        pWriter->iEnd,                      /* end_block */
        (pWriter->bNoLeafData==0 ? pWriter->nLeafData : 0),   /* end_block */
        pRoot->block.a, pRoot->block.n      /* root */
    );
  }
  sqlite3_free(pRoot->block.a);
  sqlite3_free(pRoot->key.a);

  *pRc = rc;
}