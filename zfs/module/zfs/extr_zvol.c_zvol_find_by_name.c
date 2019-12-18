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
typedef  int /*<<< orphan*/  zvol_state_t ;

/* Variables and functions */
 int /*<<< orphan*/ * zvol_find_by_name_hash (char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zvol_name_hash (char const*) ; 

__attribute__((used)) static zvol_state_t *
zvol_find_by_name(const char *name, int mode)
{
	return (zvol_find_by_name_hash(name, zvol_name_hash(name), mode));
}