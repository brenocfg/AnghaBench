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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int MAXPATHLEN ; 
 int /*<<< orphan*/  ZPOOL_ERR_DATASET ; 
 int /*<<< orphan*/  ZPOOL_ERR_OBJECT ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ nvpair_value_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* safe_malloc (size_t) ; 
 int /*<<< orphan*/  verify (int) ; 
 scalar_t__ zpool_get_errlog (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  zpool_obj_to_path (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t) ; 

__attribute__((used)) static void
print_error_log(zpool_handle_t *zhp)
{
	nvlist_t *nverrlist = NULL;
	nvpair_t *elem;
	char *pathname;
	size_t len = MAXPATHLEN * 2;

	if (zpool_get_errlog(zhp, &nverrlist) != 0)
		return;

	(void) printf("errors: Permanent errors have been "
	    "detected in the following files:\n\n");

	pathname = safe_malloc(len);
	elem = NULL;
	while ((elem = nvlist_next_nvpair(nverrlist, elem)) != NULL) {
		nvlist_t *nv;
		uint64_t dsobj, obj;

		verify(nvpair_value_nvlist(elem, &nv) == 0);
		verify(nvlist_lookup_uint64(nv, ZPOOL_ERR_DATASET,
		    &dsobj) == 0);
		verify(nvlist_lookup_uint64(nv, ZPOOL_ERR_OBJECT,
		    &obj) == 0);
		zpool_obj_to_path(zhp, dsobj, obj, pathname, len);
		(void) printf("%7s %s\n", "", pathname);
	}
	free(pathname);
	nvlist_free(nverrlist);
}