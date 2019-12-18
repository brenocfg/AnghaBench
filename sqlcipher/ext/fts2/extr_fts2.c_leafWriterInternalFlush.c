#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ sqlite_int64 ;
typedef  int /*<<< orphan*/  fulltext_vtab ;
struct TYPE_4__ {int nData; char* pData; } ;
struct TYPE_5__ {int nTermDistinct; int has_parent; scalar_t__ iEndBlockid; scalar_t__ iStartBlockid; int /*<<< orphan*/  parentWriter; TYPE_1__ data; } ;
typedef  TYPE_2__ LeafWriter ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_VALID_LEAF_NODE (char*,int) ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int block_insert (int /*<<< orphan*/ *,char*,int,scalar_t__*) ; 
 int getVarint32 (char*,int*) ; 
 int /*<<< orphan*/  interiorWriterAppend (int /*<<< orphan*/ *,char const*,int,scalar_t__) ; 
 int /*<<< orphan*/  interiorWriterInit (int,char const*,int,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int leafWriterInternalFlush(fulltext_vtab *v, LeafWriter *pWriter,
                                   int iData, int nData){
  sqlite_int64 iBlockid = 0;
  const char *pStartingTerm;
  int nStartingTerm, rc, n;

  /* Must have the leading varint(0) flag, plus at least some
  ** valid-looking data.
  */
  assert( nData>2 );
  assert( iData>=0 );
  assert( iData+nData<=pWriter->data.nData );
  ASSERT_VALID_LEAF_NODE(pWriter->data.pData+iData, nData);

  rc = block_insert(v, pWriter->data.pData+iData, nData, &iBlockid);
  if( rc!=SQLITE_OK ) return rc;
  assert( iBlockid!=0 );

  /* Reconstruct the first term in the leaf for purposes of building
  ** the interior node.
  */
  n = getVarint32(pWriter->data.pData+iData+1, &nStartingTerm);
  pStartingTerm = pWriter->data.pData+iData+1+n;
  assert( pWriter->data.nData>iData+1+n+nStartingTerm );
  assert( pWriter->nTermDistinct>0 );
  assert( pWriter->nTermDistinct<=nStartingTerm );
  nStartingTerm = pWriter->nTermDistinct;

  if( pWriter->has_parent ){
    interiorWriterAppend(&pWriter->parentWriter,
                         pStartingTerm, nStartingTerm, iBlockid);
  }else{
    interiorWriterInit(1, pStartingTerm, nStartingTerm, iBlockid,
                       &pWriter->parentWriter);
    pWriter->has_parent = 1;
  }

  /* Track the span of this segment's leaf nodes. */
  if( pWriter->iEndBlockid==0 ){
    pWriter->iEndBlockid = pWriter->iStartBlockid = iBlockid;
  }else{
    pWriter->iEndBlockid++;
    assert( iBlockid==pWriter->iEndBlockid );
  }

  return SQLITE_OK;
}