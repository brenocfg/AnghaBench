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
struct TYPE_5__ {TYPE_2__* cc_provider_private; } ;
typedef  TYPE_1__ crypto_ctx_t ;
struct TYPE_6__ {int ac_flags; scalar_t__ ac_keysched_len; int /*<<< orphan*/  ac_keysched; } ;
typedef  TYPE_2__ aes_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int CRYPTO_SUCCESS ; 
 int PROVIDER_OWNS_KEY_SCHEDULE ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  crypto_free_mode_ctx (TYPE_2__*) ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
aes_free_context(crypto_ctx_t *ctx)
{
	aes_ctx_t *aes_ctx = ctx->cc_provider_private;

	if (aes_ctx != NULL) {
		if (aes_ctx->ac_flags & PROVIDER_OWNS_KEY_SCHEDULE) {
			ASSERT(aes_ctx->ac_keysched_len != 0);
			bzero(aes_ctx->ac_keysched, aes_ctx->ac_keysched_len);
			kmem_free(aes_ctx->ac_keysched,
			    aes_ctx->ac_keysched_len);
		}
		crypto_free_mode_ctx(aes_ctx);
		ctx->cc_provider_private = NULL;
	}

	return (CRYPTO_SUCCESS);
}