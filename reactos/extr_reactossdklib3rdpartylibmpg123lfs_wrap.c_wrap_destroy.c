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
struct wrap_data {struct wrap_data* indextable; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct wrap_data*) ; 
 int /*<<< orphan*/  wrap_io_cleanup (void*) ; 

__attribute__((used)) static void wrap_destroy(void *handle)
{
	struct wrap_data *wh = handle;
	wrap_io_cleanup(handle);
	if(wh->indextable != NULL)
	free(wh->indextable);

	free(wh);
}