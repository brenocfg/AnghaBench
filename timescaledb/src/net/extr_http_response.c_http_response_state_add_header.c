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
struct TYPE_3__ {int /*<<< orphan*/ * headers; int /*<<< orphan*/  context; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_1__ HttpResponseState ;
typedef  int /*<<< orphan*/  HttpHeader ;

/* Variables and functions */
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ts_http_header_create (char const*,size_t,char const*,size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
http_response_state_add_header(HttpResponseState *state, const char *name, size_t name_len,
							   const char *value, size_t value_len)
{
	MemoryContext old = MemoryContextSwitchTo(state->context);
	HttpHeader *new_header =
		ts_http_header_create(name, name_len, value, value_len, state->headers);

	state->headers = new_header;
	MemoryContextSwitchTo(old);
}