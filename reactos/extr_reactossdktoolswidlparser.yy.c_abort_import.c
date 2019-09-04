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
struct TYPE_2__ {int /*<<< orphan*/  temp_name; } ;

/* Variables and functions */
 TYPE_1__* import_stack ; 
 int import_stack_ptr ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

void abort_import(void)
{
	int ptr;

	for (ptr=0; ptr<import_stack_ptr; ptr++)
		unlink(import_stack[ptr].temp_name);
}