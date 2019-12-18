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
 int /*<<< orphan*/  iter_handlers (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  print_data_handler ; 
 int /*<<< orphan*/  print_delay_handler ; 
 int /*<<< orphan*/  print_device_handler ; 
 int /*<<< orphan*/  print_panic_handler ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
print_all_handlers(void)
{
	int count = 0, total = 0;

	(void) iter_handlers(print_device_handler, &count);
	if (count > 0) {
		total += count;
		(void) printf("\n");
		count = 0;
	}

	(void) iter_handlers(print_delay_handler, &count);
	if (count > 0) {
		total += count;
		(void) printf("\n");
		count = 0;
	}

	(void) iter_handlers(print_data_handler, &count);
	if (count > 0) {
		total += count;
		(void) printf("\n");
		count = 0;
	}

	(void) iter_handlers(print_panic_handler, &count);

	return (count + total);
}