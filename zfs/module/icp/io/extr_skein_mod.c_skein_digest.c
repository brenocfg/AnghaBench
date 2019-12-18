#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  crypto_req_handle_t ;
struct TYPE_9__ {scalar_t__ cd_length; } ;
typedef  TYPE_1__ crypto_data_t ;
typedef  int /*<<< orphan*/  crypto_ctx_t ;
struct TYPE_10__ {int /*<<< orphan*/  sc_digest_bitlen; } ;
typedef  int /*<<< orphan*/ * SKEIN_CTX_LVALUE ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ CRYPTO_BITS2BYTES (int /*<<< orphan*/ ) ; 
 int CRYPTO_BUFFER_TOO_SMALL ; 
 int CRYPTO_SUCCESS ; 
 TYPE_6__* SKEIN_CTX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (TYPE_6__*,int) ; 
 int /*<<< orphan*/  kmem_free (TYPE_6__*,int) ; 
 int skein_final (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int skein_update (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
skein_digest(crypto_ctx_t *ctx, crypto_data_t *data, crypto_data_t *digest,
    crypto_req_handle_t req)
{
	int error = CRYPTO_SUCCESS;

	ASSERT(SKEIN_CTX(ctx) != NULL);

	if (digest->cd_length <
	    CRYPTO_BITS2BYTES(SKEIN_CTX(ctx)->sc_digest_bitlen)) {
		digest->cd_length =
		    CRYPTO_BITS2BYTES(SKEIN_CTX(ctx)->sc_digest_bitlen);
		return (CRYPTO_BUFFER_TOO_SMALL);
	}

	error = skein_update(ctx, data, req);
	if (error != CRYPTO_SUCCESS) {
		bzero(SKEIN_CTX(ctx), sizeof (*SKEIN_CTX(ctx)));
		kmem_free(SKEIN_CTX(ctx), sizeof (*SKEIN_CTX(ctx)));
		SKEIN_CTX_LVALUE(ctx) = NULL;
		digest->cd_length = 0;
		return (error);
	}
	error = skein_final(ctx, digest, req);

	return (error);
}