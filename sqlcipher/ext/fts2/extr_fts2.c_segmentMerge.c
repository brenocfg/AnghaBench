#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  lrs ;
typedef  int /*<<< orphan*/  fulltext_vtab ;
typedef  int /*<<< orphan*/  LeavesReader ;
typedef  int /*<<< orphan*/  LeafWriter ;

/* Variables and functions */
 int MERGE_COUNT ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  leafWriterDestroy (int /*<<< orphan*/ *) ; 
 int leafWriterFinalize (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  leafWriterInit (int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  leavesReaderAtEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  leavesReaderDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  leavesReaderReorder (int /*<<< orphan*/ *,int) ; 
 int leavesReaderStep (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ leavesReaderTermCmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int leavesReadersInit (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int*) ; 
 int leavesReadersMerge (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ **,char,int) ; 
 int segdirNextIndex (int /*<<< orphan*/ *,int,int*) ; 
 int segdir_delete (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int segmentMerge(fulltext_vtab *v, int iLevel){
  LeafWriter writer;
  LeavesReader lrs[MERGE_COUNT];
  int i, rc, idx = 0;

  /* Determine the next available segment index at the next level,
  ** merging as necessary.
  */
  rc = segdirNextIndex(v, iLevel+1, &idx);
  if( rc!=SQLITE_OK ) return rc;

  /* TODO(shess) This assumes that we'll always see exactly
  ** MERGE_COUNT segments to merge at a given level.  That will be
  ** broken if we allow the developer to request preemptive or
  ** deferred merging.
  */
  memset(&lrs, '\0', sizeof(lrs));
  rc = leavesReadersInit(v, iLevel, lrs, &i);
  if( rc!=SQLITE_OK ) return rc;
  assert( i==MERGE_COUNT );

  leafWriterInit(iLevel+1, idx, &writer);

  /* Since leavesReaderReorder() pushes readers at eof to the end,
  ** when the first reader is empty, all will be empty.
  */
  while( !leavesReaderAtEnd(lrs) ){
    /* Figure out how many readers share their next term. */
    for(i=1; i<MERGE_COUNT && !leavesReaderAtEnd(lrs+i); i++){
      if( 0!=leavesReaderTermCmp(lrs, lrs+i) ) break;
    }

    rc = leavesReadersMerge(v, lrs, i, &writer);
    if( rc!=SQLITE_OK ) goto err;

    /* Step forward those that were merged. */
    while( i-->0 ){
      rc = leavesReaderStep(v, lrs+i);
      if( rc!=SQLITE_OK ) goto err;

      /* Reorder by term, then by age. */
      leavesReaderReorder(lrs+i, MERGE_COUNT-i);
    }
  }

  for(i=0; i<MERGE_COUNT; i++){
    leavesReaderDestroy(&lrs[i]);
  }

  rc = leafWriterFinalize(v, &writer);
  leafWriterDestroy(&writer);
  if( rc!=SQLITE_OK ) return rc;

  /* Delete the merged segment data. */
  return segdir_delete(v, iLevel);

 err:
  for(i=0; i<MERGE_COUNT; i++){
    leavesReaderDestroy(&lrs[i]);
  }
  leafWriterDestroy(&writer);
  return rc;
}