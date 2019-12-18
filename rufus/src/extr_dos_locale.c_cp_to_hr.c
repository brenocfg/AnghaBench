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
typedef  scalar_t__ ULONG ;
struct TYPE_3__ {scalar_t__ cp; char const* name; } ;

/* Variables and functions */
 int ARRAYSIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* cp_hr_list ; 

__attribute__((used)) static const char* cp_to_hr(ULONG cp)
{
	int i;
	for (i=0; i<ARRAYSIZE(cp_hr_list); i++) {
		if (cp_hr_list[i].cp == cp) {
			return cp_hr_list[i].name;
		}
	}
	// Should never happen, so this oughta get some attention
	assert(i < ARRAYSIZE(cp_hr_list));
	return NULL;
}