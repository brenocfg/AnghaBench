#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ulong_t ;
typedef  scalar_t__ uint_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uchar_t ;
struct TYPE_21__ {int /*<<< orphan*/  hc_ocontext; int /*<<< orphan*/  hc_icontext; } ;
typedef  TYPE_4__ sha1_hmac_ctx_t ;
typedef  size_t off_t ;
typedef  int /*<<< orphan*/ * crypto_spi_ctx_template_t ;
typedef  int /*<<< orphan*/  crypto_session_id_t ;
typedef  int /*<<< orphan*/  crypto_req_handle_t ;
typedef  int /*<<< orphan*/  crypto_provider_handle_t ;
struct TYPE_22__ {scalar_t__ cm_type; int cm_param_len; int /*<<< orphan*/ * cm_param; } ;
typedef  TYPE_5__ crypto_mechanism_t ;
struct TYPE_23__ {scalar_t__ ck_format; int /*<<< orphan*/ * ck_data; int /*<<< orphan*/  ck_length; } ;
typedef  TYPE_6__ crypto_key_t ;
struct TYPE_18__ {scalar_t__ iov_base; } ;
struct TYPE_24__ {int cd_length; int cd_format; size_t cd_offset; TYPE_3__* cd_uio; TYPE_1__ cd_raw; } ;
typedef  TYPE_7__ crypto_data_t ;
struct TYPE_20__ {scalar_t__ uio_iovcnt; TYPE_2__* uio_iov; int /*<<< orphan*/  uio_segflg; } ;
struct TYPE_19__ {size_t iov_len; size_t iov_base; } ;

/* Variables and functions */
 int CRYPTO_ARGUMENTS_BAD ; 
 scalar_t__ CRYPTO_BITS2BYTES (int /*<<< orphan*/ ) ; 
 int CRYPTO_DATA_LEN_RANGE ; 
