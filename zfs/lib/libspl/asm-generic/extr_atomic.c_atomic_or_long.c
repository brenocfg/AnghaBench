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
typedef  int /*<<< orphan*/  ulong_t ;

/* Variables and functions */
 void atomic_or_ulong (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
atomic_or_long(ulong_t *target, ulong_t bits)
{
	return (atomic_or_ulong(target, bits));
}