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
struct TYPE_4__ {int /*<<< orphan*/ * saved_ramps; } ;
typedef  TYPE_1__ w32gdi_state_t ;

/* Variables and functions */
 TYPE_1__* malloc (int) ; 

__attribute__((used)) static int
w32gdi_init(w32gdi_state_t **state)
{
	*state = malloc(sizeof(w32gdi_state_t));
	if (state == NULL) return -1;

	w32gdi_state_t *s = *state;
	s->saved_ramps = NULL;

	return 0;
}