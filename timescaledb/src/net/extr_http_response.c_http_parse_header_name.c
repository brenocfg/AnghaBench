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
struct TYPE_3__ {void* state; int /*<<< orphan*/  cur_header_name_len; scalar_t__ parse_offset; scalar_t__ raw_buffer; int /*<<< orphan*/  cur_header_value; } ;
typedef  TYPE_1__ HttpResponseState ;

/* Variables and functions */
#define  CARRIAGE_RETURN 129 
 void* HTTP_STATE_ALMOST_DONE ; 
 void* HTTP_STATE_ERROR ; 
 void* HTTP_STATE_HEADER_VALUE ; 
#define  SEP_CHAR 128 

__attribute__((used)) static void
http_parse_header_name(HttpResponseState *state, const char next)
{
	switch (next)
	{
		case SEP_CHAR:
			state->state = HTTP_STATE_HEADER_VALUE;
			state->cur_header_value = state->raw_buffer + state->parse_offset + 1;
			break;
		case CARRIAGE_RETURN:
			if (state->cur_header_name_len == 0)
			{
				state->state = HTTP_STATE_ALMOST_DONE;
				break;
			}
			else
			{
				/*
				 * I'm guessing getting a carriage return in the middle of
				 * field
				 */
				/* name is bad... */
				state->state = HTTP_STATE_ERROR;
				break;
			}
		default:
			/* Header names are only alphabetic chars */
			if (('a' <= next && next <= 'z') || ('A' <= next && next <= 'Z') || next == '-')
			{
				/* Good, then the next call will save this char */
				state->cur_header_name_len++;
				break;
			}
			state->state = HTTP_STATE_ERROR;
			break;
	}
}