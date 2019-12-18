#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int pos; } ;
typedef  TYPE_1__ zpl_dir_context_t ;
struct TYPE_16__ {int z_id; scalar_t__ z_zn_prefetch; scalar_t__ z_unlinked; int /*<<< orphan*/  z_sa_hdl; } ;
typedef  TYPE_2__ znode_t ;
struct TYPE_17__ {int /*<<< orphan*/ * z_os; } ;
typedef  TYPE_3__ zfsvfs_t ;
typedef  int /*<<< orphan*/  zap_cursor_t ;
struct TYPE_18__ {int za_integer_length; scalar_t__ za_num_integers; int /*<<< orphan*/  za_name; int /*<<< orphan*/  za_first_integer; scalar_t__ za_normalization_conflict; } ;
typedef  TYPE_4__ zap_attribute_t ;
typedef  scalar_t__ uint8_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  parent ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  cred_t ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 int /*<<< orphan*/  CE_WARN ; 
 scalar_t__ DT_DIR ; 
 int ENOENT ; 
 int /*<<< orphan*/  ENXIO ; 
 TYPE_2__* ITOZ (struct inode*) ; 
 TYPE_3__* ITOZSB (struct inode*) ; 
 int /*<<< orphan*/  SA_ZPL_PARENT (TYPE_3__*) ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int ZFSCTL_INO_ROOT ; 
 char* ZFS_CTLDIR_NAME ; 
 int ZFS_DIRENT_OBJ (int /*<<< orphan*/ ) ; 
 scalar_t__ ZFS_DIRENT_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZFS_ENTER (TYPE_3__*) ; 
 int /*<<< orphan*/  ZFS_EXIT (TYPE_3__*) ; 
 int /*<<< orphan*/  ZFS_VERIFY_ZP (TYPE_2__*) ; 
 int /*<<< orphan*/  ZIO_PRIORITY_SYNC_READ ; 
 int /*<<< orphan*/  cmn_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_prefetch (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sa_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zap_cursor_advance (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zap_cursor_init_serialized (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int zap_cursor_retrieve (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int zap_cursor_serialize (int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_show_ctldir (TYPE_2__*) ; 
 int /*<<< orphan*/  zpl_dir_emit (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__) ; 

int
zfs_readdir(struct inode *ip, zpl_dir_context_t *ctx, cred_t *cr)
{
	znode_t		*zp = ITOZ(ip);
	zfsvfs_t	*zfsvfs = ITOZSB(ip);
	objset_t	*os;
	zap_cursor_t	zc;
	zap_attribute_t	zap;
	int		error;
	uint8_t		prefetch;
	uint8_t		type;
	int		done = 0;
	uint64_t	parent;
	uint64_t	offset; /* must be unsigned; checks for < 1 */

	ZFS_ENTER(zfsvfs);
	ZFS_VERIFY_ZP(zp);

	if ((error = sa_lookup(zp->z_sa_hdl, SA_ZPL_PARENT(zfsvfs),
	    &parent, sizeof (parent))) != 0)
		goto out;

	/*
	 * Quit if directory has been removed (posix)
	 */
	if (zp->z_unlinked)
		goto out;

	error = 0;
	os = zfsvfs->z_os;
	offset = ctx->pos;
	prefetch = zp->z_zn_prefetch;

	/*
	 * Initialize the iterator cursor.
	 */
	if (offset <= 3) {
		/*
		 * Start iteration from the beginning of the directory.
		 */
		zap_cursor_init(&zc, os, zp->z_id);
	} else {
		/*
		 * The offset is a serialized cursor.
		 */
		zap_cursor_init_serialized(&zc, os, zp->z_id, offset);
	}

	/*
	 * Transform to file-system independent format
	 */
	while (!done) {
		uint64_t objnum;
		/*
		 * Special case `.', `..', and `.zfs'.
		 */
		if (offset == 0) {
			(void) strcpy(zap.za_name, ".");
			zap.za_normalization_conflict = 0;
			objnum = zp->z_id;
			type = DT_DIR;
		} else if (offset == 1) {
			(void) strcpy(zap.za_name, "..");
			zap.za_normalization_conflict = 0;
			objnum = parent;
			type = DT_DIR;
		} else if (offset == 2 && zfs_show_ctldir(zp)) {
			(void) strcpy(zap.za_name, ZFS_CTLDIR_NAME);
			zap.za_normalization_conflict = 0;
			objnum = ZFSCTL_INO_ROOT;
			type = DT_DIR;
		} else {
			/*
			 * Grab next entry.
			 */
			if ((error = zap_cursor_retrieve(&zc, &zap))) {
				if (error == ENOENT)
					break;
				else
					goto update;
			}

			/*
			 * Allow multiple entries provided the first entry is
			 * the object id.  Non-zpl consumers may safely make
			 * use of the additional space.
			 *
			 * XXX: This should be a feature flag for compatibility
			 */
			if (zap.za_integer_length != 8 ||
			    zap.za_num_integers == 0) {
				cmn_err(CE_WARN, "zap_readdir: bad directory "
				    "entry, obj = %lld, offset = %lld, "
				    "length = %d, num = %lld\n",
				    (u_longlong_t)zp->z_id,
				    (u_longlong_t)offset,
				    zap.za_integer_length,
				    (u_longlong_t)zap.za_num_integers);
				error = SET_ERROR(ENXIO);
				goto update;
			}

			objnum = ZFS_DIRENT_OBJ(zap.za_first_integer);
			type = ZFS_DIRENT_TYPE(zap.za_first_integer);
		}

		done = !zpl_dir_emit(ctx, zap.za_name, strlen(zap.za_name),
		    objnum, type);
		if (done)
			break;

		/* Prefetch znode */
		if (prefetch) {
			dmu_prefetch(os, objnum, 0, 0, 0,
			    ZIO_PRIORITY_SYNC_READ);
		}

		/*
		 * Move to the next entry, fill in the previous offset.
		 */
		if (offset > 2 || (offset == 2 && !zfs_show_ctldir(zp))) {
			zap_cursor_advance(&zc);
			offset = zap_cursor_serialize(&zc);
		} else {
			offset += 1;
		}
		ctx->pos = offset;
	}
	zp->z_zn_prefetch = B_FALSE; /* a lookup will re-enable pre-fetching */

update:
	zap_cursor_fini(&zc);
	if (error == ENOENT)
		error = 0;
out:
	ZFS_EXIT(zfsvfs);

	return (error);
}