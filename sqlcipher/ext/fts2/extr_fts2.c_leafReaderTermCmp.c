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
struct TYPE_4__ {int nData; int /*<<< orphan*/  pData; } ;
struct TYPE_5__ {TYPE_1__ term; } ;
typedef  TYPE_2__ LeafReader ;

/* Variables and functions */
 int memcmp (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static int leafReaderTermCmp(LeafReader *pReader,
                             const char *pTerm, int nTerm, int isPrefix){
  int c, n = pReader->term.nData<nTerm ? pReader->term.nData : nTerm;
  if( n==0 ){
    if( pReader->term.nData>0 ) return -1;
    if(nTerm>0 ) return 1;
    return 0;
  }

  c = memcmp(pReader->term.pData, pTerm, n);
  if( c!=0 ) return c;
  if( isPrefix && n==nTerm ) return 0;
  return pReader->term.nData - nTerm;
}