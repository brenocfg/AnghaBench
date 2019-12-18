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
struct TYPE_3__ {scalar_t__ nStem; scalar_t__* apHash; scalar_t__* aQueue; scalar_t__ pDone; scalar_t__ pStem; scalar_t__ mxQueue; scalar_t__ rLimit; } ;
typedef  TYPE_1__ fuzzer_cursor ;
typedef  scalar_t__ fuzzer_cost ;

/* Variables and functions */
 int FUZZER_NQUEUE ; 
 int /*<<< orphan*/  fuzzerClearStemList (scalar_t__) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void fuzzerClearCursor(fuzzer_cursor *pCur, int clearHash){
  int i;
  fuzzerClearStemList(pCur->pStem);
  fuzzerClearStemList(pCur->pDone);
  for(i=0; i<FUZZER_NQUEUE; i++) fuzzerClearStemList(pCur->aQueue[i]);
  pCur->rLimit = (fuzzer_cost)0;
  if( clearHash && pCur->nStem ){
    pCur->mxQueue = 0;
    pCur->pStem = 0;
    pCur->pDone = 0;
    memset(pCur->aQueue, 0, sizeof(pCur->aQueue));
    memset(pCur->apHash, 0, sizeof(pCur->apHash));
  }
  pCur->nStem = 0;
}