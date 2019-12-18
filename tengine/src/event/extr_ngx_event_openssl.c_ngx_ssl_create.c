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
typedef  int ngx_uint_t ;
struct TYPE_3__ {int /*<<< orphan*/ * ctx; scalar_t__ async_enable; int /*<<< orphan*/  buffer_size; int /*<<< orphan*/  log; } ;
typedef  TYPE_1__ ngx_ssl_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  NGX_SSL_BUFSIZE ; 
 int NGX_SSL_SSLv2 ; 
 int NGX_SSL_SSLv3 ; 
 int NGX_SSL_TLSv1 ; 
 int NGX_SSL_TLSv1_1 ; 
 int NGX_SSL_TLSv1_2 ; 
 int NGX_SSL_TLSv1_3 ; 
 int /*<<< orphan*/  SSL_CTX_clear_options (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * SSL_CTX_new (int /*<<< orphan*/ ) ; 
 scalar_t__ SSL_CTX_set_ex_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  SSL_CTX_set_info_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_max_proto_version (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_min_proto_version (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_mode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_options (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SSL_CTX_set_read_ahead (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SSL_MODE_ASYNC ; 
 int /*<<< orphan*/  SSL_MODE_NO_AUTO_CHAIN ; 
 int /*<<< orphan*/  SSL_MODE_RELEASE_BUFFERS ; 
 int SSL_OP_DONT_INSERT_EMPTY_FRAGMENTS ; 
 int SSL_OP_MICROSOFT_BIG_SSLV3_BUFFER ; 
 int SSL_OP_MICROSOFT_SESS_ID_BUG ; 
 int SSL_OP_MSIE_SSLV2_RSA_PADDING ; 
 int SSL_OP_NETSCAPE_CHALLENGE_BUG ; 
 int SSL_OP_NO_ANTI_REPLAY ; 
 int SSL_OP_NO_CLIENT_RENEGOTIATION ; 
 int SSL_OP_NO_COMPRESSION ; 
 int SSL_OP_NO_SSLv2 ; 
 int SSL_OP_NO_SSLv3 ; 
 int SSL_OP_NO_TLSv1 ; 
 int SSL_OP_NO_TLSv1_1 ; 
 int SSL_OP_NO_TLSv1_2 ; 
 int SSL_OP_NO_TLSv1_3 ; 
 int SSL_OP_SINGLE_DH_USE ; 
 int SSL_OP_SSLEAY_080_CLIENT_DH_BUG ; 
 int SSL_OP_SSLREF2_REUSE_CERT_TYPE_BUG ; 
 int SSL_OP_TLS_BLOCK_PADDING_BUG ; 
 int SSL_OP_TLS_D5_BUG ; 
 int /*<<< orphan*/  SSLv23_method () ; 
 int /*<<< orphan*/  TLS1_2_VERSION ; 
 int /*<<< orphan*/  TLS1_3_VERSION ; 
 int /*<<< orphan*/  ngx_ssl_certificate_index ; 
 int /*<<< orphan*/  ngx_ssl_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_ssl_info_callback ; 
 int /*<<< orphan*/  ngx_ssl_server_conf_index ; 

ngx_int_t
ngx_ssl_create(ngx_ssl_t *ssl, ngx_uint_t protocols, void *data)
{
    ssl->ctx = SSL_CTX_new(SSLv23_method());

    if (ssl->ctx == NULL) {
        ngx_ssl_error(NGX_LOG_EMERG, ssl->log, 0, "SSL_CTX_new() failed");
        return NGX_ERROR;
    }

    if (SSL_CTX_set_ex_data(ssl->ctx, ngx_ssl_server_conf_index, data) == 0) {
        ngx_ssl_error(NGX_LOG_EMERG, ssl->log, 0,
                      "SSL_CTX_set_ex_data() failed");
        return NGX_ERROR;
    }

    if (SSL_CTX_set_ex_data(ssl->ctx, ngx_ssl_certificate_index, NULL) == 0) {
        ngx_ssl_error(NGX_LOG_EMERG, ssl->log, 0,
                      "SSL_CTX_set_ex_data() failed");
        return NGX_ERROR;
    }

    ssl->buffer_size = NGX_SSL_BUFSIZE;

    /* client side options */

#ifdef SSL_OP_MICROSOFT_SESS_ID_BUG
    SSL_CTX_set_options(ssl->ctx, SSL_OP_MICROSOFT_SESS_ID_BUG);
#endif

#ifdef SSL_OP_NETSCAPE_CHALLENGE_BUG
    SSL_CTX_set_options(ssl->ctx, SSL_OP_NETSCAPE_CHALLENGE_BUG);
#endif

    /* server side options */

#ifdef SSL_OP_SSLREF2_REUSE_CERT_TYPE_BUG
    SSL_CTX_set_options(ssl->ctx, SSL_OP_SSLREF2_REUSE_CERT_TYPE_BUG);
#endif

#ifdef SSL_OP_MICROSOFT_BIG_SSLV3_BUFFER
    SSL_CTX_set_options(ssl->ctx, SSL_OP_MICROSOFT_BIG_SSLV3_BUFFER);
#endif

#ifdef SSL_OP_MSIE_SSLV2_RSA_PADDING
    /* this option allow a potential SSL 2.0 rollback (CAN-2005-2969) */
    SSL_CTX_set_options(ssl->ctx, SSL_OP_MSIE_SSLV2_RSA_PADDING);
#endif

#ifdef SSL_OP_SSLEAY_080_CLIENT_DH_BUG
    SSL_CTX_set_options(ssl->ctx, SSL_OP_SSLEAY_080_CLIENT_DH_BUG);
#endif

#ifdef SSL_OP_TLS_D5_BUG
    SSL_CTX_set_options(ssl->ctx, SSL_OP_TLS_D5_BUG);
#endif

#ifdef SSL_OP_TLS_BLOCK_PADDING_BUG
    SSL_CTX_set_options(ssl->ctx, SSL_OP_TLS_BLOCK_PADDING_BUG);
#endif

#ifdef SSL_OP_DONT_INSERT_EMPTY_FRAGMENTS
    SSL_CTX_set_options(ssl->ctx, SSL_OP_DONT_INSERT_EMPTY_FRAGMENTS);
#endif

    SSL_CTX_set_options(ssl->ctx, SSL_OP_SINGLE_DH_USE);

#if OPENSSL_VERSION_NUMBER >= 0x009080dfL
    /* only in 0.9.8m+ */
    SSL_CTX_clear_options(ssl->ctx,
                          SSL_OP_NO_SSLv2|SSL_OP_NO_SSLv3|SSL_OP_NO_TLSv1);
#endif

    if (!(protocols & NGX_SSL_SSLv2)) {
        SSL_CTX_set_options(ssl->ctx, SSL_OP_NO_SSLv2);
    }
    if (!(protocols & NGX_SSL_SSLv3)) {
        SSL_CTX_set_options(ssl->ctx, SSL_OP_NO_SSLv3);
    }
    if (!(protocols & NGX_SSL_TLSv1)) {
        SSL_CTX_set_options(ssl->ctx, SSL_OP_NO_TLSv1);
    }
#ifdef SSL_OP_NO_TLSv1_1
    SSL_CTX_clear_options(ssl->ctx, SSL_OP_NO_TLSv1_1);
    if (!(protocols & NGX_SSL_TLSv1_1)) {
        SSL_CTX_set_options(ssl->ctx, SSL_OP_NO_TLSv1_1);
    }
#endif
#ifdef SSL_OP_NO_TLSv1_2
    SSL_CTX_clear_options(ssl->ctx, SSL_OP_NO_TLSv1_2);
    if (!(protocols & NGX_SSL_TLSv1_2)) {
        SSL_CTX_set_options(ssl->ctx, SSL_OP_NO_TLSv1_2);
    }
#endif
#ifdef SSL_OP_NO_TLSv1_3
    SSL_CTX_clear_options(ssl->ctx, SSL_OP_NO_TLSv1_3);
    if (!(protocols & NGX_SSL_TLSv1_3)) {
        SSL_CTX_set_options(ssl->ctx, SSL_OP_NO_TLSv1_3);
    }
#endif

#ifdef SSL_CTX_set_min_proto_version
    SSL_CTX_set_min_proto_version(ssl->ctx, 0);
    SSL_CTX_set_max_proto_version(ssl->ctx, TLS1_2_VERSION);
#endif

#ifdef TLS1_3_VERSION
    SSL_CTX_set_min_proto_version(ssl->ctx, 0);
    SSL_CTX_set_max_proto_version(ssl->ctx, TLS1_3_VERSION);
#endif

#ifdef SSL_OP_NO_COMPRESSION
    SSL_CTX_set_options(ssl->ctx, SSL_OP_NO_COMPRESSION);
#endif

#ifdef SSL_OP_NO_ANTI_REPLAY
    SSL_CTX_set_options(ssl->ctx, SSL_OP_NO_ANTI_REPLAY);
#endif

#ifdef SSL_OP_NO_CLIENT_RENEGOTIATION
    SSL_CTX_set_options(ssl->ctx, SSL_OP_NO_CLIENT_RENEGOTIATION);
#endif

#ifdef SSL_MODE_RELEASE_BUFFERS
    SSL_CTX_set_mode(ssl->ctx, SSL_MODE_RELEASE_BUFFERS);
#endif

#ifdef SSL_MODE_NO_AUTO_CHAIN
    SSL_CTX_set_mode(ssl->ctx, SSL_MODE_NO_AUTO_CHAIN);
#endif

#if (NGX_SSL && NGX_SSL_ASYNC)
    if (ssl->async_enable) {
        SSL_CTX_set_mode(ssl->ctx, SSL_MODE_ASYNC);
    }
#endif

    SSL_CTX_set_read_ahead(ssl->ctx, 1);

    SSL_CTX_set_info_callback(ssl->ctx, ngx_ssl_info_callback);

    return NGX_OK;
}