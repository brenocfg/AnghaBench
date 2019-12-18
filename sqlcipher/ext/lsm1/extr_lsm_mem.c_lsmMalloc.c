#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* (* xMalloc ) (TYPE_1__*,size_t) ;} ;
typedef  TYPE_1__ lsm_env ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 void* stub1 (TYPE_1__*,size_t) ; 

void *lsmMalloc(lsm_env *pEnv, size_t N){
  assert( pEnv );
  return pEnv->xMalloc(pEnv, N);
}