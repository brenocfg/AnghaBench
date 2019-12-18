#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * displays; } ;
typedef  TYPE_1__ quartz_state_t ;

/* Variables and functions */
 TYPE_1__* malloc (int) ; 

__attribute__((used)) static int
quartz_init(quartz_state_t **state)
{
	*state = malloc(sizeof(quartz_state_t));
	if (*state == NULL) return -1;

	quartz_state_t *s = *state;
	s->displays = NULL;

	return 0;
}