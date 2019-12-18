#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {char* dds_origin; } ;
struct TYPE_11__ {TYPE_1__ zfs_dmustats; } ;
typedef  TYPE_2__ zfs_handle_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  int /*<<< orphan*/  keylocation ;
typedef  int boolean_t ;
typedef  int /*<<< orphan*/  avl_tree_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  DCP_CMD_FORCE_INHERIT ; 
 int /*<<< orphan*/  DCP_CMD_FORCE_NEW_KEY ; 
 int ENOENT ; 
 int MAXNAMELEN ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int /*<<< orphan*/  ZFS_PROP_ENCRYPTION ; 
 int /*<<< orphan*/  ZFS_PROP_KEYLOCATION ; 
 int /*<<< orphan*/  ZFS_TYPE_DATASET ; 
 scalar_t__ ZIO_CRYPT_OFF ; 
 int guid_to_name (int /*<<< orphan*/ *,char const*,scalar_t__,int /*<<< orphan*/ ,char*) ; 
 int lzc_change_key (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nvlist_exists (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ nvlist_lookup_nvlist (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ nvpair_value_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ nvpair_value_uint64 (int /*<<< orphan*/ *,scalar_t__*) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  zfs_close (TYPE_2__*) ; 
 int /*<<< orphan*/  zfs_crypto_get_encryption_root (TYPE_2__*,int*,int /*<<< orphan*/ *) ; 
 TYPE_2__* zfs_open (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int zfs_prop_get (TYPE_2__*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_prop_get_int (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int zfs_prop_set (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfs_prop_to_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_refresh_properties (TYPE_2__*) ; 

__attribute__((used)) static int
recv_fix_encryption_hierarchy(libzfs_handle_t *hdl, const char *top_zfs,
    nvlist_t *stream_nv, avl_tree_t *stream_avl)
{
	int err;
	nvpair_t *fselem = NULL;
	nvlist_t *stream_fss;

	VERIFY(0 == nvlist_lookup_nvlist(stream_nv, "fss", &stream_fss));

	while ((fselem = nvlist_next_nvpair(stream_fss, fselem)) != NULL) {
		zfs_handle_t *zhp = NULL;
		uint64_t crypt;
		nvlist_t *snaps, *props, *stream_nvfs = NULL;
		nvpair_t *snapel = NULL;
		boolean_t is_encroot, is_clone, stream_encroot;
		char *cp;
		char *stream_keylocation = NULL;
		char keylocation[MAXNAMELEN];
		char fsname[ZFS_MAX_DATASET_NAME_LEN];

		keylocation[0] = '\0';
		VERIFY(0 == nvpair_value_nvlist(fselem, &stream_nvfs));
		VERIFY(0 == nvlist_lookup_nvlist(stream_nvfs, "snaps", &snaps));
		VERIFY(0 == nvlist_lookup_nvlist(stream_nvfs, "props", &props));
		stream_encroot = nvlist_exists(stream_nvfs, "is_encroot");

		/* find a snapshot from the stream that exists locally */
		err = ENOENT;
		while ((snapel = nvlist_next_nvpair(snaps, snapel)) != NULL) {
			uint64_t guid;

			VERIFY(0 == nvpair_value_uint64(snapel, &guid));
			err = guid_to_name(hdl, top_zfs, guid, B_FALSE,
			    fsname);
			if (err == 0)
				break;
		}

		if (err != 0)
			continue;

		cp = strchr(fsname, '@');
		if (cp != NULL)
			*cp = '\0';

		zhp = zfs_open(hdl, fsname, ZFS_TYPE_DATASET);
		if (zhp == NULL) {
			err = ENOENT;
			goto error;
		}

		crypt = zfs_prop_get_int(zhp, ZFS_PROP_ENCRYPTION);
		is_clone = zhp->zfs_dmustats.dds_origin[0] != '\0';
		(void) zfs_crypto_get_encryption_root(zhp, &is_encroot, NULL);

		/* we don't need to do anything for unencrypted datasets */
		if (crypt == ZIO_CRYPT_OFF) {
			zfs_close(zhp);
			continue;
		}

		/*
		 * If the dataset is flagged as an encryption root, was not
		 * received as a clone and is not currently an encryption root,
		 * force it to become one. Fixup the keylocation if necessary.
		 */
		if (stream_encroot) {
			if (!is_clone && !is_encroot) {
				err = lzc_change_key(fsname,
				    DCP_CMD_FORCE_NEW_KEY, NULL, NULL, 0);
				if (err != 0) {
					zfs_close(zhp);
					goto error;
				}
			}

			VERIFY(0 == nvlist_lookup_string(props,
			    zfs_prop_to_name(ZFS_PROP_KEYLOCATION),
			    &stream_keylocation));

			/*
			 * Refresh the properties in case the call to
			 * lzc_change_key() changed the value.
			 */
			zfs_refresh_properties(zhp);
			err = zfs_prop_get(zhp, ZFS_PROP_KEYLOCATION,
			    keylocation, sizeof (keylocation), NULL, NULL,
			    0, B_TRUE);
			if (err != 0) {
				zfs_close(zhp);
				goto error;
			}

			if (strcmp(keylocation, stream_keylocation) != 0) {
				err = zfs_prop_set(zhp,
				    zfs_prop_to_name(ZFS_PROP_KEYLOCATION),
				    stream_keylocation);
				if (err != 0) {
					zfs_close(zhp);
					goto error;
				}
			}
		}

		/*
		 * If the dataset is not flagged as an encryption root and is
		 * currently an encryption root, force it to inherit from its
		 * parent. The root of a raw send should never be
		 * force-inherited.
		 */
		if (!stream_encroot && is_encroot &&
		    strcmp(top_zfs, fsname) != 0) {
			err = lzc_change_key(fsname, DCP_CMD_FORCE_INHERIT,
			    NULL, NULL, 0);
			if (err != 0) {
				zfs_close(zhp);
				goto error;
			}
		}

		zfs_close(zhp);
	}

	return (0);

error:
	return (err);
}