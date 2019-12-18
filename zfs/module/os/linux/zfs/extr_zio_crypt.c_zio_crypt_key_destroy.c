#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  zk_hmac_tmpl; int /*<<< orphan*/  zk_current_tmpl; int /*<<< orphan*/  zk_salt_lock; } ;
typedef  TYPE_1__ zio_crypt_key_t ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  crypto_destroy_ctx_template (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_destroy (int /*<<< orphan*/ *) ; 

void
zio_crypt_key_destroy(zio_crypt_key_t *key)
{
	rw_destroy(&key->zk_salt_lock);

	/* free crypto templates */
	crypto_destroy_ctx_template(key->zk_current_tmpl);
	crypto_destroy_ctx_template(key->zk_hmac_tmpl);

	/* zero out sensitive data */
	bzero(key, sizeof (zio_crypt_key_t));
}