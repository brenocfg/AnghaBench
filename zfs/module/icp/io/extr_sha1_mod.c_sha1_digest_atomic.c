#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  crypto_session_id_t ;
typedef  int /*<<< orphan*/  crypto_req_handle_t ;
typedef  int /*<<< orphan*/  crypto_provider_handle_t ;
struct TYPE_10__ {scalar_t__ cm_type; } ;
typedef  TYPE_2__ crypto_mechanism_t ;
struct TYPE_9__ {scalar_t__ iov_base; } ;
struct TYPE_11__ {int cd_format; scalar_t__ cd_length; int /*<<< orphan*/  cd_offset; TYPE_1__ cd_raw; } ;
typedef  TYPE_3__ crypto_data_t ;
typedef  int /*<<< orphan*/  SHA1_CTX ;

/* Variables and functions */
 int CRYPTO_ARGUMENTS_BAD ; 
#define  CRYPTO_DATA_RAW 129 
#define  CRYPTO_DATA_UIO 128 
 int CRYPTO_MECHANISM_INVALID ; 
 int CRYPTO_SUCCESS ; 
 int /*<<< orphan*/  SHA1Final (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA1Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA1Update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ SHA1_DIGEST_LENGTH ; 
 scalar_t__ SHA1_MECH_INFO_TYPE ; 
 int sha1_digest_final_uio (int /*<<< orphan*/ *,TYPE_3__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int sha1_digest_update_uio (int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static int
sha1_digest_atomic(crypto_provider_handle_t provider,
    crypto_session_id_t session_id, crypto_mechanism_t *mechanism,
    crypto_data_t *data, crypto_data_t *digest,
    crypto_req_handle_t req)
{
	int ret = CRYPTO_SUCCESS;
	SHA1_CTX sha1_ctx;

	if (mechanism->cm_type != SHA1_MECH_INFO_TYPE)
		return (CRYPTO_MECHANISM_INVALID);

	/*
	 * Do the SHA1 init.
	 */
	SHA1Init(&sha1_ctx);

	/*
	 * Do the SHA1 update on the specified input data.
	 */
	switch (data->cd_format) {
	case CRYPTO_DATA_RAW:
		SHA1Update(&sha1_ctx,
		    (uint8_t *)data->cd_raw.iov_base + data->cd_offset,
		    data->cd_length);
		break;
	case CRYPTO_DATA_UIO:
		ret = sha1_digest_update_uio(&sha1_ctx, data);
		break;
	default:
		ret = CRYPTO_ARGUMENTS_BAD;
	}

	if (ret != CRYPTO_SUCCESS) {
		/* the update failed, bail */
		digest->cd_length = 0;
		return (ret);
	}

	/*
	 * Do a SHA1 final, must be done separately since the digest
	 * type can be different than the input data type.
	 */
	switch (digest->cd_format) {
	case CRYPTO_DATA_RAW:
		SHA1Final((unsigned char *)digest->cd_raw.iov_base +
		    digest->cd_offset, &sha1_ctx);
		break;
	case CRYPTO_DATA_UIO:
		ret = sha1_digest_final_uio(&sha1_ctx, digest,
		    SHA1_DIGEST_LENGTH, NULL);
		break;
	default:
		ret = CRYPTO_ARGUMENTS_BAD;
	}

	if (ret == CRYPTO_SUCCESS) {
		digest->cd_length = SHA1_DIGEST_LENGTH;
	} else {
		digest->cd_length = 0;
	}

	return (ret);
}