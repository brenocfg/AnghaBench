#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  crypto_ctx_t ;
typedef  int /*<<< orphan*/ * SKEIN_CTX_LVALUE ;

/* Variables and functions */
 int CRYPTO_SUCCESS ; 
 int /*<<< orphan*/ * SKEIN_CTX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
skein_free_context(crypto_ctx_t *ctx)
{
	if (SKEIN_CTX(ctx) != NULL) {
		bzero(SKEIN_CTX(ctx), sizeof (*SKEIN_CTX(ctx)));
		kmem_free(SKEIN_CTX(ctx), sizeof (*SKEIN_CTX(ctx)));
		SKEIN_CTX_LVALUE(ctx) = NULL;
	}

	return (CRYPTO_SUCCESS);
}