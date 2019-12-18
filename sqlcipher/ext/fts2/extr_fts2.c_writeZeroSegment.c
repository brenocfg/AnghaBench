#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fulltext_vtab ;
typedef  int /*<<< orphan*/  fts2HashElem ;
typedef  int /*<<< orphan*/  fts2Hash ;
struct TYPE_10__ {int /*<<< orphan*/  nTerm; int /*<<< orphan*/  pTerm; int /*<<< orphan*/  pCollector; } ;
typedef  TYPE_1__ TermData ;
struct TYPE_11__ {int /*<<< orphan*/  nData; int /*<<< orphan*/  pData; } ;
typedef  int /*<<< orphan*/  LeafWriter ;
typedef  TYPE_2__ DataBuffer ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dataBufferDestroy (TYPE_2__*) ; 
 int /*<<< orphan*/  dataBufferInit (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dataBufferReset (TYPE_2__*) ; 
 int /*<<< orphan*/  dlcAddDoclist (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int fts2HashCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fts2HashData (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fts2HashFirst (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fts2HashKey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fts2HashKeysize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fts2HashNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  leafWriterDestroy (int /*<<< orphan*/ *) ; 
 int leafWriterFinalize (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  leafWriterInit (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int leafWriterStep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qsort (TYPE_1__*,int,int,int /*<<< orphan*/ ) ; 
 int segdirNextIndex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_1__*) ; 
 TYPE_1__* sqlite3_malloc (int) ; 
 int /*<<< orphan*/  termDataCmp ; 

__attribute__((used)) static int writeZeroSegment(fulltext_vtab *v, fts2Hash *pTerms){
  fts2HashElem *e;
  int idx, rc, i, n;
  TermData *pData;
  LeafWriter writer;
  DataBuffer dl;

  /* Determine the next index at level 0, merging as necessary. */
  rc = segdirNextIndex(v, 0, &idx);
  if( rc!=SQLITE_OK ) return rc;

  n = fts2HashCount(pTerms);
  pData = sqlite3_malloc(n*sizeof(TermData));

  for(i = 0, e = fts2HashFirst(pTerms); e; i++, e = fts2HashNext(e)){
    assert( i<n );
    pData[i].pTerm = fts2HashKey(e);
    pData[i].nTerm = fts2HashKeysize(e);
    pData[i].pCollector = fts2HashData(e);
  }
  assert( i==n );

  /* TODO(shess) Should we allow user-defined collation sequences,
  ** here?  I think we only need that once we support prefix searches.
  */
  if( n>1 ) qsort(pData, n, sizeof(*pData), termDataCmp);

  /* TODO(shess) Refactor so that we can write directly to the segment
  ** DataBuffer, as happens for segment merges.
  */
  leafWriterInit(0, idx, &writer);
  dataBufferInit(&dl, 0);
  for(i=0; i<n; i++){
    dataBufferReset(&dl);
    dlcAddDoclist(pData[i].pCollector, &dl);
    rc = leafWriterStep(v, &writer,
                        pData[i].pTerm, pData[i].nTerm, dl.pData, dl.nData);
    if( rc!=SQLITE_OK ) goto err;
  }
  rc = leafWriterFinalize(v, &writer);

 err:
  dataBufferDestroy(&dl);
  sqlite3_free(pData);
  leafWriterDestroy(&writer);
  return rc;
}