#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* zc_value; scalar_t__ zc_nvlist_src; scalar_t__ zc_nvlist_conf; char* zc_string; int /*<<< orphan*/  zc_nvlist_dst_size; int /*<<< orphan*/  zc_action_handle; int /*<<< orphan*/  zc_obj; int /*<<< orphan*/  zc_cookie; int /*<<< orphan*/  zc_cleanup_fd; int /*<<< orphan*/  zc_guid; int /*<<< orphan*/  zc_begin_record; int /*<<< orphan*/  zc_iflags; int /*<<< orphan*/  zc_nvlist_conf_size; int /*<<< orphan*/  zc_nvlist_src_size; } ;
typedef  TYPE_2__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  tofs ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_7__ {int /*<<< orphan*/  drr_begin; } ;
struct TYPE_9__ {TYPE_1__ drr_u; scalar_t__ drr_payloadlen; int /*<<< orphan*/  drr_type; } ;
typedef  TYPE_3__ dmu_replay_record_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  DRR_BEGIN ; 
 int /*<<< orphan*/  EINVAL ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 scalar_t__ dataset_namecheck (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int get_nvlist (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_smush (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ put_nvlist (TYPE_2__*,int /*<<< orphan*/ *) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int zfs_ioc_recv_impl (char*,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int
zfs_ioc_recv(zfs_cmd_t *zc)
{
	dmu_replay_record_t begin_record;
	nvlist_t *errors = NULL;
	nvlist_t *recvdprops = NULL;
	nvlist_t *localprops = NULL;
	char *origin = NULL;
	char *tosnap;
	char tofs[ZFS_MAX_DATASET_NAME_LEN];
	int error = 0;

	if (dataset_namecheck(zc->zc_value, NULL, NULL) != 0 ||
	    strchr(zc->zc_value, '@') == NULL ||
	    strchr(zc->zc_value, '%'))
		return (SET_ERROR(EINVAL));

	(void) strlcpy(tofs, zc->zc_value, sizeof (tofs));
	tosnap = strchr(tofs, '@');
	*tosnap++ = '\0';

	if (zc->zc_nvlist_src != 0 &&
	    (error = get_nvlist(zc->zc_nvlist_src, zc->zc_nvlist_src_size,
	    zc->zc_iflags, &recvdprops)) != 0)
		return (error);

	if (zc->zc_nvlist_conf != 0 &&
	    (error = get_nvlist(zc->zc_nvlist_conf, zc->zc_nvlist_conf_size,
	    zc->zc_iflags, &localprops)) != 0)
		return (error);

	if (zc->zc_string[0])
		origin = zc->zc_string;

	begin_record.drr_type = DRR_BEGIN;
	begin_record.drr_payloadlen = 0;
	begin_record.drr_u.drr_begin = zc->zc_begin_record;

	error = zfs_ioc_recv_impl(tofs, tosnap, origin, recvdprops, localprops,
	    NULL, zc->zc_guid, B_FALSE, zc->zc_cookie, &begin_record,
	    zc->zc_cleanup_fd, &zc->zc_cookie, &zc->zc_obj,
	    &zc->zc_action_handle, &errors);
	nvlist_free(recvdprops);
	nvlist_free(localprops);

	/*
	 * Now that all props, initial and delayed, are set, report the prop
	 * errors to the caller.
	 */
	if (zc->zc_nvlist_dst_size != 0 && errors != NULL &&
	    (nvlist_smush(errors, zc->zc_nvlist_dst_size) != 0 ||
	    put_nvlist(zc, errors) != 0)) {
		/*
		 * Caller made zc->zc_nvlist_dst less than the minimum expected
		 * size or supplied an invalid address.
		 */
		error = SET_ERROR(EINVAL);
	}

	nvlist_free(errors);

	return (error);
}