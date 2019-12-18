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
struct TYPE_4__ {int content_length; void* state; int /*<<< orphan*/  cur_header_value_len; int /*<<< orphan*/  cur_header_name_len; int /*<<< orphan*/  cur_header_value; int /*<<< orphan*/ * cur_header_name; } ;
typedef  TYPE_1__ HttpResponseState ;

/* Variables and functions */
 int /*<<< orphan*/  HTTP_CONTENT_LENGTH ; 
 void* HTTP_STATE_ERROR ; 
 void* HTTP_STATE_HEADER_NAME ; 
#define  NEW_LINE 128 
 int /*<<< orphan*/  http_response_state_add_header (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sscanf (int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
http_parse_interm(HttpResponseState *state, const char next)
{
	int temp_length;

	switch (next)
	{
		case NEW_LINE:
			state->state = HTTP_STATE_HEADER_NAME;
			/* Store another header */
			http_response_state_add_header(state,
										   state->cur_header_name,
										   state->cur_header_name_len,
										   state->cur_header_value,
										   state->cur_header_value_len);

			/* Check if the line we just read is Content-Length */
			if (state->cur_header_name != NULL &&
				strncmp(HTTP_CONTENT_LENGTH, state->cur_header_name, state->cur_header_name_len) ==
					0)
			{
				if (sscanf(state->cur_header_value, "%d", &temp_length) == 1)
				{
					state->content_length = temp_length;
				}
				else
				{
					state->state = HTTP_STATE_ERROR;
					break;
				}
			}
			state->cur_header_name_len = 0;
			state->cur_header_value_len = 0;
			break;
		default:
			state->state = HTTP_STATE_ERROR;
			break;
	}
}