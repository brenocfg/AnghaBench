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
 int ARRAYSIZE (char const***) ; 
 int /*<<< orphan*/  assert (int) ; 
 char const*** kb_hr_list ; 
 scalar_t__ safe_strcmp (char const*,char const*) ; 

__attribute__((used)) static const char* kb_to_hr(const char* kb)
{
	int i;
	for (i=0; i<ARRAYSIZE(kb_hr_list); i++) {
		if (safe_strcmp(kb, kb_hr_list[i][0]) == 0) {
			return kb_hr_list[i][1];
		}
	}
	// Should never happen, so let's try to get some attention here
	assert(i < ARRAYSIZE(kb_hr_list));
	return NULL;
}