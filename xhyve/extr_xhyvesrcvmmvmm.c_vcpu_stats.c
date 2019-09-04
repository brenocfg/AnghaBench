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
struct vm {TYPE_1__* vcpu; } ;
struct TYPE_2__ {void* stats; } ;

/* Variables and functions */

void *
vcpu_stats(struct vm *vm, int vcpuid)
{

	return (vm->vcpu[vcpuid].stats);
}