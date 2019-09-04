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
typedef  int /*<<< orphan*/  macexpstackentry_t ;

/* Variables and functions */
 int /*<<< orphan*/ ** macexpstack ; 
 size_t macexpstackidx ; 
 int /*<<< orphan*/  pp_internal_error (char*,int,char*) ; 

__attribute__((used)) static macexpstackentry_t *pop_macro(void)
{
	if(macexpstackidx <= 0)
		pp_internal_error(__FILE__, __LINE__, "Macro expansion stack underflow\n");
	return macexpstack[--macexpstackidx];
}