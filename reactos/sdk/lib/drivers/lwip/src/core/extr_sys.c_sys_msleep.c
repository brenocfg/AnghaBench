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
typedef  scalar_t__ u32_t ;
typedef  int /*<<< orphan*/  sys_sem_t ;
typedef  scalar_t__ err_t ;

/* Variables and functions */
 scalar_t__ ERR_OK ; 
 int /*<<< orphan*/  sys_arch_sem_wait (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  sys_sem_free (int /*<<< orphan*/ *) ; 
 scalar_t__ sys_sem_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
sys_msleep(u32_t ms)
{
  if (ms > 0) {
    sys_sem_t delaysem;
    err_t err = sys_sem_new(&delaysem, 0);
    if (err == ERR_OK) {
      sys_arch_sem_wait(&delaysem, ms);
      sys_sem_free(&delaysem);
    }
  }
}