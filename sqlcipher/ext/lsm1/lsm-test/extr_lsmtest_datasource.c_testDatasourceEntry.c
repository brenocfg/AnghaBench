#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int eType; int nMinKey; int nMaxVal; int nMinVal; void* aVal; void* aKey; int /*<<< orphan*/  nMaxKey; } ;
typedef  TYPE_1__ Datasource ;

/* Variables and functions */
#define  TEST_DATASOURCE_RANDOM 129 
#define  TEST_DATASOURCE_SEQUENCE 128 
 int /*<<< orphan*/  assert (int) ; 
 int sprintf (void*,char*,int) ; 
 int /*<<< orphan*/  testPrngString (int,void*,int) ; 
 int testPrngValue (int) ; 

void testDatasourceEntry(
  Datasource *p, 
  int iData, 
  void **ppKey, int *pnKey,
  void **ppVal, int *pnVal
){
  assert( (ppKey==0)==(pnKey==0) );
  assert( (ppVal==0)==(pnVal==0) );

  if( ppKey ){
    int nKey = 0;
    switch( p->eType ){
      case TEST_DATASOURCE_RANDOM: {
        int nRange = (1 + p->nMaxKey - p->nMinKey);
        nKey = (int)( testPrngValue((u32)iData) % nRange ) + p->nMinKey; 
        testPrngString((u32)iData, p->aKey, nKey);
        break;
      }
      case TEST_DATASOURCE_SEQUENCE:
        nKey = sprintf(p->aKey, "%012d", iData);
        break;
    }
    *ppKey = p->aKey;
    *pnKey = nKey;
  }
  if( ppVal ){
    u32 nVal = testPrngValue((u32)iData)%(1+p->nMaxVal-p->nMinVal)+p->nMinVal;
    testPrngString((u32)~iData, p->aVal, (int)nVal);
    *ppVal = p->aVal;
    *pnVal = (int)nVal;
  }
}