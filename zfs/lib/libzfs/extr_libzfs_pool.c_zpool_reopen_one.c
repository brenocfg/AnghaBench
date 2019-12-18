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
typedef  int /*<<< orphan*/  zpool_handle_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  dgettext (int /*<<< orphan*/ ,char*) ; 
 int lzc_reopen (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zpool_get_handle (int /*<<< orphan*/ *) ; 
 char* zpool_get_name (int /*<<< orphan*/ *) ; 
 int zpool_standard_error_fmt (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char const*) ; 

int
zpool_reopen_one(zpool_handle_t *zhp, void *data)
{
	libzfs_handle_t *hdl = zpool_get_handle(zhp);
	const char *pool_name = zpool_get_name(zhp);
	boolean_t *scrub_restart = data;
	int error;

	error = lzc_reopen(pool_name, *scrub_restart);
	if (error) {
		return (zpool_standard_error_fmt(hdl, error,
		    dgettext(TEXT_DOMAIN, "cannot reopen '%s'"), pool_name));
	}

	return (0);
}