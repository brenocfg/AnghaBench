#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  c; } ;
typedef  TYPE_1__ redisAsyncContext ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int C_ERR ; 
 int C_OK ; 
 scalar_t__ REDIS_ERR ; 
 int /*<<< orphan*/ * SSL_new (int /*<<< orphan*/ ) ; 
 scalar_t__ redisInitiateSSL (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  redis_tls_ctx ; 

__attribute__((used)) static int instanceLinkNegotiateTLS(redisAsyncContext *context) {
#ifndef USE_OPENSSL
    (void) context;
#else
    if (!redis_tls_ctx) return C_ERR;
    SSL *ssl = SSL_new(redis_tls_ctx);
    if (!ssl) return C_ERR;

    if (redisInitiateSSL(&context->c, ssl) == REDIS_ERR) return C_ERR;
#endif
    return C_OK;
}