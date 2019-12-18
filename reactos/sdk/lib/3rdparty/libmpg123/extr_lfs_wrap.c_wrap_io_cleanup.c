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
struct wrap_data {scalar_t__ iotype; int my_fd; int /*<<< orphan*/ * handle; int /*<<< orphan*/  (* h_cleanup ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 scalar_t__ IO_HANDLE ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wrap_io_cleanup(void *handle)
{
	struct wrap_data *ioh = handle;
	if(ioh->iotype == IO_HANDLE)
	{
		if(ioh->h_cleanup != NULL && ioh->handle != NULL)
		ioh->h_cleanup(ioh->handle);

		ioh->handle = NULL;
	}
	if(ioh->my_fd >= 0)
	{
		close(ioh->my_fd);
		ioh->my_fd = -1;
	}
}