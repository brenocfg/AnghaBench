#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  redisContext ;
struct TYPE_2__ {scalar_t__ sni; scalar_t__ key; scalar_t__ cert; scalar_t__ cacertdir; scalar_t__ cacert; } ;
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int REDIS_ERR ; 
 int REDIS_OK ; 
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_load_verify_locations (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/ * SSL_CTX_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_default_verify_paths (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_set_options (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SSL_CTX_set_verify (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_use_PrivateKey_file (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_use_certificate_chain_file (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  SSL_FILETYPE_PEM ; 
 int SSL_OP_NO_SSLv2 ; 
 int SSL_OP_NO_SSLv3 ; 
 int /*<<< orphan*/  SSL_VERIFY_PEER ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set_tlsext_host_name (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  SSLv23_client_method () ; 
 TYPE_1__ config ; 
 int redisInitiateSSL (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cliSecureConnection(redisContext *c, const char **err) {
#ifdef USE_OPENSSL
    static SSL_CTX *ssl_ctx = NULL;

    if (!ssl_ctx) {
        ssl_ctx = SSL_CTX_new(SSLv23_client_method());
        if (!ssl_ctx) {
            *err = "Failed to create SSL_CTX";
            goto error;
        }

        SSL_CTX_set_options(ssl_ctx, SSL_OP_NO_SSLv2 | SSL_OP_NO_SSLv3);
        SSL_CTX_set_verify(ssl_ctx, SSL_VERIFY_PEER, NULL);

        if (config.cacert || config.cacertdir) {
            if (!SSL_CTX_load_verify_locations(ssl_ctx, config.cacert, config.cacertdir)) {
                *err = "Invalid CA Certificate File/Directory";
                goto error;
            }
        } else {
            if (!SSL_CTX_set_default_verify_paths(ssl_ctx)) {
                *err = "Failed to use default CA paths";
                goto error;
            }
        }

        if (config.cert && !SSL_CTX_use_certificate_chain_file(ssl_ctx, config.cert)) {
            *err = "Invalid client certificate";
            goto error;
        }

        if (config.key && !SSL_CTX_use_PrivateKey_file(ssl_ctx, config.key, SSL_FILETYPE_PEM)) {
            *err = "Invalid private key";
            goto error;
        }
    }

    SSL *ssl = SSL_new(ssl_ctx);
    if (!ssl) {
        *err = "Failed to create SSL object";
        return REDIS_ERR;
    }

    if (config.sni && !SSL_set_tlsext_host_name(ssl, config.sni)) {
        *err = "Failed to configure SNI";
        SSL_free(ssl);
        return REDIS_ERR;
    }

    return redisInitiateSSL(c, ssl);

error:
    SSL_CTX_free(ssl_ctx);
    ssl_ctx = NULL;
    return REDIS_ERR;
#else
    (void) c;
    (void) err;
    return REDIS_OK;
#endif
}