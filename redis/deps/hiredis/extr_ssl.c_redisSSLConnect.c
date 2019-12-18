#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * ssl; int /*<<< orphan*/ * ssl_ctx; } ;
typedef  TYPE_1__ redisSSLContext ;
struct TYPE_7__ {int flags; scalar_t__ err; int /*<<< orphan*/  fd; TYPE_1__* privdata; int /*<<< orphan*/ * funcs; } ;
typedef  TYPE_2__ redisContext ;
typedef  int /*<<< orphan*/  err ;
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_clear_error () ; 
 unsigned long ERR_peek_last_error () ; 
 char* ERR_reason_error_string (unsigned long) ; 
 int REDIS_BLOCK ; 
 int REDIS_ERR ; 
 int /*<<< orphan*/  REDIS_ERR_IO ; 
 int /*<<< orphan*/  REDIS_ERR_OTHER ; 
 int REDIS_OK ; 
 int SSL_ERROR_SYSCALL ; 
 int SSL_ERROR_WANT_READ ; 
 int SSL_ERROR_WANT_WRITE ; 
 int /*<<< orphan*/  SSL_MODE_ACCEPT_MOVING_WRITE_BUFFER ; 
 int SSL_connect (int /*<<< orphan*/ *) ; 
 int SSL_get_error (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SSL_set_connect_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set_fd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_set_mode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __redisSetError (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  redisContextSSLFuncs ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int redisSSLConnect(redisContext *c, SSL_CTX *ssl_ctx, SSL *ssl) {
    if (c->privdata) {
        __redisSetError(c, REDIS_ERR_OTHER, "redisContext was already associated");
        return REDIS_ERR;
    }
    c->privdata = calloc(1, sizeof(redisSSLContext));

    c->funcs = &redisContextSSLFuncs;
    redisSSLContext *rssl = c->privdata;

    rssl->ssl_ctx = ssl_ctx;
    rssl->ssl = ssl;

    SSL_set_mode(rssl->ssl, SSL_MODE_ACCEPT_MOVING_WRITE_BUFFER);
    SSL_set_fd(rssl->ssl, c->fd);
    SSL_set_connect_state(rssl->ssl);

    ERR_clear_error();
    int rv = SSL_connect(rssl->ssl);
    if (rv == 1) {
        return REDIS_OK;
    }

    rv = SSL_get_error(rssl->ssl, rv);
    if (((c->flags & REDIS_BLOCK) == 0) &&
        (rv == SSL_ERROR_WANT_READ || rv == SSL_ERROR_WANT_WRITE)) {
        return REDIS_OK;
    }

    if (c->err == 0) {
        char err[512];
        if (rv == SSL_ERROR_SYSCALL)
            snprintf(err,sizeof(err)-1,"SSL_connect failed: %s",strerror(errno));
        else {
            unsigned long e = ERR_peek_last_error();
            snprintf(err,sizeof(err)-1,"SSL_connect failed: %s",
                    ERR_reason_error_string(e));
        }
        __redisSetError(c, REDIS_ERR_IO, err);
    }
    return REDIS_ERR;
}