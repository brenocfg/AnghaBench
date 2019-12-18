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
typedef  int /*<<< orphan*/  skein_ctx_t ;
typedef  int /*<<< orphan*/ * crypto_spi_ctx_template_t ;
typedef  int /*<<< orphan*/  crypto_req_handle_t ;
typedef  int /*<<< orphan*/  crypto_provider_handle_t ;
typedef  int /*<<< orphan*/  crypto_mechanism_t ;
typedef  int /*<<< orphan*/  crypto_key_t ;

/* Variables and functions */
 int CRYPTO_HOST_MEMORY ; 
 int CRYPTO_SUCCESS ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  crypto_kmflag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ *,int) ; 
 int skein_mac_ctx_build (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
skein_create_ctx_template(crypto_provider_handle_t provider,
    crypto_mechanism_t *mechanism, crypto_key_t *key,
    crypto_spi_ctx_template_t *ctx_template, size_t *ctx_template_size,
    crypto_req_handle_t req)
{
	int		error;
	skein_ctx_t	*ctx_tmpl;

	ctx_tmpl = kmem_alloc(sizeof (*ctx_tmpl), crypto_kmflag(req));
	if (ctx_tmpl == NULL)
		return (CRYPTO_HOST_MEMORY);
	error = skein_mac_ctx_build(ctx_tmpl, mechanism, key);
	if (error != CRYPTO_SUCCESS)
		goto errout;
	*ctx_template = ctx_tmpl;
	*ctx_template_size = sizeof (*ctx_tmpl);

	return (CRYPTO_SUCCESS);
errout:
	bzero(ctx_tmpl, sizeof (*ctx_tmpl));
	kmem_free(ctx_tmpl, sizeof (*ctx_tmpl));
	return (error);
}