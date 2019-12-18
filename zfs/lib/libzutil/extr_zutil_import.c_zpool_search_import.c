#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pool_config_ops_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_8__ {scalar_t__ lpc_open_access_error; int /*<<< orphan*/  lpc_printerr; int /*<<< orphan*/  const* lpc_ops; void* lpc_lib_handle; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ libpc_handle_t ;
struct TYPE_9__ {int /*<<< orphan*/  guid; int /*<<< orphan*/ * poolname; int /*<<< orphan*/ * cachefile; } ;
typedef  TYPE_2__ importargs_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  EZFS_EACESS ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  dgettext (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ geteuid () ; 
 scalar_t__ nvlist_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verify (int) ; 
 int /*<<< orphan*/ * zpool_find_import_cached (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zpool_find_import_impl (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  zutil_error (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

nvlist_t *
zpool_search_import(void *hdl, importargs_t *import,
    const pool_config_ops_t *pco)
{
	libpc_handle_t handle = { 0 };
	nvlist_t *pools = NULL;

	handle.lpc_lib_handle = hdl;
	handle.lpc_ops = pco;
	handle.lpc_printerr = B_TRUE;

	verify(import->poolname == NULL || import->guid == 0);

	if (import->cachefile != NULL)
		pools = zpool_find_import_cached(&handle, import->cachefile,
		    import->poolname, import->guid);
	else
		pools = zpool_find_import_impl(&handle, import);

	if ((pools == NULL || nvlist_empty(pools)) &&
	    handle.lpc_open_access_error && geteuid() != 0) {
		(void) zutil_error(&handle, EZFS_EACESS, dgettext(TEXT_DOMAIN,
		    "no pools found"));
	}

	return (pools);
}