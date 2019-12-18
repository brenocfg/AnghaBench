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
struct TYPE_6__ {int /*<<< orphan*/  zpool_name; int /*<<< orphan*/ * zpool_hdl; } ;
typedef  TYPE_1__ zpool_handle_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  EZFS_INVALIDNAME ; 
 int /*<<< orphan*/  EZFS_NOENT ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  dgettext (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 TYPE_1__* zfs_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_error_fmt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  zpool_close (TYPE_1__*) ; 
 int /*<<< orphan*/  zpool_name_valid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ zpool_refresh_stats (TYPE_1__*,scalar_t__*) ; 

zpool_handle_t *
zpool_open_canfail(libzfs_handle_t *hdl, const char *pool)
{
	zpool_handle_t *zhp;
	boolean_t missing;

	/*
	 * Make sure the pool name is valid.
	 */
	if (!zpool_name_valid(hdl, B_TRUE, pool)) {
		(void) zfs_error_fmt(hdl, EZFS_INVALIDNAME,
		    dgettext(TEXT_DOMAIN, "cannot open '%s'"),
		    pool);
		return (NULL);
	}

	if ((zhp = zfs_alloc(hdl, sizeof (zpool_handle_t))) == NULL)
		return (NULL);

	zhp->zpool_hdl = hdl;
	(void) strlcpy(zhp->zpool_name, pool, sizeof (zhp->zpool_name));

	if (zpool_refresh_stats(zhp, &missing) != 0) {
		zpool_close(zhp);
		return (NULL);
	}

	if (missing) {
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN, "no such pool"));
		(void) zfs_error_fmt(hdl, EZFS_NOENT,
		    dgettext(TEXT_DOMAIN, "cannot open '%s'"), pool);
		zpool_close(zhp);
		return (NULL);
	}

	return (zhp);
}