#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zfs_handle_t ;
struct TYPE_4__ {scalar_t__ cb_first; int /*<<< orphan*/  cb_scripted; } ;
typedef  TYPE_1__ list_cbdata_t ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 int /*<<< orphan*/  print_dataset (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  print_header (TYPE_1__*) ; 

__attribute__((used)) static int
list_callback(zfs_handle_t *zhp, void *data)
{
	list_cbdata_t *cbp = data;

	if (cbp->cb_first) {
		if (!cbp->cb_scripted)
			print_header(cbp);
		cbp->cb_first = B_FALSE;
	}

	print_dataset(zhp, cbp);

	return (0);
}