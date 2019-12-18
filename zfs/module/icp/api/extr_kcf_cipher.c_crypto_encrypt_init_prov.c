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
typedef  int /*<<< orphan*/  crypto_session_id_t ;
typedef  int /*<<< orphan*/  crypto_provider_t ;
typedef  int /*<<< orphan*/  crypto_mechanism_t ;
typedef  int /*<<< orphan*/  crypto_key_t ;
typedef  int /*<<< orphan*/  crypto_ctx_template_t ;
typedef  int /*<<< orphan*/  crypto_context_t ;
typedef  int /*<<< orphan*/  crypto_call_req_t ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_FG_ENCRYPT ; 
 int crypto_cipher_init_prov (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
crypto_encrypt_init_prov(crypto_provider_t pd, crypto_session_id_t sid,
    crypto_mechanism_t *mech, crypto_key_t *key,
    crypto_ctx_template_t tmpl, crypto_context_t *ctxp,
    crypto_call_req_t *crq)
{
	return (crypto_cipher_init_prov(pd, sid, mech, key, tmpl, ctxp, crq,
	    CRYPTO_FG_ENCRYPT));
}