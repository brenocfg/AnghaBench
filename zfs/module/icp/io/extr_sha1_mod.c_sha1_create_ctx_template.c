#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint_t ;
typedef  int /*<<< orphan*/  uchar_t ;
struct TYPE_8__ {scalar_t__ hc_mech_type; int /*<<< orphan*/  hc_icontext; } ;
typedef  TYPE_1__ sha1_hmac_ctx_t ;
typedef  scalar_t__ crypto_spi_ctx_template_t ;
typedef  int /*<<< orphan*/  crypto_req_handle_t ;
typedef  int /*<<< orphan*/  crypto_provider_handle_t ;
struct TYPE_9__ {scalar_t__ cm_type; } ;
typedef  TYPE_2__ crypto_mechanism_t ;
struct TYPE_10__ {scalar_t__ ck_format; int /*<<< orphan*/ * ck_data; int /*<<< orphan*/  ck_length; } ;
typedef  TYPE_3__ crypto_key_t ;

/* Variables and functions */
 int CRYPTO_ARGUMENTS_BAD ; 
 scalar_t__ CRYPTO_BITS2BYTES (int /*<<< orphan*/ ) ; 
 int CRYPTO_HOST_MEMORY ; 
 scalar_t__ CRYPTO_KEY_RAW ; 
 int CRYPTO_MECHANISM_INVALID ; 
 int CRYPTO_SUCCESS ; 
 int /*<<< orphan*/  PROV_SHA1_DIGEST_KEY (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int SHA1_DIGEST_LENGTH ; 
 scalar_t__ SHA1_HMAC_BLOCK_SIZE ; 
 scalar_t__ SHA1_HMAC_GEN_MECH_INFO_TYPE ; 
 scalar_t__ SHA1_HMAC_MECH_INFO_TYPE ; 
 int /*<<< orphan*/  crypto_kmflag (int /*<<< orphan*/ ) ; 
 TYPE_1__* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sha1_mac_init_ctx (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int
sha1_create_ctx_template(crypto_provider_handle_t provider,
    crypto_mechanism_t *mechanism, crypto_key_t *key,
    crypto_spi_ctx_template_t *ctx_template, size_t *ctx_template_size,
    crypto_req_handle_t req)
{
	sha1_hmac_ctx_t *sha1_hmac_ctx_tmpl;
	uint_t keylen_in_bytes = CRYPTO_BITS2BYTES(key->ck_length);

	if ((mechanism->cm_type != SHA1_HMAC_MECH_INFO_TYPE) &&
	    (mechanism->cm_type != SHA1_HMAC_GEN_MECH_INFO_TYPE)) {
		return (CRYPTO_MECHANISM_INVALID);
	}

	/* Add support for key by attributes (RFE 4706552) */
	if (key->ck_format != CRYPTO_KEY_RAW)
		return (CRYPTO_ARGUMENTS_BAD);

	/*
	 * Allocate and initialize SHA1 context.
	 */
	sha1_hmac_ctx_tmpl = kmem_alloc(sizeof (sha1_hmac_ctx_t),
	    crypto_kmflag(req));
	if (sha1_hmac_ctx_tmpl == NULL)
		return (CRYPTO_HOST_MEMORY);

	if (keylen_in_bytes > SHA1_HMAC_BLOCK_SIZE) {
		uchar_t digested_key[SHA1_DIGEST_LENGTH];

		/*
		 * Hash the passed-in key to get a smaller key.
		 * The inner context is used since it hasn't been
		 * initialized yet.
		 */
		PROV_SHA1_DIGEST_KEY(&sha1_hmac_ctx_tmpl->hc_icontext,
		    key->ck_data, keylen_in_bytes, digested_key);
		sha1_mac_init_ctx(sha1_hmac_ctx_tmpl, digested_key,
		    SHA1_DIGEST_LENGTH);
	} else {
		sha1_mac_init_ctx(sha1_hmac_ctx_tmpl, key->ck_data,
		    keylen_in_bytes);
	}

	sha1_hmac_ctx_tmpl->hc_mech_type = mechanism->cm_type;
	*ctx_template = (crypto_spi_ctx_template_t)sha1_hmac_ctx_tmpl;
	*ctx_template_size = sizeof (sha1_hmac_ctx_t);


	return (CRYPTO_SUCCESS);
}