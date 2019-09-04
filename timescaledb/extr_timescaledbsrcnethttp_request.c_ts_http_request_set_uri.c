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
struct TYPE_3__ {char* uri; int uri_len; int /*<<< orphan*/  context; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_1__ HttpRequest ;

/* Variables and functions */
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 char* palloc (int) ; 
 int strlen (char const*) ; 

void
ts_http_request_set_uri(HttpRequest *req, const char *uri)
{
	MemoryContext old = MemoryContextSwitchTo(req->context);
	int uri_len = strlen(uri);

	req->uri = palloc(uri_len + 1);
	memcpy(req->uri, uri, uri_len);
	req->uri[uri_len] = '\0';
	req->uri_len = uri_len;
	MemoryContextSwitchTo(old);
}