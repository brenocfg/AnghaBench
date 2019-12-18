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
typedef  scalar_t__ zfs_keyformat_t ;
typedef  int /*<<< orphan*/  zfs_handle_t ;
typedef  scalar_t__ uint_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 scalar_t__ DEFAULT_PBKDF2_ITERATIONS ; 
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 scalar_t__ WRAPPING_KEY_LEN ; 
 scalar_t__ ZFS_KEYFORMAT_PASSPHRASE ; 
 int /*<<< orphan*/  ZFS_PROP_PBKDF2_ITERS ; 
 int /*<<< orphan*/  ZFS_PROP_PBKDF2_SALT ; 
 int derive_key (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ *,size_t,scalar_t__,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dgettext (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int get_key_material (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,char*,char const*,int /*<<< orphan*/ **,size_t*,int /*<<< orphan*/ *) ; 
 int nvlist_add_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int pkcs11_get_urandom (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* zfs_get_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_prop_to_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
populate_create_encryption_params_nvlists(libzfs_handle_t *hdl,
    zfs_handle_t *zhp, boolean_t newkey, zfs_keyformat_t keyformat,
    char *keylocation, nvlist_t *props, uint8_t **wkeydata, uint_t *wkeylen)
{
	int ret;
	uint64_t iters = 0, salt = 0;
	uint8_t *key_material = NULL;
	size_t key_material_len = 0;
	uint8_t *key_data = NULL;
	const char *fsname = (zhp) ? zfs_get_name(zhp) : NULL;

	/* get key material from keyformat and keylocation */
	ret = get_key_material(hdl, B_TRUE, newkey, keyformat, keylocation,
	    fsname, &key_material, &key_material_len, NULL);
	if (ret != 0)
		goto error;

	/* passphrase formats require a salt and pbkdf2 iters property */
	if (keyformat == ZFS_KEYFORMAT_PASSPHRASE) {
		/* always generate a new salt */
		ret = pkcs11_get_urandom((uint8_t *)&salt, sizeof (uint64_t));
		if (ret != sizeof (uint64_t)) {
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "Failed to generate salt."));
			goto error;
		}

		ret = nvlist_add_uint64(props,
		    zfs_prop_to_name(ZFS_PROP_PBKDF2_SALT), salt);
		if (ret != 0) {
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "Failed to add salt to properties."));
			goto error;
		}

		/*
		 * If not otherwise specified, use the default number of
		 * pbkdf2 iterations. If specified, we have already checked
		 * that the given value is greater than MIN_PBKDF2_ITERATIONS
		 * during zfs_valid_proplist().
		 */
		ret = nvlist_lookup_uint64(props,
		    zfs_prop_to_name(ZFS_PROP_PBKDF2_ITERS), &iters);
		if (ret == ENOENT) {
			iters = DEFAULT_PBKDF2_ITERATIONS;
			ret = nvlist_add_uint64(props,
			    zfs_prop_to_name(ZFS_PROP_PBKDF2_ITERS), iters);
			if (ret != 0)
				goto error;
		} else if (ret != 0) {
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "Failed to get pbkdf2 iterations."));
			goto error;
		}
	} else {
		/* check that pbkdf2iters was not specified by the user */
		ret = nvlist_lookup_uint64(props,
		    zfs_prop_to_name(ZFS_PROP_PBKDF2_ITERS), &iters);
		if (ret == 0) {
			ret = EINVAL;
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "Cannot specify pbkdf2iters with a non-passphrase "
			    "keyformat."));
			goto error;
		}
	}

	/* derive a key from the key material */
	ret = derive_key(hdl, keyformat, iters, key_material, key_material_len,
	    salt, &key_data);
	if (ret != 0)
		goto error;

	free(key_material);

	*wkeydata = key_data;
	*wkeylen = WRAPPING_KEY_LEN;
	return (0);

error:
	if (key_material != NULL)
		free(key_material);
	if (key_data != NULL)
		free(key_data);

	*wkeydata = NULL;
	*wkeylen = 0;
	return (ret);
}