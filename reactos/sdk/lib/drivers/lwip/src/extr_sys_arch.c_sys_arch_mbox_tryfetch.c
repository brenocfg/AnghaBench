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
typedef  int /*<<< orphan*/  u32_t ;
typedef  int /*<<< orphan*/  sys_mbox_t ;

/* Variables and functions */
 scalar_t__ SYS_ARCH_TIMEOUT ; 
 int /*<<< orphan*/  SYS_MBOX_EMPTY ; 
 scalar_t__ sys_arch_mbox_fetch (int /*<<< orphan*/ *,void**,int) ; 

u32_t
sys_arch_mbox_tryfetch(sys_mbox_t *mbox, void **msg)
{
    if (sys_arch_mbox_fetch(mbox, msg, 1) != SYS_ARCH_TIMEOUT)
        return 0;
    else
        return SYS_MBOX_EMPTY;
}