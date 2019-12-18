#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int nData; } ;
struct TYPE_6__ {scalar_t__ nData; int /*<<< orphan*/  iBlockid; scalar_t__ pData; TYPE_4__ term; } ;
typedef  TYPE_1__ InteriorReader ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dataBufferAppend (TYPE_4__*,scalar_t__,int) ; 
 int /*<<< orphan*/  dataBufferReset (TYPE_4__*) ; 
 int getVarint32 (scalar_t__,int*) ; 
 int /*<<< orphan*/  interiorReaderAtEnd (TYPE_1__*) ; 

__attribute__((used)) static void interiorReaderStep(InteriorReader *pReader){
  assert( !interiorReaderAtEnd(pReader) );

  /* If the last term has been read, signal eof, else construct the
  ** next term.
  */
  if( pReader->nData==0 ){
    dataBufferReset(&pReader->term);
  }else{
    int n, nPrefix, nSuffix;

    n = getVarint32(pReader->pData, &nPrefix);
    n += getVarint32(pReader->pData+n, &nSuffix);

    /* Truncate the current term and append suffix data. */
    pReader->term.nData = nPrefix;
    dataBufferAppend(&pReader->term, pReader->pData+n, nSuffix);

    assert( n+nSuffix<=pReader->nData );
    pReader->pData += n+nSuffix;
    pReader->nData -= n+nSuffix;
  }
  pReader->iBlockid++;
}