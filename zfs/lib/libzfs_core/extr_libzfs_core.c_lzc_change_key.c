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
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZFS_IOC_CHANGE_KEY ; 
 char* ZPOOL_HIDDEN_ARGS ; 
 int /*<<< orphan*/  fnvlist_add_nvlist (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fnvlist_add_uint64 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnvlist_add_uint8_array (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int lzc_ioctl (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 

int
lzc_change_key(const char *fsname, uint64_t crypt_cmd, nvlist_t *props,
    uint8_t *wkeydata, uint_t wkeylen)
{
	int error;
	nvlist_t *ioc_args = fnvlist_alloc();
	nvlist_t *hidden_args = NULL;

	fnvlist_add_uint64(ioc_args, "crypt_cmd", crypt_cmd);

	if (wkeydata != NULL) {
		hidden_args = fnvlist_alloc();
		fnvlist_add_uint8_array(hidden_args, "wkeydata", wkeydata,
		    wkeylen);
		fnvlist_add_nvlist(ioc_args, ZPOOL_HIDDEN_ARGS, hidden_args);
	}

	if (props != NULL)
		fnvlist_add_nvlist(ioc_args, "props", props);

	error = lzc_ioctl(ZFS_IOC_CHANGE_KEY, fsname, ioc_args, NULL);
	nvlist_free(hidden_args);
	nvlist_free(ioc_args);

	return (error);
}