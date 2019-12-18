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
struct TYPE_3__ {char* body; size_t body_len; int /*<<< orphan*/  context; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_1__ HttpRequest ;

/* Variables and functions */
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 char* palloc (size_t) ; 

void
ts_http_request_set_body(HttpRequest *req, const char *body, size_t body_len)
{
	MemoryContext old = MemoryContextSwitchTo(req->context);

	req->body = palloc(body_len + 1);
	memcpy(req->body, body, body_len);
	req->body[body_len] = '\0';
	req->body_len = body_len;
	MemoryContextSwitchTo(old);
}