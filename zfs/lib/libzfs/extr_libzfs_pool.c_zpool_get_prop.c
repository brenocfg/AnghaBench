#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zprop_source_t ;
typedef  int zpool_prop_t ;
struct TYPE_9__ {int /*<<< orphan*/ * zpool_props; } ;
typedef  TYPE_1__ zpool_handle_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 scalar_t__ POOL_STATE_UNAVAIL ; 
#define  PROP_TYPE_INDEX 148 
#define  PROP_TYPE_NUMBER 147 
#define  PROP_TYPE_STRING 146 
 int SPA_VERSION_FEATURES ; 
 int UINT64_MAX ; 
#define  ZPOOL_PROP_ALLOCATED 145 
#define  ZPOOL_PROP_ALTROOT 144 
#define  ZPOOL_PROP_ASHIFT 143 
#define  ZPOOL_PROP_CACHEFILE 142 
#define  ZPOOL_PROP_CAPACITY 141 
#define  ZPOOL_PROP_CHECKPOINT 140 
#define  ZPOOL_PROP_COMMENT 139 
#define  ZPOOL_PROP_DEDUPRATIO 138 
#define  ZPOOL_PROP_EXPANDSZ 137 
#define  ZPOOL_PROP_FRAGMENTATION 136 
#define  ZPOOL_PROP_FREE 135 
#define  ZPOOL_PROP_FREEING 134 
#define  ZPOOL_PROP_GUID 133 
#define  ZPOOL_PROP_HEALTH 132 
#define  ZPOOL_PROP_LEAKED 131 
#define  ZPOOL_PROP_NAME 130 
#define  ZPOOL_PROP_SIZE 129 
#define  ZPOOL_PROP_VERSION 128 
 int /*<<< orphan*/  ZPROP_SRC_NONE ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,...) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  zfs_nicebytes (int,char*,size_t) ; 
 int /*<<< orphan*/  zfs_nicenum (int,char*,size_t) ; 
 scalar_t__ zpool_get_all_props (TYPE_1__*) ; 
 char const* zpool_get_name (TYPE_1__*) ; 
 int zpool_get_prop_int (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 char const* zpool_get_prop_string (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ zpool_get_state (TYPE_1__*) ; 
 char const* zpool_get_state_str (TYPE_1__*) ; 
 int zpool_prop_get_type (int) ; 
 int /*<<< orphan*/  zpool_prop_index_to_string (int,int,char const**) ; 

int
zpool_get_prop(zpool_handle_t *zhp, zpool_prop_t prop, char *buf,
    size_t len, zprop_source_t *srctype, boolean_t literal)
{
	uint64_t intval;
	const char *strval;
	zprop_source_t src = ZPROP_SRC_NONE;

	if (zpool_get_state(zhp) == POOL_STATE_UNAVAIL) {
		switch (prop) {
		case ZPOOL_PROP_NAME:
			(void) strlcpy(buf, zpool_get_name(zhp), len);
			break;

		case ZPOOL_PROP_HEALTH:
			(void) strlcpy(buf, zpool_get_state_str(zhp), len);
			break;

		case ZPOOL_PROP_GUID:
			intval = zpool_get_prop_int(zhp, prop, &src);
			(void) snprintf(buf, len, "%llu", (u_longlong_t)intval);
			break;

		case ZPOOL_PROP_ALTROOT:
		case ZPOOL_PROP_CACHEFILE:
		case ZPOOL_PROP_COMMENT:
			if (zhp->zpool_props != NULL ||
			    zpool_get_all_props(zhp) == 0) {
				(void) strlcpy(buf,
				    zpool_get_prop_string(zhp, prop, &src),
				    len);
				break;
			}
			/* FALLTHROUGH */
		default:
			(void) strlcpy(buf, "-", len);
			break;
		}

		if (srctype != NULL)
			*srctype = src;
		return (0);
	}

	if (zhp->zpool_props == NULL && zpool_get_all_props(zhp) &&
	    prop != ZPOOL_PROP_NAME)
		return (-1);

	switch (zpool_prop_get_type(prop)) {
	case PROP_TYPE_STRING:
		(void) strlcpy(buf, zpool_get_prop_string(zhp, prop, &src),
		    len);
		break;

	case PROP_TYPE_NUMBER:
		intval = zpool_get_prop_int(zhp, prop, &src);

		switch (prop) {
		case ZPOOL_PROP_SIZE:
		case ZPOOL_PROP_ALLOCATED:
		case ZPOOL_PROP_FREE:
		case ZPOOL_PROP_FREEING:
		case ZPOOL_PROP_LEAKED:
		case ZPOOL_PROP_ASHIFT:
			if (literal)
				(void) snprintf(buf, len, "%llu",
				    (u_longlong_t)intval);
			else
				(void) zfs_nicenum(intval, buf, len);
			break;

		case ZPOOL_PROP_EXPANDSZ:
		case ZPOOL_PROP_CHECKPOINT:
			if (intval == 0) {
				(void) strlcpy(buf, "-", len);
			} else if (literal) {
				(void) snprintf(buf, len, "%llu",
				    (u_longlong_t)intval);
			} else {
				(void) zfs_nicebytes(intval, buf, len);
			}
			break;

		case ZPOOL_PROP_CAPACITY:
			if (literal) {
				(void) snprintf(buf, len, "%llu",
				    (u_longlong_t)intval);
			} else {
				(void) snprintf(buf, len, "%llu%%",
				    (u_longlong_t)intval);
			}
			break;

		case ZPOOL_PROP_FRAGMENTATION:
			if (intval == UINT64_MAX) {
				(void) strlcpy(buf, "-", len);
			} else if (literal) {
				(void) snprintf(buf, len, "%llu",
				    (u_longlong_t)intval);
			} else {
				(void) snprintf(buf, len, "%llu%%",
				    (u_longlong_t)intval);
			}
			break;

		case ZPOOL_PROP_DEDUPRATIO:
			if (literal)
				(void) snprintf(buf, len, "%llu.%02llu",
				    (u_longlong_t)(intval / 100),
				    (u_longlong_t)(intval % 100));
			else
				(void) snprintf(buf, len, "%llu.%02llux",
				    (u_longlong_t)(intval / 100),
				    (u_longlong_t)(intval % 100));
			break;

		case ZPOOL_PROP_HEALTH:
			(void) strlcpy(buf, zpool_get_state_str(zhp), len);
			break;
		case ZPOOL_PROP_VERSION:
			if (intval >= SPA_VERSION_FEATURES) {
				(void) snprintf(buf, len, "-");
				break;
			}
			/* FALLTHROUGH */
		default:
			(void) snprintf(buf, len, "%llu", (u_longlong_t)intval);
		}
		break;

	case PROP_TYPE_INDEX:
		intval = zpool_get_prop_int(zhp, prop, &src);
		if (zpool_prop_index_to_string(prop, intval, &strval)
		    != 0)
			return (-1);
		(void) strlcpy(buf, strval, len);
		break;

	default:
		abort();
	}

	if (srctype)
		*srctype = src;

	return (0);
}