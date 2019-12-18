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

/* Variables and functions */
 int /*<<< orphan*/  CONF_modules_unload (int) ; 
 int /*<<< orphan*/  CRYPTO_cleanup_all_ex_data () ; 
 int /*<<< orphan*/  ENGINE_cleanup () ; 
 int /*<<< orphan*/  ERR_free_strings () ; 
 int /*<<< orphan*/  EVP_cleanup () ; 
 int /*<<< orphan*/  SSL_COMP_get_compression_methods () ; 
 scalar_t__ TLS_IS_INIT ; 
 int /*<<< orphan*/  sk_SSL_COMP_free (int /*<<< orphan*/ ) ; 

void __attribute__((destructor)) ltls_destory(void) {
    if(TLS_IS_INIT) {
        ENGINE_cleanup();
        CONF_modules_unload(1);
        ERR_free_strings();
        EVP_cleanup();
        sk_SSL_COMP_free(SSL_COMP_get_compression_methods());
        CRYPTO_cleanup_all_ex_data();
    }
}