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
typedef  int XactEvent ;

/* Variables and functions */
#define  XACT_EVENT_ABORT 129 
#define  XACT_EVENT_PARALLEL_ABORT 128 
 int expect_chunk_modification ; 

__attribute__((used)) static void
process_utility_xact_abort(XactEvent event, void *arg)
{
	switch (event)
	{
		case XACT_EVENT_ABORT:
		case XACT_EVENT_PARALLEL_ABORT:

			/*
			 * Reset the expect_chunk_modification flag because it this is an
			 * internal safety flag that is set to true only temporarily
			 * during chunk operations. It should never remain true across
			 * transactions.
			 */
			expect_chunk_modification = false;
		default:
			break;
	}
}