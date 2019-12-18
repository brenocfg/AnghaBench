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
typedef  int zfs_keyformat_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  LE_64 (int /*<<< orphan*/ ) ; 
 int PKCS5_PBKDF2_HMAC_SHA1 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int WRAPPING_KEY_LEN ; 
#define  ZFS_KEYFORMAT_HEX 130 
#define  ZFS_KEYFORMAT_PASSPHRASE 129 
#define  ZFS_KEYFORMAT_RAW 128 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dgettext (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int hex_key_to_raw (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/ * zfs_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
derive_key(libzfs_handle_t *hdl, zfs_keyformat_t format, uint64_t iters,
    uint8_t *key_material, size_t key_material_len, uint64_t salt,
    uint8_t **key_out)
{
	int ret;
	uint8_t *key;

	*key_out = NULL;

	key = zfs_alloc(hdl, WRAPPING_KEY_LEN);
	if (!key)
		return (ENOMEM);

	switch (format) {
	case ZFS_KEYFORMAT_RAW:
		bcopy(key_material, key, WRAPPING_KEY_LEN);
		break;
	case ZFS_KEYFORMAT_HEX:
		ret = hex_key_to_raw((char *)key_material,
		    WRAPPING_KEY_LEN * 2, key);
		if (ret != 0) {
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "Invalid hex key provided."));
			goto error;
		}
		break;
	case ZFS_KEYFORMAT_PASSPHRASE:
		salt = LE_64(salt);

		ret = PKCS5_PBKDF2_HMAC_SHA1((char *)key_material,
		    strlen((char *)key_material), ((uint8_t *)&salt),
		    sizeof (uint64_t), iters, WRAPPING_KEY_LEN, key);
		if (ret != 1) {
			ret = EIO;
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "Failed to generate key from passphrase."));
			goto error;
		}
		break;
	default:
		ret = EINVAL;
		goto error;
	}

	*key_out = key;
	return (0);

error:
	free(key);

	*key_out = NULL;
	return (ret);
}