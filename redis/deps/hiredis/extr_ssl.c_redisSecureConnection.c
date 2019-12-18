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
typedef  int /*<<< orphan*/  redisContext ;
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int REDIS_ERR ; 
 int /*<<< orphan*/  REDIS_ERR_OTHER ; 
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_load_verify_locations (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_CTX_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_info_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_options (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SSL_CTX_set_verify (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_use_PrivateKey_file (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_use_certificate_chain_file (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  SSL_FILETYPE_PEM ; 
 int SSL_OP_NO_SSLv2 ; 
 int SSL_OP_NO_SSLv3 ; 
 int /*<<< orphan*/  SSL_VERIFY_PEER ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_library_init () ; 
 int /*<<< orphan*/ * SSL_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set_tlsext_host_name (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  SSLv23_client_method () ; 
 int /*<<< orphan*/  __redisSetError (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  initOpensslLocks () ; 
 int redisSSLConnect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sslLogCallback ; 

int redisSecureConnection(redisContext *c, const char *capath,
                          const char *certpath, const char *keypath, const char *servername) {

    SSL_CTX *ssl_ctx = NULL;
    SSL *ssl = NULL;

    /* Initialize global OpenSSL stuff */
    static int isInit = 0;
    if (!isInit) {
        isInit = 1;
        SSL_library_init();
#ifdef HIREDIS_USE_CRYPTO_LOCKS
        initOpensslLocks();
#endif
    }

    ssl_ctx = SSL_CTX_new(SSLv23_client_method());
    if (!ssl_ctx) {
        __redisSetError(c, REDIS_ERR_OTHER, "Failed to create SSL_CTX");
        goto error;
    }

#ifdef HIREDIS_SSL_TRACE
    SSL_CTX_set_info_callback(ssl_ctx, sslLogCallback);
#endif
    SSL_CTX_set_options(ssl_ctx, SSL_OP_NO_SSLv2 | SSL_OP_NO_SSLv3);
    SSL_CTX_set_verify(ssl_ctx, SSL_VERIFY_PEER, NULL);
    if ((certpath != NULL && keypath == NULL) || (keypath != NULL && certpath == NULL)) {
        __redisSetError(c, REDIS_ERR_OTHER, "certpath and keypath must be specified together");
        goto error;
    }

    if (capath) {
        if (!SSL_CTX_load_verify_locations(ssl_ctx, capath, NULL)) {
            __redisSetError(c, REDIS_ERR_OTHER, "Invalid CA certificate");
            goto error;
        }
    }
    if (certpath) {
        if (!SSL_CTX_use_certificate_chain_file(ssl_ctx, certpath)) {
            __redisSetError(c, REDIS_ERR_OTHER, "Invalid client certificate");
            goto error;
        }
        if (!SSL_CTX_use_PrivateKey_file(ssl_ctx, keypath, SSL_FILETYPE_PEM)) {
            __redisSetError(c, REDIS_ERR_OTHER, "Invalid client key");
            goto error;
        }
    }

    ssl = SSL_new(ssl_ctx);
    if (!ssl) {
        __redisSetError(c, REDIS_ERR_OTHER, "Couldn't create new SSL instance");
        goto error;
    }
    if (servername) {
        if (!SSL_set_tlsext_host_name(ssl, servername)) {
            __redisSetError(c, REDIS_ERR_OTHER, "Couldn't set server name indication");
            goto error;
        }
    }

    return redisSSLConnect(c, ssl_ctx, ssl);

error:
    if (ssl) SSL_free(ssl);
    if (ssl_ctx) SSL_CTX_free(ssl_ctx);
    return REDIS_ERR;
}