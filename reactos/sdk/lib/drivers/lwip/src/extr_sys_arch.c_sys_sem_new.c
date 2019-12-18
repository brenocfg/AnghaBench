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
typedef  int u8_t ;
struct TYPE_3__ {int Valid; int /*<<< orphan*/  Event; } ;
typedef  TYPE_1__ sys_sem_t ;
typedef  int /*<<< orphan*/  err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  ERR_OK ; 
 int /*<<< orphan*/  KeInitializeEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SynchronizationEvent ; 

err_t
sys_sem_new(sys_sem_t *sem, u8_t count)
{
    ASSERT(count == 0 || count == 1);
    
    /* It seems lwIP uses the semaphore implementation as either a completion event or a lock
     * so I optimize for this case by using a synchronization event and setting its initial state
     * to signalled for a lock and non-signalled for a completion event */

    KeInitializeEvent(&sem->Event, SynchronizationEvent, count);
    
    sem->Valid = 1;
    
    return ERR_OK;
}