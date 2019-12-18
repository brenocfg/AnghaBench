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
typedef  int /*<<< orphan*/  zio_cksum_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  dgettext (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int nvlist_unpack (char*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int recv_read (int /*<<< orphan*/ *,int,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* zfs_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
recv_read_nvlist(libzfs_handle_t *hdl, int fd, int len, nvlist_t **nvp,
    boolean_t byteswap, zio_cksum_t *zc)
{
	char *buf;
	int err;

	buf = zfs_alloc(hdl, len);
	if (buf == NULL)
		return (ENOMEM);

	err = recv_read(hdl, fd, buf, len, byteswap, zc);
	if (err != 0) {
		free(buf);
		return (err);
	}

	err = nvlist_unpack(buf, len, nvp, 0);
	free(buf);
	if (err != 0) {
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN, "invalid "
		    "stream (malformed nvlist)"));
		return (EINVAL);
	}
	return (0);
}