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
typedef  scalar_t__ ssize_t ;
struct TYPE_3__ {scalar_t__ offset; } ;
typedef  TYPE_1__ HttpResponseState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ MAX_RAW_BUFFER_SIZE ; 

ssize_t
ts_http_response_state_buffer_remaining(HttpResponseState *state)
{
	Assert(state->offset <= MAX_RAW_BUFFER_SIZE);

	return MAX_RAW_BUFFER_SIZE - state->offset;
}