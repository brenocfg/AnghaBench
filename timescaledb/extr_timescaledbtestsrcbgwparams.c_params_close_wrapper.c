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
typedef  int /*<<< orphan*/  TestParamsWrapper ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsm_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dsm_find_mapping (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  params_get_dsm_handle () ; 

__attribute__((used)) static void
params_close_wrapper(TestParamsWrapper *wrapper)
{
	dsm_segment *seg = dsm_find_mapping(params_get_dsm_handle());

	Assert(seg != NULL);
	dsm_detach(seg);
}