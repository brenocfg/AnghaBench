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
struct d3dx9_base_effect {int /*<<< orphan*/  version_counter; TYPE_1__* pool; } ;
typedef  int /*<<< orphan*/  ULONG64 ;
struct TYPE_2__ {int /*<<< orphan*/  version_counter; } ;

/* Variables and functions */

__attribute__((used)) static ULONG64 *get_version_counter_ptr(struct d3dx9_base_effect *base)
{
    return base->pool ? &base->pool->version_counter : &base->version_counter;
}