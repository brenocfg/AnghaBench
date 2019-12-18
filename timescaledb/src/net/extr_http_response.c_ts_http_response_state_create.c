#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  context; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_1__ HttpResponseState ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_DEFAULT_SIZES ; 
 int /*<<< orphan*/  AllocSetContextCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* palloc (int) ; 
 int /*<<< orphan*/  ts_http_response_state_init (TYPE_1__*) ; 

HttpResponseState *
ts_http_response_state_create()
{
	MemoryContext context =
		AllocSetContextCreate(CurrentMemoryContext, "Http Response", ALLOCSET_DEFAULT_SIZES);
	MemoryContext old = MemoryContextSwitchTo(context);
	HttpResponseState *ret = palloc(sizeof(HttpResponseState));

	memset(ret, 0, sizeof(*ret));

	ret->context = context;
	ts_http_response_state_init(ret);
	MemoryContextSwitchTo(old);
	return ret;
}