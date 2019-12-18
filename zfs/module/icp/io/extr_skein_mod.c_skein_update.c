#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  crypto_req_handle_t ;
struct TYPE_5__ {scalar_t__ iov_base; } ;
struct TYPE_6__ {int cd_format; int /*<<< orphan*/  cd_length; int /*<<< orphan*/  cd_offset; TYPE_1__ cd_raw; } ;
typedef  TYPE_2__ crypto_data_t ;
typedef  int /*<<< orphan*/  crypto_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int CRYPTO_ARGUMENTS_BAD ; 
#define  CRYPTO_DATA_RAW 129 
#define  CRYPTO_DATA_UIO 128 
 int CRYPTO_SUCCESS ; 
 int /*<<< orphan*/ * SKEIN_CTX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SKEIN_OP (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Update ; 
 int skein_digest_update_uio (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static int
skein_update(crypto_ctx_t *ctx, crypto_data_t *data, crypto_req_handle_t req)
{
	int error = CRYPTO_SUCCESS;

	ASSERT(SKEIN_CTX(ctx) != NULL);

	switch (data->cd_format) {
	case CRYPTO_DATA_RAW:
		SKEIN_OP(SKEIN_CTX(ctx), Update,
		    (uint8_t *)data->cd_raw.iov_base + data->cd_offset,
		    data->cd_length);
		break;
	case CRYPTO_DATA_UIO:
		error = skein_digest_update_uio(SKEIN_CTX(ctx), data);
		break;
	default:
		error = CRYPTO_ARGUMENTS_BAD;
	}

	return (error);
}