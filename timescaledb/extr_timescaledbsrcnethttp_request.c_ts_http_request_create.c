#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  context; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  HttpRequestMethod ;
typedef  TYPE_1__ HttpRequest ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_DEFAULT_SIZES ; 
 int /*<<< orphan*/  AllocSetContextCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 TYPE_1__* palloc0 (int) ; 
 int /*<<< orphan*/  ts_http_request_init (TYPE_1__*,int /*<<< orphan*/ ) ; 

HttpRequest *
ts_http_request_create(HttpRequestMethod method)
{
	MemoryContext request_context =
		AllocSetContextCreate(CurrentMemoryContext, "Http Request", ALLOCSET_DEFAULT_SIZES);
	MemoryContext old = MemoryContextSwitchTo(request_context);
	HttpRequest *req = palloc0(sizeof(HttpRequest));

	req->context = request_context;
	ts_http_request_init(req, method);

	MemoryContextSwitchTo(old);
	return req;
}