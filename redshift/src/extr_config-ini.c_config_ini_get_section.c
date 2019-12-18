#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* sections; } ;
typedef  TYPE_1__ config_ini_state_t ;
struct TYPE_6__ {struct TYPE_6__* next; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ config_ini_section_t ;

/* Variables and functions */
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char const*) ; 

config_ini_section_t *
config_ini_get_section(config_ini_state_t *state, const char *name)
{
	config_ini_section_t *section = state->sections;
	while (section != NULL) {
		if (strcasecmp(section->name, name) == 0) {
			return section;
		}
		section = section->next;
	}

	return NULL;
}