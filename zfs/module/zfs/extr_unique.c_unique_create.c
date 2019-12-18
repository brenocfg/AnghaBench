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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  unique_insert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unique_remove (int /*<<< orphan*/ ) ; 

uint64_t
unique_create(void)
{
	uint64_t value = unique_insert(0);
	unique_remove(value);
	return (value);
}