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
typedef  size_t uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  NV_ENCODE_NATIVE ; 
 scalar_t__ nvlist_pack (int /*<<< orphan*/ *,char**,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_size (int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verify (int) ; 
 char* zfs_alloc (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int
zcmd_write_nvlist_com(libzfs_handle_t *hdl, uint64_t *outnv, uint64_t *outlen,
    nvlist_t *nvl)
{
	char *packed;
	size_t len;

	verify(nvlist_size(nvl, &len, NV_ENCODE_NATIVE) == 0);

	if ((packed = zfs_alloc(hdl, len)) == NULL)
		return (-1);

	verify(nvlist_pack(nvl, &packed, &len, NV_ENCODE_NATIVE, 0) == 0);

	*outnv = (uint64_t)(uintptr_t)packed;
	*outlen = len;

	return (0);
}