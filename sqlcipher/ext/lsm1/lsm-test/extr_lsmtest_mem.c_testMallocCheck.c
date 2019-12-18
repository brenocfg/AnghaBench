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
struct TYPE_3__ {scalar_t__ pMemCtx; } ;
typedef  TYPE_1__ lsm_env ;
typedef  int /*<<< orphan*/  TmGlobal ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  tmMallocCheck (int /*<<< orphan*/ *,int*,int*,int /*<<< orphan*/ *) ; 

void testMallocCheck(
  lsm_env *pEnv,
  int *pnLeakAlloc,
  int *pnLeakByte,
  FILE *pFile
){
  if( pEnv->pMemCtx==0 ){
    *pnLeakAlloc = 0;
    *pnLeakByte = 0;
  }else{
    tmMallocCheck((TmGlobal *)(pEnv->pMemCtx), pnLeakAlloc, pnLeakByte, pFile);
  }
}