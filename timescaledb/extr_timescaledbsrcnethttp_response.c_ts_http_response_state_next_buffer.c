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
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {scalar_t__ offset; char* raw_buffer; } ;
typedef  TYPE_1__ HttpResponseState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ MAX_RAW_BUFFER_SIZE ; 
 int /*<<< orphan*/  ts_http_response_state_buffer_remaining (TYPE_1__*) ; 

char *
ts_http_response_state_next_buffer(HttpResponseState *state, ssize_t *bufsize)
{
	Assert(state->offset <= MAX_RAW_BUFFER_SIZE);

	if (NULL != bufsize)
		*bufsize = ts_http_response_state_buffer_remaining(state);

	/*
	 * This should not happen, be we return NULL in this case and let caller
	 * deal with it
	 */
	if (state->offset > MAX_RAW_BUFFER_SIZE)
		return NULL;

	return state->raw_buffer + state->offset;
}