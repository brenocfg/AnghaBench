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

/* Variables and functions */
 void* atomic_cas_ptr (void*,void*,void*) ; 

void *
casptr(void *target, void *arg1, void *arg2)
{
	return (atomic_cas_ptr(target, arg1, arg2));
}