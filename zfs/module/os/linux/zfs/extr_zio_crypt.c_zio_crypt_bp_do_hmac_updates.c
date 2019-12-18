#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_4__ {char* iov_base; int /*<<< orphan*/  iov_len; } ;
struct TYPE_5__ {int /*<<< orphan*/  cd_length; TYPE_1__ cd_raw; scalar_t__ cd_offset; int /*<<< orphan*/  cd_format; } ;
typedef  TYPE_2__ crypto_data_t ;
typedef  int /*<<< orphan*/  crypto_context_t ;
typedef  int /*<<< orphan*/  boolean_t ;
typedef  int /*<<< orphan*/  blkptr_t ;
typedef  int /*<<< orphan*/  blkptr_auth_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_DATA_RAW ; 
 int CRYPTO_SUCCESS ; 
 int /*<<< orphan*/  EIO ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int crypto_mac_update (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zio_crypt_bp_auth_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zio_crypt_bp_do_hmac_updates(crypto_context_t ctx, uint64_t version,
    boolean_t should_bswap, blkptr_t *bp)
{
	int ret;
	uint_t bab_len;
	blkptr_auth_buf_t bab;
	crypto_data_t cd;

	zio_crypt_bp_auth_init(version, should_bswap, bp, &bab, &bab_len);
	cd.cd_format = CRYPTO_DATA_RAW;
	cd.cd_offset = 0;
	cd.cd_length = bab_len;
	cd.cd_raw.iov_base = (char *)&bab;
	cd.cd_raw.iov_len = cd.cd_length;

	ret = crypto_mac_update(ctx, &cd, NULL);
	if (ret != CRYPTO_SUCCESS) {
		ret = SET_ERROR(EIO);
		goto error;
	}

	return (0);

error:
	return (ret);
}