#define  CRYPTO_DATA_RAW 129 
#define  CRYPTO_DATA_UIO 128 
 int CRYPTO_INVALID_MAC ; 
 scalar_t__ CRYPTO_KEY_RAW ; 
 int CRYPTO_MECHANISM_INVALID ; 
 int CRYPTO_MECHANISM_PARAM_INVALID ; 
 int CRYPTO_SUCCESS ; 
 size_t MIN (size_t,size_t) ; 
 int /*<<< orphan*/  PROV_SHA1_DIGEST_KEY (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PROV_SHA1_GET_DIGEST_LEN (TYPE_5__*,int) ; 
 int /*<<< orphan*/  SHA1Final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA1Update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int SHA1_DIGEST_LENGTH ; 
 scalar_t__ SHA1_HMAC_BLOCK_SIZE ; 
 scalar_t__ SHA1_HMAC_GEN_MECH_INFO_TYPE ; 
 scalar_t__ SHA1_HMAC_MECH_INFO_TYPE ; 
 int /*<<< orphan*/  SHA1_MAC_UPDATE (TYPE_7__*,TYPE_4__,int) ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  bcmp (int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,TYPE_4__*,int) ; 
 int /*<<< orphan*/  bzero (TYPE_4__*,int) ; 
 int /*<<< orphan*/  sha1_mac_init_ctx (TYPE_4__*,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int
sha1_mac_verify_atomic(crypto_provider_handle_t provider,
    crypto_session_id_t session_id, crypto_mechanism_t *mechanism,
    crypto_key_t *key, crypto_data_t *data, crypto_data_t *mac,
    crypto_spi_ctx_template_t ctx_template, crypto_req_handle_t req)
{
	int ret = CRYPTO_SUCCESS;
	uchar_t digest[SHA1_DIGEST_LENGTH];
	sha1_hmac_ctx_t sha1_hmac_ctx;
	uint32_t digest_len = SHA1_DIGEST_LENGTH;
	uint_t keylen_in_bytes = CRYPTO_BITS2BYTES(key->ck_length);

	if (mechanism->cm_type != SHA1_HMAC_MECH_INFO_TYPE &&
	    mechanism->cm_type != SHA1_HMAC_GEN_MECH_INFO_TYPE)
		return (CRYPTO_MECHANISM_INVALID);

	/* Add support for key by attributes (RFE 4706552) */
	if (key->ck_format != CRYPTO_KEY_RAW)
		return (CRYPTO_ARGUMENTS_BAD);

	if (ctx_template != NULL) {
		/* reuse context template */
		bcopy(ctx_template, &sha1_hmac_ctx, sizeof (sha1_hmac_ctx_t));
	} else {
		/* no context template, initialize context */
		if (keylen_in_bytes > SHA1_HMAC_BLOCK_SIZE) {
			/*
			 * Hash the passed-in key to get a smaller key.
			 * The inner context is used since it hasn't been
			 * initialized yet.
			 */
			PROV_SHA1_DIGEST_KEY(&sha1_hmac_ctx.hc_icontext,
			    key->ck_data, keylen_in_bytes, digest);
			sha1_mac_init_ctx(&sha1_hmac_ctx, digest,
			    SHA1_DIGEST_LENGTH);
		} else {
			sha1_mac_init_ctx(&sha1_hmac_ctx, key->ck_data,
			    keylen_in_bytes);
		}
	}

	/* get the mechanism parameters, if applicable */
	if (mechanism->cm_type == SHA1_HMAC_GEN_MECH_INFO_TYPE) {
		if (mechanism->cm_param == NULL ||
		    mechanism->cm_param_len != sizeof (ulong_t)) {
			ret = CRYPTO_MECHANISM_PARAM_INVALID;
			goto bail;
		}
		PROV_SHA1_GET_DIGEST_LEN(mechanism, digest_len);
		if (digest_len > SHA1_DIGEST_LENGTH) {
			ret = CRYPTO_MECHANISM_PARAM_INVALID;
			goto bail;
		}
	}

	if (mac->cd_length != digest_len) {
		ret = CRYPTO_INVALID_MAC;
		goto bail;
	}

	/* do a SHA1 update of the inner context using the specified data */
	SHA1_MAC_UPDATE(data, sha1_hmac_ctx, ret);
	if (ret != CRYPTO_SUCCESS)
		/* the update failed, free context and bail */
		goto bail;

	/* do a SHA1 final on the inner context */
	SHA1Final(digest, &sha1_hmac_ctx.hc_icontext);

	/*
	 * Do an SHA1 update on the outer context, feeding the inner
	 * digest as data.
	 */
	SHA1Update(&sha1_hmac_ctx.hc_ocontext, digest, SHA1_DIGEST_LENGTH);

	/*
	 * Do a SHA1 final on the outer context, storing the computed
	 * digest in the users buffer.
	 */
	SHA1Final(digest, &sha1_hmac_ctx.hc_ocontext);

	/*
	 * Compare the computed digest against the expected digest passed
	 * as argument.
	 */

	switch (mac->cd_format) {

	case CRYPTO_DATA_RAW:
		if (bcmp(digest, (unsigned char *)mac->cd_raw.iov_base +
		    mac->cd_offset, digest_len) != 0)
			ret = CRYPTO_INVALID_MAC;
		break;

	case CRYPTO_DATA_UIO: {
		off_t offset = mac->cd_offset;
		uint_t vec_idx = 0;
		off_t scratch_offset = 0;
		size_t length = digest_len;
		size_t cur_len;

		/* we support only kernel buffer */
		if (mac->cd_uio->uio_segflg != UIO_SYSSPACE)
			return (CRYPTO_ARGUMENTS_BAD);

		/* jump to the first iovec containing the expected digest */
		while (vec_idx < mac->cd_uio->uio_iovcnt &&
		    offset >= mac->cd_uio->uio_iov[vec_idx].iov_len) {
			offset -= mac->cd_uio->uio_iov[vec_idx].iov_len;
			vec_idx++;
		}
		if (vec_idx == mac->cd_uio->uio_iovcnt) {
			/*
			 * The caller specified an offset that is
			 * larger than the total size of the buffers
			 * it provided.
			 */
			ret = CRYPTO_DATA_LEN_RANGE;
			break;
		}

		/* do the comparison of computed digest vs specified one */
		while (vec_idx < mac->cd_uio->uio_iovcnt && length > 0) {
			cur_len = MIN(mac->cd_uio->uio_iov[vec_idx].iov_len -
			    offset, length);

			if (bcmp(digest + scratch_offset,
			    mac->cd_uio->uio_iov[vec_idx].iov_base + offset,
			    cur_len) != 0) {
				ret = CRYPTO_INVALID_MAC;
				break;
			}

			length -= cur_len;
			vec_idx++;
			scratch_offset += cur_len;
			offset = 0;
		}
		break;
	}

	default:
		ret = CRYPTO_ARGUMENTS_BAD;
	}

	bzero(&sha1_hmac_ctx, sizeof (sha1_hmac_ctx_t));
	return (ret);
bail:
	bzero(&sha1_hmac_ctx, sizeof (sha1_hmac_ctx_t));
	mac->cd_length = 0;
	return (ret);
}