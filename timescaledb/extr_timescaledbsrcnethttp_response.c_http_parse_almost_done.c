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
struct TYPE_3__ {int /*<<< orphan*/  state; int /*<<< orphan*/  content_length; scalar_t__ parse_offset; scalar_t__ raw_buffer; int /*<<< orphan*/  body_start; } ;
typedef  TYPE_1__ HttpResponseState ;

/* Variables and functions */
 int /*<<< orphan*/  HTTP_STATE_BODY ; 
 int /*<<< orphan*/  HTTP_STATE_DONE ; 
 int /*<<< orphan*/  HTTP_STATE_ERROR ; 
#define  NEW_LINE 128 

__attribute__((used)) static void
http_parse_almost_done(HttpResponseState *state, const char next)
{
	/* Don't do anything, this is intermediate state */
	switch (next)
	{
		case NEW_LINE:
			state->state = HTTP_STATE_BODY;
			state->body_start = state->raw_buffer + state->parse_offset + 1;
			/* Special case if there is no body */
			if (state->content_length == 0)
				state->state = HTTP_STATE_DONE;
			break;
		default:
			state->state = HTTP_STATE_ERROR;
			break;
	}
}