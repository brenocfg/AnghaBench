#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zpool_handle_t ;
struct TYPE_2__ {int cb_namewidth; int /*<<< orphan*/  cb_verbose; int /*<<< orphan*/  cb_name_flags; } ;
typedef  TYPE_1__ iostat_cbdata_t ;

/* Variables and functions */
 int get_columns () ; 
 int get_namewidth (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
get_namewidth_iostat(zpool_handle_t *zhp, void *data)
{
	iostat_cbdata_t *cb = data;
	int width, columns;

	width = get_namewidth(zhp, cb->cb_namewidth, cb->cb_name_flags,
	    cb->cb_verbose);
	columns = get_columns();

	if (width < 10)
		width = 10;
	if (width > columns - 42)
		width = columns - 42;

	cb->cb_namewidth = width;

	return (0);
}