#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* zc_serd_checksum; char* zc_serd_io; scalar_t__ zc_has_remove_timer; } ;
struct TYPE_8__ {int /*<<< orphan*/  zc_node; int /*<<< orphan*/  zc_remove_timer; TYPE_1__ zc_data; } ;
typedef  TYPE_2__ zfs_case_t ;
typedef  int /*<<< orphan*/  fmd_hdl_t ;
typedef  int /*<<< orphan*/  fmd_case_t ;

/* Variables and functions */
 TYPE_2__* fmd_case_getspecific (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fmd_hdl_free (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  fmd_serd_destroy (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fmd_timer_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uu_list_node_fini (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uu_list_remove (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  zfs_case_pool ; 
 int /*<<< orphan*/  zfs_cases ; 

__attribute__((used)) static void
zfs_fm_close(fmd_hdl_t *hdl, fmd_case_t *cs)
{
	zfs_case_t *zcp = fmd_case_getspecific(hdl, cs);

	if (zcp->zc_data.zc_serd_checksum[0] != '\0')
		fmd_serd_destroy(hdl, zcp->zc_data.zc_serd_checksum);
	if (zcp->zc_data.zc_serd_io[0] != '\0')
		fmd_serd_destroy(hdl, zcp->zc_data.zc_serd_io);
	if (zcp->zc_data.zc_has_remove_timer)
		fmd_timer_remove(hdl, zcp->zc_remove_timer);

	uu_list_remove(zfs_cases, zcp);
	uu_list_node_fini(zcp, &zcp->zc_node, zfs_case_pool);
	fmd_hdl_free(hdl, zcp, sizeof (zfs_case_t));
}