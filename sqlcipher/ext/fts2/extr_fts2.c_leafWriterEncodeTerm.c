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
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ nData; } ;
struct TYPE_6__ {int nData; char const* pData; } ;
struct TYPE_5__ {TYPE_3__ term; TYPE_4__ data; } ;
typedef  TYPE_1__ LeafWriter ;

/* Variables and functions */
 int VARINT_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dataBufferAppend2 (TYPE_4__*,char*,int,char const*,int) ; 
 int /*<<< orphan*/  dataBufferReplace (TYPE_3__*,char const*,int) ; 
 int putVarint (char*,int) ; 

__attribute__((used)) static int leafWriterEncodeTerm(LeafWriter *pWriter,
                                const char *pTerm, int nTerm){
  char c[VARINT_MAX+VARINT_MAX];
  int n, nPrefix = 0;

  assert( nTerm>0 );
  while( nPrefix<pWriter->term.nData &&
         pTerm[nPrefix]==pWriter->term.pData[nPrefix] ){
    nPrefix++;
    /* Failing this implies that the terms weren't in order. */
    assert( nPrefix<nTerm );
  }

  if( pWriter->data.nData==0 ){
    /* Encode the node header and leading term as:
    **  varint(0)
    **  varint(nTerm)
    **  char pTerm[nTerm]
    */
    n = putVarint(c, '\0');
    n += putVarint(c+n, nTerm);
    dataBufferAppend2(&pWriter->data, c, n, pTerm, nTerm);
  }else{
    /* Delta-encode the term as:
    **  varint(nPrefix)
    **  varint(nSuffix)
    **  char pTermSuffix[nSuffix]
    */
    n = putVarint(c, nPrefix);
    n += putVarint(c+n, nTerm-nPrefix);
    dataBufferAppend2(&pWriter->data, c, n, pTerm+nPrefix, nTerm-nPrefix);
  }
  dataBufferReplace(&pWriter->term, pTerm, nTerm);

  return nPrefix+1;
}