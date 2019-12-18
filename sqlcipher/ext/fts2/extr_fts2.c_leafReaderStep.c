#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int nData; } ;
struct TYPE_5__ {int nData; scalar_t__ pData; TYPE_4__ term; } ;
typedef  TYPE_1__ LeafReader ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dataBufferAppend (TYPE_4__*,scalar_t__,int) ; 
 int getVarint32 (scalar_t__,int*) ; 
 int /*<<< orphan*/  leafReaderAtEnd (TYPE_1__*) ; 

__attribute__((used)) static void leafReaderStep(LeafReader *pReader){
  int n, nData, nPrefix, nSuffix;
  assert( !leafReaderAtEnd(pReader) );

  /* Skip previous entry's data block. */
  n = getVarint32(pReader->pData, &nData);
  assert( n+nData<=pReader->nData );
  pReader->pData += n+nData;
  pReader->nData -= n+nData;

  if( !leafReaderAtEnd(pReader) ){
    /* Construct the new term using a prefix from the old term plus a
    ** suffix from the leaf data.
    */
    n = getVarint32(pReader->pData, &nPrefix);
    n += getVarint32(pReader->pData+n, &nSuffix);
    assert( n+nSuffix<pReader->nData );
    pReader->term.nData = nPrefix;
    dataBufferAppend(&pReader->term, pReader->pData+n, nSuffix);

    pReader->pData += n+nSuffix;
    pReader->nData -= n+nSuffix;
  }
}