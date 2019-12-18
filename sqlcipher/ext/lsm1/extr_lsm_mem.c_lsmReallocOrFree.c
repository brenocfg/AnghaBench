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
 int /*<<< orphan*/  lsm_free (int /*<<< orphan*/ *,void*) ; 
 void* lsm_realloc (int /*<<< orphan*/ *,void*,size_t) ; 

void *lsmReallocOrFree(lsm_env *pEnv, void *p, size_t N){
  void *pNew;
  pNew = lsm_realloc(pEnv, p, N);
  if( !pNew ) lsm_free(pEnv, p);
  return pNew;
}