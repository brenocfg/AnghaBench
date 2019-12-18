#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  zk_version; int /*<<< orphan*/  zk_hmac_key; } ;
typedef  TYPE_2__ zio_crypt_key_t ;
typedef  scalar_t__ uint_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_16__ {scalar_t__ dn_type; } ;
struct TYPE_13__ {TYPE_7__ os_projectused_dnode; TYPE_7__ os_groupused_dnode; TYPE_7__ os_userused_dnode; int /*<<< orphan*/  os_flags; TYPE_7__ os_meta_dnode; int /*<<< orphan*/  os_type; } ;
typedef  TYPE_3__ objset_phys_t ;
struct TYPE_14__ {scalar_t__ cm_param_len; int /*<<< orphan*/ * cm_param; int /*<<< orphan*/  cm_type; } ;
typedef  TYPE_4__ crypto_mechanism_t ;
struct TYPE_11__ {char* iov_base; int iov_len; } ;
struct TYPE_15__ {int cd_length; TYPE_1__ cd_raw; scalar_t__ cd_offset; int /*<<< orphan*/  cd_format; } ;
typedef  TYPE_5__ crypto_data_t ;
typedef  int /*<<< orphan*/  crypto_context_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  BSWAP_64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_DATA_RAW ; 
 int CRYPTO_SUCCESS ; 
 scalar_t__ DMU_OT_NONE ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  OBJSET_CRYPT_PORTABLE_FLAGS_MASK ; 
 scalar_t__ OBJSET_PHYS_SIZE_V1 ; 
 scalar_t__ OBJSET_PHYS_SIZE_V2 ; 
 scalar_t__ OBJSET_PHYS_SIZE_V3 ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int SHA512_DIGEST_LENGTH ; 
 int /*<<< orphan*/  SUN_CKM_SHA512_HMAC ; 
 int ZFS_HOST_BYTEORDER ; 
 int /*<<< orphan*/  ZIO_OBJSET_MAC_LEN ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int crypto_mac_final (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int crypto_mac_init (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int crypto_mac_update (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_mech2id (int /*<<< orphan*/ ) ; 
 int zio_crypt_do_dnode_hmac_updates (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_7__*) ; 

int
zio_crypt_do_objset_hmacs(zio_crypt_key_t *key, void *data, uint_t datalen,
    boolean_t should_bswap, uint8_t *portable_mac, uint8_t *local_mac)
{
	int ret;
	crypto_mechanism_t mech;
	crypto_context_t ctx;
	crypto_data_t cd;
	objset_phys_t *osp = data;
	uint64_t intval;
	boolean_t le_bswap = (should_bswap == ZFS_HOST_BYTEORDER);
	uint8_t raw_portable_mac[SHA512_DIGEST_LENGTH];
	uint8_t raw_local_mac[SHA512_DIGEST_LENGTH];

	/* initialize HMAC mechanism */
	mech.cm_type = crypto_mech2id(SUN_CKM_SHA512_HMAC);
	mech.cm_param = NULL;
	mech.cm_param_len = 0;

	cd.cd_format = CRYPTO_DATA_RAW;
	cd.cd_offset = 0;

	/* calculate the portable MAC from the portable fields and metadnode */
	ret = crypto_mac_init(&mech, &key->zk_hmac_key, NULL, &ctx, NULL);
	if (ret != CRYPTO_SUCCESS) {
		ret = SET_ERROR(EIO);
		goto error;
	}

	/* add in the os_type */
	intval = (le_bswap) ? osp->os_type : BSWAP_64(osp->os_type);
	cd.cd_length = sizeof (uint64_t);
	cd.cd_raw.iov_base = (char *)&intval;
	cd.cd_raw.iov_len = cd.cd_length;

	ret = crypto_mac_update(ctx, &cd, NULL);
	if (ret != CRYPTO_SUCCESS) {
		ret = SET_ERROR(EIO);
		goto error;
	}

	/* add in the portable os_flags */
	intval = osp->os_flags;
	if (should_bswap)
		intval = BSWAP_64(intval);
	intval &= OBJSET_CRYPT_PORTABLE_FLAGS_MASK;
	if (!ZFS_HOST_BYTEORDER)
		intval = BSWAP_64(intval);

	cd.cd_length = sizeof (uint64_t);
	cd.cd_raw.iov_base = (char *)&intval;
	cd.cd_raw.iov_len = cd.cd_length;

	ret = crypto_mac_update(ctx, &cd, NULL);
	if (ret != CRYPTO_SUCCESS) {
		ret = SET_ERROR(EIO);
		goto error;
	}

	/* add in fields from the metadnode */
	ret = zio_crypt_do_dnode_hmac_updates(ctx, key->zk_version,
	    should_bswap, &osp->os_meta_dnode);
	if (ret)
		goto error;

	/* store the final digest in a temporary buffer and copy what we need */
	cd.cd_length = SHA512_DIGEST_LENGTH;
	cd.cd_raw.iov_base = (char *)raw_portable_mac;
	cd.cd_raw.iov_len = cd.cd_length;

	ret = crypto_mac_final(ctx, &cd, NULL);
	if (ret != CRYPTO_SUCCESS) {
		ret = SET_ERROR(EIO);
		goto error;
	}

	bcopy(raw_portable_mac, portable_mac, ZIO_OBJSET_MAC_LEN);

	/*
	 * The local MAC protects the user, group and project accounting.
	 * If these objects are not present, the local MAC is zeroed out.
	 */
	if ((datalen >= OBJSET_PHYS_SIZE_V3 &&
	    osp->os_userused_dnode.dn_type == DMU_OT_NONE &&
	    osp->os_groupused_dnode.dn_type == DMU_OT_NONE &&
	    osp->os_projectused_dnode.dn_type == DMU_OT_NONE) ||
	    (datalen >= OBJSET_PHYS_SIZE_V2 &&
	    osp->os_userused_dnode.dn_type == DMU_OT_NONE &&
	    osp->os_groupused_dnode.dn_type == DMU_OT_NONE) ||
	    (datalen <= OBJSET_PHYS_SIZE_V1)) {
		bzero(local_mac, ZIO_OBJSET_MAC_LEN);
		return (0);
	}

	/* calculate the local MAC from the userused and groupused dnodes */
	ret = crypto_mac_init(&mech, &key->zk_hmac_key, NULL, &ctx, NULL);
	if (ret != CRYPTO_SUCCESS) {
		ret = SET_ERROR(EIO);
		goto error;
	}

	/* add in the non-portable os_flags */
	intval = osp->os_flags;
	if (should_bswap)
		intval = BSWAP_64(intval);
	intval &= ~OBJSET_CRYPT_PORTABLE_FLAGS_MASK;
	if (!ZFS_HOST_BYTEORDER)
		intval = BSWAP_64(intval);

	cd.cd_length = sizeof (uint64_t);
	cd.cd_raw.iov_base = (char *)&intval;
	cd.cd_raw.iov_len = cd.cd_length;

	ret = crypto_mac_update(ctx, &cd, NULL);
	if (ret != CRYPTO_SUCCESS) {
		ret = SET_ERROR(EIO);
		goto error;
	}

	/* add in fields from the user accounting dnodes */
	if (osp->os_userused_dnode.dn_type != DMU_OT_NONE) {
		ret = zio_crypt_do_dnode_hmac_updates(ctx, key->zk_version,
		    should_bswap, &osp->os_userused_dnode);
		if (ret)
			goto error;
	}

	if (osp->os_groupused_dnode.dn_type != DMU_OT_NONE) {
		ret = zio_crypt_do_dnode_hmac_updates(ctx, key->zk_version,
		    should_bswap, &osp->os_groupused_dnode);
		if (ret)
			goto error;
	}

	if (osp->os_projectused_dnode.dn_type != DMU_OT_NONE &&
	    datalen >= OBJSET_PHYS_SIZE_V3) {
		ret = zio_crypt_do_dnode_hmac_updates(ctx, key->zk_version,
		    should_bswap, &osp->os_projectused_dnode);
		if (ret)
			goto error;
	}

	/* store the final digest in a temporary buffer and copy what we need */
	cd.cd_length = SHA512_DIGEST_LENGTH;
	cd.cd_raw.iov_base = (char *)raw_local_mac;
	cd.cd_raw.iov_len = cd.cd_length;

	ret = crypto_mac_final(ctx, &cd, NULL);
	if (ret != CRYPTO_SUCCESS) {
		ret = SET_ERROR(EIO);
		goto error;
	}

	bcopy(raw_local_mac, local_mac, ZIO_OBJSET_MAC_LEN);

	return (0);

error:
	bzero(portable_mac, ZIO_OBJSET_MAC_LEN);
	bzero(local_mac, ZIO_OBJSET_MAC_LEN);
	return (ret);
}