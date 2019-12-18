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
typedef  int /*<<< orphan*/  progress_t ;
typedef  int /*<<< orphan*/  printf_t ;

/* Variables and functions */
 unsigned long* bled_cancel_request ; 
 int bled_initialized ; 
 int /*<<< orphan*/  bled_printf ; 
 int /*<<< orphan*/  bled_progress ; 

int bled_init(printf_t print_function, progress_t progress_function, unsigned long* cancel_request)
{
	if (bled_initialized)
		return -1;
	bled_initialized = true;
	bled_printf = print_function;
	bled_progress = progress_function;
	bled_cancel_request = cancel_request;
	return 0;
}