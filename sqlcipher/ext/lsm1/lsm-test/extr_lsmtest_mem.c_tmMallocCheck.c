#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__** aHash; TYPE_2__* pFirst; } ;
typedef  TYPE_1__ TmGlobal ;
struct TYPE_7__ {scalar_t__ nByte; struct TYPE_7__* pNext; } ;
typedef  TYPE_2__ TmBlockHdr ;
struct TYPE_8__ {int nOutAlloc; int nOutByte; int nByte; int nAlloc; int /*<<< orphan*/ * aFrame; struct TYPE_8__* pNext; } ;
typedef  TYPE_3__ TmAgg ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int ArraySize (TYPE_3__**) ; 
 int TM_BACKTRACE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void tmMallocCheck(
  TmGlobal *pTm,
  int *pnLeakAlloc,
  int *pnLeakByte,
  FILE *pFile
){
  TmBlockHdr *pHdr;
  int nLeak = 0;
  int nByte = 0;

  if( pTm==0 ) return;

  for(pHdr=pTm->pFirst; pHdr; pHdr=pHdr->pNext){
    nLeak++; 
    nByte += pHdr->nByte;
  }
  if( pnLeakAlloc ) *pnLeakAlloc = nLeak;
  if( pnLeakByte ) *pnLeakByte = nByte;

#ifdef TM_BACKTRACE
  if( pFile ){
    int i;
    fprintf(pFile, "LEAKS\n");
    for(i=0; i<ArraySize(pTm->aHash); i++){
      TmAgg *pAgg;
      for(pAgg=pTm->aHash[i]; pAgg; pAgg=pAgg->pNext){
        if( pAgg->nOutAlloc ){
          int j;
          fprintf(pFile, "%d %d ", pAgg->nOutByte, pAgg->nOutAlloc);
          for(j=0; j<TM_BACKTRACE; j++){
            fprintf(pFile, "%p ", pAgg->aFrame[j]);
          }
          fprintf(pFile, "\n");
        }
      }
    }
    fprintf(pFile, "\nALLOCATIONS\n");
    for(i=0; i<ArraySize(pTm->aHash); i++){
      TmAgg *pAgg;
      for(pAgg=pTm->aHash[i]; pAgg; pAgg=pAgg->pNext){
        int j;
        fprintf(pFile, "%d %d ", pAgg->nByte, pAgg->nAlloc);
        for(j=0; j<TM_BACKTRACE; j++) fprintf(pFile, "%p ", pAgg->aFrame[j]);
        fprintf(pFile, "\n");
      }
    }
  }
#else
  (void)pFile;
#endif
}