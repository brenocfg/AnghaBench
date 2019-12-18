#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_9__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ zc_version; scalar_t__ zc_has_remove_timer; } ;
struct TYPE_10__ {int /*<<< orphan*/  zc_node; int /*<<< orphan*/  zc_remove_timer; TYPE_9__ zc_data; int /*<<< orphan*/ * zc_case; } ;
typedef  TYPE_1__ zfs_case_t ;
typedef  int /*<<< orphan*/  fmd_hdl_t ;
typedef  int /*<<< orphan*/  fmd_case_t ;

/* Variables and functions */
 int /*<<< orphan*/  CASE_DATA ; 
 scalar_t__ CASE_DATA_VERSION_SERD ; 
 int /*<<< orphan*/  FMD_SLEEP ; 
 int /*<<< orphan*/  fmd_buf_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_9__*,int) ; 
 int /*<<< orphan*/  fmd_case_setspecific (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  fmd_hdl_free (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 TYPE_1__* fmd_hdl_zalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmd_timer_install (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uu_list_insert_before (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  uu_list_node_init (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_case_pool ; 
 int /*<<< orphan*/  zfs_cases ; 
 int /*<<< orphan*/  zfs_remove_timeout ; 

__attribute__((used)) static zfs_case_t *
zfs_case_unserialize(fmd_hdl_t *hdl, fmd_case_t *cp)
{
	zfs_case_t *zcp;

	zcp = fmd_hdl_zalloc(hdl, sizeof (zfs_case_t), FMD_SLEEP);
	zcp->zc_case = cp;

	fmd_buf_read(hdl, cp, CASE_DATA, &zcp->zc_data,
	    sizeof (zcp->zc_data));

	if (zcp->zc_data.zc_version > CASE_DATA_VERSION_SERD) {
		fmd_hdl_free(hdl, zcp, sizeof (zfs_case_t));
		return (NULL);
	}

	/*
	 * fmd_buf_read() will have already zeroed out the remainder of the
	 * buffer, so we don't have to do anything special if the version
	 * doesn't include the SERD engine name.
	 */

	if (zcp->zc_data.zc_has_remove_timer)
		zcp->zc_remove_timer = fmd_timer_install(hdl, zcp,
		    NULL, zfs_remove_timeout);

	uu_list_node_init(zcp, &zcp->zc_node, zfs_case_pool);
	(void) uu_list_insert_before(zfs_cases, NULL, zcp);

	fmd_case_setspecific(hdl, cp, zcp);

	return (zcp);
}