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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  crypto_req_handle_t ;
struct TYPE_9__ {scalar_t__ iov_base; } ;
struct TYPE_10__ {int cd_format; int /*<<< orphan*/  cd_length; int /*<<< orphan*/  cd_offset; TYPE_1__ cd_raw; } ;
typedef  TYPE_2__ crypto_data_t ;
struct TYPE_11__ {int /*<<< orphan*/ * cc_provider_private; } ;
typedef  TYPE_3__ crypto_ctx_t ;
struct TYPE_12__ {int /*<<< orphan*/  hc_icontext; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int CRYPTO_ARGUMENTS_BAD ; 
#define  CRYPTO_DATA_RAW 129 
#define  CRYPTO_DATA_UIO 128 
 int CRYPTO_SUCCESS ; 
 TYPE_7__* PROV_SHA1_HMAC_CTX (TYPE_3__*) ; 
 int /*<<< orphan*/  SHA1Update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sha1_digest_update_uio (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static int
sha1_mac_update(crypto_ctx_t *ctx, crypto_data_t *data, crypto_req_handle_t req)
{
	int ret = CRYPTO_SUCCESS;

	ASSERT(ctx->cc_provider_private != NULL);

	/*
	 * Do a SHA1 update of the inner context using the specified
	 * data.
	 */
	switch (data->cd_format) {
	case CRYPTO_DATA_RAW:
		SHA1Update(&PROV_SHA1_HMAC_CTX(ctx)->hc_icontext,
		    (uint8_t *)data->cd_raw.iov_base + data->cd_offset,
		    data->cd_length);
		break;
	case CRYPTO_DATA_UIO:
		ret = sha1_digest_update_uio(
		    &PROV_SHA1_HMAC_CTX(ctx)->hc_icontext, data);
		break;
	default:
		ret = CRYPTO_ARGUMENTS_BAD;
	}

	return (ret);
}