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
struct TYPE_4__ {char const* pData; int nData; int /*<<< orphan*/  term; int /*<<< orphan*/  iBlockid; } ;
typedef  TYPE_1__ InteriorReader ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dataBufferInit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dataBufferReplace (int /*<<< orphan*/ *,char const*,int) ; 
 int getVarint (char const*,int /*<<< orphan*/ *) ; 
 int getVarint32 (char const*,int*) ; 

__attribute__((used)) static void interiorReaderInit(const char *pData, int nData,
                               InteriorReader *pReader){
  int n, nTerm;

  /* Require at least the leading flag byte */
  assert( nData>0 );
  assert( pData[0]!='\0' );

  CLEAR(pReader);

  /* Decode the base blockid, and set the cursor to the first term. */
  n = getVarint(pData+1, &pReader->iBlockid);
  assert( 1+n<=nData );
  pReader->pData = pData+1+n;
  pReader->nData = nData-(1+n);

  /* A single-child interior node (such as when a leaf node was too
  ** large for the segment directory) won't have any terms.
  ** Otherwise, decode the first term.
  */
  if( pReader->nData==0 ){
    dataBufferInit(&pReader->term, 0);
  }else{
    n = getVarint32(pReader->pData, &nTerm);
    dataBufferInit(&pReader->term, nTerm);
    dataBufferReplace(&pReader->term, pReader->pData+n, nTerm);
    assert( n+nTerm<=pReader->nData );
    pReader->pData += n+nTerm;
    pReader->nData -= n+nTerm;
  }
}