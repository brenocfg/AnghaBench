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
typedef  TYPE_1__ HttpRequest ;
typedef  int /*<<< orphan*/  HttpHeader ;

/* Variables and functions */
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/ * ts_http_header_create (char const*,int,char const*,int,int /*<<< orphan*/ *) ; 

void
ts_http_request_set_header(HttpRequest *req, const char *name, const char *value)
{
	MemoryContext old = MemoryContextSwitchTo(req->context);
	int name_len = strlen(name);
	int value_len = strlen(value);
	HttpHeader *new_header = ts_http_header_create(name, name_len, value, value_len, req->headers);

	req->headers = new_header;
	MemoryContextSwitchTo(old);
}