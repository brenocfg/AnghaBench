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
struct TYPE_4__ {char const* pData; int nData; int /*<<< orphan*/  term; } ;
typedef  TYPE_1__ LeafReader ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dataBufferInit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dataBufferReplace (int /*<<< orphan*/ *,char const*,int) ; 
 int getVarint32 (char const*,int*) ; 

__attribute__((used)) static void leafReaderInit(const char *pData, int nData,
                           LeafReader *pReader){
  int nTerm, n;

  assert( nData>0 );
  assert( pData[0]=='\0' );

  CLEAR(pReader);

  /* Read the first term, skipping the header byte. */
  n = getVarint32(pData+1, &nTerm);
  dataBufferInit(&pReader->term, nTerm);
  dataBufferReplace(&pReader->term, pData+1+n, nTerm);

  /* Position after the first term. */
  assert( 1+n+nTerm<nData );
  pReader->pData = pData+1+n+nTerm;
  pReader->nData = nData-1-n-nTerm;
}