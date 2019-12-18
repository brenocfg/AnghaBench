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
typedef  int /*<<< orphan*/  fulltext_vtab ;
struct TYPE_7__ {scalar_t__ nData; int /*<<< orphan*/  pData; } ;
typedef  int /*<<< orphan*/  OptLeavesReader ;
typedef  int /*<<< orphan*/  LeafWriter ;
typedef  TYPE_1__ DataBuffer ;
typedef  int /*<<< orphan*/  DLReader ;

/* Variables and functions */
 int /*<<< orphan*/  DL_DEFAULT ; 
 int /*<<< orphan*/  LEAF_MAX ; 
 int MERGE_COUNT ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dataBufferDestroy (TYPE_1__*) ; 
 int /*<<< orphan*/  dataBufferInit (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dataBufferReset (TYPE_1__*) ; 
 int /*<<< orphan*/  dlrDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlrInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  docListMerge (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  docListTrim (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int leafWriterStep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  optLeavesReaderAtEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  optLeavesReaderData (int /*<<< orphan*/ *) ; 
 scalar_t__ optLeavesReaderDataBytes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  optLeavesReaderReorder (int /*<<< orphan*/ *,int) ; 
 int optLeavesReaderStep (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  optLeavesReaderTerm (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  optLeavesReaderTermBytes (int /*<<< orphan*/ *) ; 
 scalar_t__ optLeavesReaderTermCmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int optimizeInternal(fulltext_vtab *v,
                            OptLeavesReader *readers, int nReaders,
                            LeafWriter *pWriter){
  int i, rc = SQLITE_OK;
  DataBuffer doclist, merged, tmp;

  /* Order the readers. */
  i = nReaders;
  while( i-- > 0 ){
    optLeavesReaderReorder(&readers[i], nReaders-i);
  }

  dataBufferInit(&doclist, LEAF_MAX);
  dataBufferInit(&merged, LEAF_MAX);

  /* Exhausted readers bubble to the end, so when the first reader is
  ** at eof, all are at eof.
  */
  while( !optLeavesReaderAtEnd(&readers[0]) ){

    /* Figure out how many readers share the next term. */
    for(i=1; i<nReaders && !optLeavesReaderAtEnd(&readers[i]); i++){
      if( 0!=optLeavesReaderTermCmp(&readers[0], &readers[i]) ) break;
    }

    /* Special-case for no merge. */
    if( i==1 ){
      /* Trim deletions from the doclist. */
      dataBufferReset(&merged);
      docListTrim(DL_DEFAULT,
                  optLeavesReaderData(&readers[0]),
                  optLeavesReaderDataBytes(&readers[0]),
                  -1, DL_DEFAULT, &merged);
    }else{
      DLReader dlReaders[MERGE_COUNT];
      int iReader, nReaders;

      /* Prime the pipeline with the first reader's doclist.  After
      ** one pass index 0 will reference the accumulated doclist.
      */
      dlrInit(&dlReaders[0], DL_DEFAULT,
              optLeavesReaderData(&readers[0]),
              optLeavesReaderDataBytes(&readers[0]));
      iReader = 1;

      assert( iReader<i );  /* Must execute the loop at least once. */
      while( iReader<i ){
        /* Merge 16 inputs per pass. */
        for( nReaders=1; iReader<i && nReaders<MERGE_COUNT;
             iReader++, nReaders++ ){
          dlrInit(&dlReaders[nReaders], DL_DEFAULT,
                  optLeavesReaderData(&readers[iReader]),
                  optLeavesReaderDataBytes(&readers[iReader]));
        }

        /* Merge doclists and swap result into accumulator. */
        dataBufferReset(&merged);
        docListMerge(&merged, dlReaders, nReaders);
        tmp = merged;
        merged = doclist;
        doclist = tmp;

        while( nReaders-- > 0 ){
          dlrDestroy(&dlReaders[nReaders]);
        }

        /* Accumulated doclist to reader 0 for next pass. */
        dlrInit(&dlReaders[0], DL_DEFAULT, doclist.pData, doclist.nData);
      }

      /* Destroy reader that was left in the pipeline. */
      dlrDestroy(&dlReaders[0]);

      /* Trim deletions from the doclist. */
      dataBufferReset(&merged);
      docListTrim(DL_DEFAULT, doclist.pData, doclist.nData,
                  -1, DL_DEFAULT, &merged);
    }

    /* Only pass doclists with hits (skip if all hits deleted). */
    if( merged.nData>0 ){
      rc = leafWriterStep(v, pWriter,
                          optLeavesReaderTerm(&readers[0]),
                          optLeavesReaderTermBytes(&readers[0]),
                          merged.pData, merged.nData);
      if( rc!=SQLITE_OK ) goto err;
    }

    /* Step merged readers to next term and reorder. */
    while( i-- > 0 ){
      rc = optLeavesReaderStep(v, &readers[i]);
      if( rc!=SQLITE_OK ) goto err;

      optLeavesReaderReorder(&readers[i], nReaders-i);
    }
  }

 err:
  dataBufferDestroy(&doclist);
  dataBufferDestroy(&merged);
  return rc;
}