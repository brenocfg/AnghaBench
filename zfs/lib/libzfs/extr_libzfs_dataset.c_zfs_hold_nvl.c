#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * zfs_hdl; } ;
typedef  TYPE_1__ zfs_handle_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  int /*<<< orphan*/  errbuf ;

/* Variables and functions */
#define  E2BIG 131 
#define  EEXIST 130 
#define  EINVAL 129 
#define  ENOTSUP 128 
 int /*<<< orphan*/  EZFS_BADTYPE ; 
 int /*<<< orphan*/  EZFS_BADVERSION ; 
 int /*<<< orphan*/  EZFS_REFTAG_HOLD ; 
 int /*<<< orphan*/  EZFS_TAGTOOLONG ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fnvlist_free (int /*<<< orphan*/ *) ; 
 int fnvpair_value_int32 (int /*<<< orphan*/ *) ; 
 int lzc_hold (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 scalar_t__ nvlist_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvpair_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  zfs_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  zfs_standard_error (int /*<<< orphan*/ *,int,char*) ; 

int
zfs_hold_nvl(zfs_handle_t *zhp, int cleanup_fd, nvlist_t *holds)
{
	int ret;
	nvlist_t *errors;
	libzfs_handle_t *hdl = zhp->zfs_hdl;
	char errbuf[1024];
	nvpair_t *elem;

	errors = NULL;
	ret = lzc_hold(holds, cleanup_fd, &errors);

	if (ret == 0) {
		/* There may be errors even in the success case. */
		fnvlist_free(errors);
		return (0);
	}

	if (nvlist_empty(errors)) {
		/* no hold-specific errors */
		(void) snprintf(errbuf, sizeof (errbuf),
		    dgettext(TEXT_DOMAIN, "cannot hold"));
		switch (ret) {
		case ENOTSUP:
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "pool must be upgraded"));
			(void) zfs_error(hdl, EZFS_BADVERSION, errbuf);
			break;
		case EINVAL:
			(void) zfs_error(hdl, EZFS_BADTYPE, errbuf);
			break;
		default:
			(void) zfs_standard_error(hdl, ret, errbuf);
		}
	}

	for (elem = nvlist_next_nvpair(errors, NULL);
	    elem != NULL;
	    elem = nvlist_next_nvpair(errors, elem)) {
		(void) snprintf(errbuf, sizeof (errbuf),
		    dgettext(TEXT_DOMAIN,
		    "cannot hold snapshot '%s'"), nvpair_name(elem));
		switch (fnvpair_value_int32(elem)) {
		case E2BIG:
			/*
			 * Temporary tags wind up having the ds object id
			 * prepended. So even if we passed the length check
			 * above, it's still possible for the tag to wind
			 * up being slightly too long.
			 */
			(void) zfs_error(hdl, EZFS_TAGTOOLONG, errbuf);
			break;
		case EINVAL:
			(void) zfs_error(hdl, EZFS_BADTYPE, errbuf);
			break;
		case EEXIST:
			(void) zfs_error(hdl, EZFS_REFTAG_HOLD, errbuf);
			break;
		default:
			(void) zfs_standard_error(hdl,
			    fnvpair_value_int32(elem), errbuf);
		}
	}

	fnvlist_free(errors);
	return (ret);
}