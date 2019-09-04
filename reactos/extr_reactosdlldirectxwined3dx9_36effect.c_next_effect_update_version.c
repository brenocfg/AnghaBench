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
struct d3dx9_base_effect {int dummy; } ;
typedef  int /*<<< orphan*/  ULONG64 ;

/* Variables and functions */
 int /*<<< orphan*/  get_version_counter_ptr (struct d3dx9_base_effect*) ; 
 int /*<<< orphan*/  next_update_version (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ULONG64 next_effect_update_version(struct d3dx9_base_effect *base)
{
    return next_update_version(get_version_counter_ptr(base));
}