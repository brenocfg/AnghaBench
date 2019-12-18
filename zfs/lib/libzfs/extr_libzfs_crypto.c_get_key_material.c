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
typedef  int zfs_keylocation_t ;
typedef  int zfs_keyformat_t ;
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  scalar_t__ boolean_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 int EINVAL ; 
 size_t MAX_PASSPHRASE_LEN ; 
 size_t MIN_PASSPHRASE_LEN ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 size_t WRAPPING_KEY_LEN ; 
#define  ZFS_KEYFORMAT_HEX 132 
#define  ZFS_KEYFORMAT_PASSPHRASE 131 
#define  ZFS_KEYFORMAT_RAW 130 
 int ZFS_KEYLOCATION_NONE ; 
#define  ZFS_KEYLOCATION_PROMPT 129 
#define  ZFS_KEYLOCATION_URI 128 
 int /*<<< orphan*/  dgettext (int /*<<< orphan*/ ,char*) ; 
 int errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 
 int get_key_material_raw (int /*<<< orphan*/ *,char const*,int,scalar_t__,scalar_t__,scalar_t__**,size_t*) ; 
 scalar_t__ isatty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isxdigit (char) ; 
 scalar_t__ memcmp (char*,char*,size_t) ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int zfs_prop_parse_keylocation (char*) ; 

__attribute__((used)) static int
get_key_material(libzfs_handle_t *hdl, boolean_t do_verify, boolean_t newkey,
    zfs_keyformat_t keyformat, char *keylocation, const char *fsname,
    uint8_t **km_out, size_t *kmlen_out, boolean_t *can_retry_out)
{
	int ret, i;
	zfs_keylocation_t keyloc = ZFS_KEYLOCATION_NONE;
	FILE *fd = NULL;
	uint8_t *km = NULL, *km2 = NULL;
	size_t kmlen, kmlen2;
	boolean_t can_retry = B_FALSE;

	/* verify and parse the keylocation */
	keyloc = zfs_prop_parse_keylocation(keylocation);

	/* open the appropriate file descriptor */
	switch (keyloc) {
	case ZFS_KEYLOCATION_PROMPT:
		fd = stdin;
		if (isatty(fileno(fd))) {
			can_retry = B_TRUE;

			/* raw keys cannot be entered on the terminal */
			if (keyformat == ZFS_KEYFORMAT_RAW) {
				ret = EINVAL;
				zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
				    "Cannot enter raw keys on the terminal"));
				goto error;
			}
		}
		break;
	case ZFS_KEYLOCATION_URI:
		fd = fopen(&keylocation[7], "r");
		if (!fd) {
			ret = errno;
			errno = 0;
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "Failed to open key material file"));
			goto error;
		}
		break;
	default:
		ret = EINVAL;
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
		    "Invalid keylocation."));
		goto error;
	}

	/* fetch the key material into the buffer */
	ret = get_key_material_raw(fd, fsname, keyformat, B_FALSE, newkey,
	    &km, &kmlen);
	if (ret != 0)
		goto error;

	/* do basic validation of the key material */
	switch (keyformat) {
	case ZFS_KEYFORMAT_RAW:
		/* verify the key length is correct */
		if (kmlen < WRAPPING_KEY_LEN) {
			ret = EINVAL;
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "Raw key too short (expected %u)."),
			    WRAPPING_KEY_LEN);
			goto error;
		}

		if (kmlen > WRAPPING_KEY_LEN) {
			ret = EINVAL;
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "Raw key too long (expected %u)."),
			    WRAPPING_KEY_LEN);
			goto error;
		}
		break;
	case ZFS_KEYFORMAT_HEX:
		/* verify the key length is correct */
		if (kmlen < WRAPPING_KEY_LEN * 2) {
			ret = EINVAL;
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "Hex key too short (expected %u)."),
			    WRAPPING_KEY_LEN * 2);
			goto error;
		}

		if (kmlen > WRAPPING_KEY_LEN * 2) {
			ret = EINVAL;
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "Hex key too long (expected %u)."),
			    WRAPPING_KEY_LEN * 2);
			goto error;
		}

		/* check for invalid hex digits */
		for (i = 0; i < WRAPPING_KEY_LEN * 2; i++) {
			if (!isxdigit((char)km[i])) {
				ret = EINVAL;
				zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
				    "Invalid hex character detected."));
				goto error;
			}
		}
		break;
	case ZFS_KEYFORMAT_PASSPHRASE:
		/* verify the length is within bounds */
		if (kmlen > MAX_PASSPHRASE_LEN) {
			ret = EINVAL;
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "Passphrase too long (max %u)."),
			    MAX_PASSPHRASE_LEN);
			goto error;
		}

		if (kmlen < MIN_PASSPHRASE_LEN) {
			ret = EINVAL;
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "Passphrase too short (min %u)."),
			    MIN_PASSPHRASE_LEN);
			goto error;
		}
		break;
	default:
		/* can't happen, checked above */
		break;
	}

	if (do_verify && isatty(fileno(fd))) {
		ret = get_key_material_raw(fd, fsname, keyformat, B_TRUE,
		    newkey, &km2, &kmlen2);
		if (ret != 0)
			goto error;

		if (kmlen2 != kmlen ||
		    (memcmp((char *)km, (char *)km2, kmlen) != 0)) {
			ret = EINVAL;
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "Provided keys do not match."));
			goto error;
		}
	}

	if (fd != stdin)
		fclose(fd);

	if (km2 != NULL)
		free(km2);

	*km_out = km;
	*kmlen_out = kmlen;
	if (can_retry_out != NULL)
		*can_retry_out = can_retry;

	return (0);

error:
	if (km != NULL)
		free(km);

	if (km2 != NULL)
		free(km2);

	if (fd != NULL && fd != stdin)
		fclose(fd);

	*km_out = NULL;
	*kmlen_out = 0;
	if (can_retry_out != NULL)
		*can_retry_out = can_retry;

	return (ret);
}