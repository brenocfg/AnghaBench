#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ sqlite_int64 ;
struct TYPE_12__ {scalar_t__ iType; } ;
struct TYPE_11__ {int idx; TYPE_2__* pReader; } ;
typedef  TYPE_1__ OrderedDLReader ;
typedef  int /*<<< orphan*/  DataBuffer ;
typedef  int /*<<< orphan*/  DLWriter ;
typedef  TYPE_2__ DLReader ;

/* Variables and functions */
 int MERGE_COUNT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dataBufferAppend (int /*<<< orphan*/ *,char const*,scalar_t__) ; 
 int /*<<< orphan*/  dataBufferExpand (int /*<<< orphan*/ *,int) ; 
 scalar_t__ dlrAllDataBytes (TYPE_2__*) ; 
 int /*<<< orphan*/  dlrAtEnd (TYPE_2__*) ; 
 char const* dlrDocData (TYPE_2__*) ; 
 int dlrDocDataBytes (TYPE_2__*) ; 
 scalar_t__ dlrDocid (TYPE_2__*) ; 
 int /*<<< orphan*/  dlrStep (TYPE_2__*) ; 
 int /*<<< orphan*/  dlwAppend (int /*<<< orphan*/ *,char const*,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  dlwDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlwInit (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  orderedDLReaderReorder (TYPE_1__*,int) ; 

__attribute__((used)) static void docListMerge(DataBuffer *out,
                         DLReader *pReaders, int nReaders){
  OrderedDLReader readers[MERGE_COUNT];
  DLWriter writer;
  int i, n;
  const char *pStart = 0;
  int nStart = 0;
  sqlite_int64 iFirstDocid = 0, iLastDocid = 0;

  assert( nReaders>0 );
  if( nReaders==1 ){
    dataBufferAppend(out, dlrDocData(pReaders), dlrAllDataBytes(pReaders));
    return;
  }

  assert( nReaders<=MERGE_COUNT );
  n = 0;
  for(i=0; i<nReaders; i++){
    assert( pReaders[i].iType==pReaders[0].iType );
    readers[i].pReader = pReaders+i;
    readers[i].idx = i;
    n += dlrAllDataBytes(&pReaders[i]);
  }
  /* Conservatively size output to sum of inputs.  Output should end
  ** up strictly smaller than input.
  */
  dataBufferExpand(out, n);

  /* Get the readers into sorted order. */
  while( i-->0 ){
    orderedDLReaderReorder(readers+i, nReaders-i);
  }

  dlwInit(&writer, pReaders[0].iType, out);
  while( !dlrAtEnd(readers[0].pReader) ){
    sqlite_int64 iDocid = dlrDocid(readers[0].pReader);

    /* If this is a continuation of the current buffer to copy, extend
    ** that buffer.  memcpy() seems to be more efficient if it has a
    ** lots of data to copy.
    */
    if( dlrDocData(readers[0].pReader)==pStart+nStart ){
      nStart += dlrDocDataBytes(readers[0].pReader);
    }else{
      if( pStart!=0 ){
        dlwAppend(&writer, pStart, nStart, iFirstDocid, iLastDocid);
      }
      pStart = dlrDocData(readers[0].pReader);
      nStart = dlrDocDataBytes(readers[0].pReader);
      iFirstDocid = iDocid;
    }
    iLastDocid = iDocid;
    dlrStep(readers[0].pReader);

    /* Drop all of the older elements with the same docid. */
    for(i=1; i<nReaders &&
             !dlrAtEnd(readers[i].pReader) &&
             dlrDocid(readers[i].pReader)==iDocid; i++){
      dlrStep(readers[i].pReader);
    }

    /* Get the readers back into order. */
    while( i-->0 ){
      orderedDLReaderReorder(readers+i, nReaders-i);
    }
  }

  /* Copy over any remaining elements. */
  if( nStart>0 ) dlwAppend(&writer, pStart, nStart, iFirstDocid, iLastDocid);
  dlwDestroy(&writer);
}