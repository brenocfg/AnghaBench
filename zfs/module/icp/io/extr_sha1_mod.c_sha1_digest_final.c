#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sha1_ctx_t ;
typedef  int /*<<< orphan*/  crypto_req_handle_t ;
struct TYPE_9__ {scalar_t__ iov_base; } ;
struct TYPE_10__ {scalar_t__ cd_length; int cd_format; int /*<<< orphan*/  cd_offset; TYPE_1__ cd_raw; } ;
typedef  TYPE_2__ crypto_data_t ;
struct TYPE_11__ {int /*<<< orphan*/ * cc_provider_private; } ;
typedef  TYPE_3__ crypto_ctx_t ;
struct TYPE_12__ {int /*<<< orphan*/  sc_sha1_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int CRYPTO_ARGUMENTS_BAD ; 
 int CRYPTO_BUFFER_TOO_SMALL ; 
#define  CRYPTO_DATA_RAW 129 
#define  CRYPTO_DATA_UIO 128 
 int CRYPTO_SUCCESS ; 
 TYPE_7__* PROV_SHA1_CTX (TYPE_3__*) ; 
 int /*<<< orphan*/  SHA1Final (unsigned char*,int /*<<< orphan*/ *) ; 
 scalar_t__ SHA1_DIGEST_LENGTH ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ *,int) ; 
 int sha1_digest_final_uio (int /*<<< orphan*/ *,TYPE_2__*,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
sha1_digest_final(crypto_ctx_t *ctx, crypto_data_t *digest,
    crypto_req_handle_t req)
{
	int ret = CRYPTO_SUCCESS;

	ASSERT(ctx->cc_provider_private != NULL);

	/*
	 * We need to just return the length needed to store the output.
	 * We should not destroy the context for the following cases.
	 */
	if ((digest->cd_length == 0) ||
	    (digest->cd_length < SHA1_DIGEST_LENGTH)) {
		digest->cd_length = SHA1_DIGEST_LENGTH;
		return (CRYPTO_BUFFER_TOO_SMALL);
	}

	/*
	 * Do a SHA1 final.
	 */
	switch (digest->cd_format) {
	case CRYPTO_DATA_RAW:
		SHA1Final((unsigned char *)digest->cd_raw.iov_base +
		    digest->cd_offset, &PROV_SHA1_CTX(ctx)->sc_sha1_ctx);
		break;
	case CRYPTO_DATA_UIO:
		ret = sha1_digest_final_uio(&PROV_SHA1_CTX(ctx)->sc_sha1_ctx,
		    digest, SHA1_DIGEST_LENGTH, NULL);
		break;
	default:
		ret = CRYPTO_ARGUMENTS_BAD;
	}

	/* all done, free context and return */

	if (ret == CRYPTO_SUCCESS) {
		digest->cd_length = SHA1_DIGEST_LENGTH;
	} else {
		digest->cd_length = 0;
	}

	kmem_free(ctx->cc_provider_private, sizeof (sha1_ctx_t));
	ctx->cc_provider_private = NULL;

	return (ret);
}