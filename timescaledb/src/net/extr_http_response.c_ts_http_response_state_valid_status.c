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
struct TYPE_3__ {int status_code; } ;
typedef  TYPE_1__ HttpResponseState ;

/* Variables and functions */

bool
ts_http_response_state_valid_status(HttpResponseState *state)
{
	/* If the status code hasn't been parsed yet, return */
	if (state->status_code == -1)
		return true;
	/* If it's a bad status code, then bad! */
	if (state->status_code / 100 == 2)
		return true;
	return false;
}