#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lsm_mutex ;
struct TYPE_2__ {int bHeld; } ;
typedef  TYPE_1__ NoopMutex ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void lsmPosixOsMutexEnter(lsm_mutex *pMutex){ 
  NoopMutex *p = (NoopMutex *)pMutex;
  assert( p->bHeld==0 );
  p->bHeld = 1;
}