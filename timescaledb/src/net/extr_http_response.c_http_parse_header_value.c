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
struct TYPE_3__ {int /*<<< orphan*/  cur_header_value_len; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ HttpResponseState ;

/* Variables and functions */
#define  CARRIAGE_RETURN 129 
 int /*<<< orphan*/  HTTP_STATE_ERROR ; 
 int /*<<< orphan*/  HTTP_STATE_INTERM ; 
#define  NEW_LINE 128 

__attribute__((used)) static void
http_parse_header_value(HttpResponseState *state, const char next)
{
	/* Allow everything except... \r, \n */
	switch (next)
	{
		case CARRIAGE_RETURN:
			state->state = HTTP_STATE_INTERM;
			break;
		case NEW_LINE:
			/* \n is not allowed */
			state->state = HTTP_STATE_ERROR;
			break;
		default:
			state->cur_header_value_len++;
			break;
	}
}