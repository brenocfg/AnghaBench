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
struct TYPE_5__ {void* lon; void* lat; } ;
struct TYPE_6__ {TYPE_1__ loc; } ;
typedef  TYPE_2__ location_manual_state_t ;

/* Variables and functions */
 void* NAN ; 
 TYPE_2__* malloc (int) ; 

__attribute__((used)) static int
location_manual_init(location_manual_state_t **state)
{
	*state = malloc(sizeof(location_manual_state_t));
	if (*state == NULL) return -1;

	location_manual_state_t *s = *state;
	s->loc.lat = NAN;
	s->loc.lon = NAN;

	return 0;
}