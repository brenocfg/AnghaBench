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
struct TYPE_5__ {int /*<<< orphan*/  (* xFree ) (TYPE_1__*,void*) ;} ;
typedef  TYPE_1__ lsm_env ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,void*) ; 

void lsmFree(lsm_env *pEnv, void *p){
  assert( pEnv );
  pEnv->xFree(pEnv, p);
}