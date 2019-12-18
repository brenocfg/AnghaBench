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
struct TYPE_3__ {int /*<<< orphan*/  number; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 size_t ARRAY_LEN (TYPE_1__*) ; 
 int /*<<< orphan*/  parent_death_signal ; 
 TYPE_1__* signal_names ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char* const) ; 

int set_pdeathsig(char* const arg) {
	size_t i;

	for (i = 0; i < ARRAY_LEN(signal_names); i++) {
		if (strcmp(signal_names[i].name, arg) == 0) {
			/* Signals start at value "1" */
			parent_death_signal = signal_names[i].number;
			return 0;
		}
	}

	return 1;
}