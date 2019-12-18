#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  dsm_segment ;
typedef  int /*<<< orphan*/  dsm_handle ;
typedef  int /*<<< orphan*/  TestParamsWrapper ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CommitTransactionCommand () ; 
 int /*<<< orphan*/  ERROR ; 
 int IsTransactionState () ; 
 int /*<<< orphan*/  StartTransactionCommand () ; 
 int /*<<< orphan*/ * dsm_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dsm_find_mapping (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsm_pin_mapping (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dsm_segment_address (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  params_get_dsm_handle () ; 

__attribute__((used)) static TestParamsWrapper *
params_open_wrapper()
{
	dsm_segment *seg;
	dsm_handle handle = params_get_dsm_handle();
	TestParamsWrapper *wrapper;

	seg = dsm_find_mapping(handle);
	if (seg == NULL)
	{
#if PG96
		bool started = IsTransactionState();

		if (!started)
			StartTransactionCommand();
#endif
		seg = dsm_attach(handle);
		if (seg == NULL)
			elog(ERROR, "got NULL segment in params_open_wrapper");
#if PG96
		dsm_pin_mapping(seg);
		if (!started)
			CommitTransactionCommand();
#endif
	}

	Assert(seg != NULL);

	wrapper = dsm_segment_address(seg);

	Assert(wrapper != NULL);

	return wrapper;
}