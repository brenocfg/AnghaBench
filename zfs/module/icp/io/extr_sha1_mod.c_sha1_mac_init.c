#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ulong_t ;
typedef  scalar_t__ uint_t ;
typedef  int /*<<< orphan*/  uchar_t ;
struct TYPE_16__ {int /*<<< orphan*/  hc_icontext; } ;
typedef  TYPE_1__ sha1_hmac_ctx_t ;
typedef  int /*<<< orphan*/ * crypto_spi_ctx_template_t ;
typedef  int /*<<< orphan*/  crypto_req_handle_t ;
struct TYPE_17__ {scalar_t__ cm_type; int cm_param_len; int /*<<< orphan*/ * cm_param; } ;
typedef  TYPE_2__ crypto_mechanism_t ;
struct TYPE_18__ {scalar_t__ ck_format; int /*<<< orphan*/ * ck_data; int /*<<< orphan*/  ck_length; } ;
typedef  TYPE_3__ crypto_key_t ;
struct TYPE_19__ {TYPE_1__* cc_provider_private; } ;
typedef  TYPE_4__ crypto_ctx_t ;
struct TYPE_20__ {scalar_t__ hc_mech_type; int hc_digest_len; } ;

/* Variables and functions */
 int CRYPTO_ARGUMENTS_BAD ; 
 scalar_t__ CRYPTO_BITS2BYTES (int /*<<< orphan*/ ) ; 
 int CRYPTO_HOST_MEMORY ; 
 scalar_t__ CRYPTO_KEY_RAW ; 
 int CRYPTO_MECHANISM_INVALID ; 
 int CRYPTO_MECHANISM_PARAM_INVALID ; 
 int CRYPTO_SUCCESS ; 
 int /*<<< orphan*/  PROV_SHA1_DIGEST_KEY (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PROV_SHA1_GET_DIGEST_LEN (TYPE_2__*,int) ; 
 TYPE_5__* PROV_SHA1_HMAC_CTX (TYPE_4__*) ; 
 int SHA1_DIGEST_LENGTH ; 
 scalar_t__ SHA1_HMAC_BLOCK_SIZE ; 
 scalar_t__ SHA1_HMAC_GEN_MECH_INFO_TYPE ; 
 scalar_t__ SHA1_HMAC_MECH_INFO_TYPE ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,TYPE_5__*,int) ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  crypto_kmflag (int /*<<< orphan*/ ) ; 
 TYPE_1__* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  sha1_mac_init_ctx (TYPE_5__*,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int
sha1_mac_init(crypto_ctx_t *ctx, crypto_mechanism_t *mechanism,
    crypto_key_t *key, crypto_spi_ctx_template_t ctx_template,
    crypto_req_handle_t req)
{
	int ret = CRYPTO_SUCCESS;
	uint_t keylen_in_bytes = CRYPTO_BITS2BYTES(key->ck_length);

	if (mechanism->cm_type != SHA1_HMAC_MECH_INFO_TYPE &&
	    mechanism->cm_type != SHA1_HMAC_GEN_MECH_INFO_TYPE)
		return (CRYPTO_MECHANISM_INVALID);

	/* Add support for key by attributes (RFE 4706552) */
	if (key->ck_format != CRYPTO_KEY_RAW)
		return (CRYPTO_ARGUMENTS_BAD);

	ctx->cc_provider_private = kmem_alloc(sizeof (sha1_hmac_ctx_t),
	    crypto_kmflag(req));
	if (ctx->cc_provider_private == NULL)
		return (CRYPTO_HOST_MEMORY);

	if (ctx_template != NULL) {
		/* reuse context template */
		bcopy(ctx_template, PROV_SHA1_HMAC_CTX(ctx),
		    sizeof (sha1_hmac_ctx_t));
	} else {
		/* no context template, compute context */
		if (keylen_in_bytes > SHA1_HMAC_BLOCK_SIZE) {
			uchar_t digested_key[SHA1_DIGEST_LENGTH];
			sha1_hmac_ctx_t *hmac_ctx = ctx->cc_provider_private;

			/*
			 * Hash the passed-in key to get a smaller key.
			 * The inner context is used since it hasn't been
			 * initialized yet.
			 */
			PROV_SHA1_DIGEST_KEY(&hmac_ctx->hc_icontext,
			    key->ck_data, keylen_in_bytes, digested_key);
			sha1_mac_init_ctx(PROV_SHA1_HMAC_CTX(ctx),
			    digested_key, SHA1_DIGEST_LENGTH);
		} else {
			sha1_mac_init_ctx(PROV_SHA1_HMAC_CTX(ctx),
			    key->ck_data, keylen_in_bytes);
		}
	}

	/*
	 * Get the mechanism parameters, if applicable.
	 */
	PROV_SHA1_HMAC_CTX(ctx)->hc_mech_type = mechanism->cm_type;
	if (mechanism->cm_type == SHA1_HMAC_GEN_MECH_INFO_TYPE) {
		if (mechanism->cm_param == NULL ||
		    mechanism->cm_param_len != sizeof (ulong_t))
			ret = CRYPTO_MECHANISM_PARAM_INVALID;
		PROV_SHA1_GET_DIGEST_LEN(mechanism,
		    PROV_SHA1_HMAC_CTX(ctx)->hc_digest_len);
		if (PROV_SHA1_HMAC_CTX(ctx)->hc_digest_len >
		    SHA1_DIGEST_LENGTH)
			ret = CRYPTO_MECHANISM_PARAM_INVALID;
	}

	if (ret != CRYPTO_SUCCESS) {
		bzero(ctx->cc_provider_private, sizeof (sha1_hmac_ctx_t));
		kmem_free(ctx->cc_provider_private, sizeof (sha1_hmac_ctx_t));
		ctx->cc_provider_private = NULL;
	}

	return (ret);
}