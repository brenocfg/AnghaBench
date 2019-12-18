#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  lsm_env ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 void* lsmMalloc (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 

void *lsmMallocZero(lsm_env *pEnv, size_t N){
  void *pRet;
  assert( pEnv );
  pRet = lsmMalloc(pEnv, N);
  if( pRet ) memset(pRet, 0, N);
  return pRet;
}