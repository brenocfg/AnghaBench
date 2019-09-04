#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_53__   TYPE_6__ ;
typedef  struct TYPE_52__   TYPE_5__ ;
typedef  struct TYPE_51__   TYPE_3__ ;
typedef  struct TYPE_50__   TYPE_2__ ;
typedef  struct TYPE_49__   TYPE_1__ ;
typedef  struct TYPE_48__   TYPE_13__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_str_t ;
struct TYPE_49__ {TYPE_5__* data; int /*<<< orphan*/  handler; } ;
typedef  TYPE_1__ ngx_pool_cleanup_t ;
struct TYPE_52__ {int /*<<< orphan*/  buffer_size; int /*<<< orphan*/  log; } ;
struct TYPE_53__ {scalar_t__ len; } ;
struct TYPE_50__ {scalar_t__ enable; int verify; int verify_depth; scalar_t__ early_data; TYPE_5__ ssl; scalar_t__ stapling_verify; TYPE_6__ stapling_responder; TYPE_6__ stapling_file; scalar_t__ stapling; TYPE_13__* session_ticket_keys; scalar_t__ session_tickets; scalar_t__ session_timeout; int /*<<< orphan*/ * shm_zone; scalar_t__ builtin_session_cache; TYPE_13__* certificates; TYPE_6__ ecdh_curve; TYPE_6__ dhparam; TYPE_6__ crl; TYPE_6__ trusted_certificate; TYPE_6__ client_certificate; int /*<<< orphan*/  buffer_size; scalar_t__ prefer_server_ciphers; TYPE_6__ ciphers; TYPE_13__* passwords; TYPE_13__* certificate_keys; scalar_t__ certificate_values; int /*<<< orphan*/  protocols; int /*<<< orphan*/  line; int /*<<< orphan*/  file; } ;
typedef  TYPE_2__ ngx_http_ssl_srv_conf_t ;
struct TYPE_51__ {int /*<<< orphan*/  log; int /*<<< orphan*/  pool; } ;
typedef  TYPE_3__ ngx_conf_t ;
struct TYPE_48__ {scalar_t__ nelts; scalar_t__ elts; } ;

/* Variables and functions */
 int NGX_CONF_BITMASK_SET ; 
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_CONF_UNSET ; 
 char* NGX_DEFAULT_CIPHERS ; 
 char* NGX_DEFAULT_ECDH_CURVE ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  NGX_SSL_BUFSIZE ; 
 int NGX_SSL_NONE_SCACHE ; 
 int NGX_SSL_TLSv1 ; 
 int NGX_SSL_TLSv1_1 ; 
 int NGX_SSL_TLSv1_2 ; 
 int /*<<< orphan*/  ngx_conf_merge_bitmask_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_conf_merge_ptr_value (TYPE_13__*,TYPE_13__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_conf_merge_size_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_conf_merge_str_value (TYPE_6__,TYPE_6__,char*) ; 
 int /*<<< orphan*/  ngx_conf_merge_uint_value (int,int,int) ; 
 int /*<<< orphan*/  ngx_conf_merge_value (scalar_t__,scalar_t__,int) ; 
 scalar_t__ ngx_http_ssl_compile_certificates (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_http_ssl_sess_id_ctx ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_1__* ngx_pool_cleanup_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_ssl_certificates (TYPE_3__*,TYPE_5__*,TYPE_13__*,TYPE_13__*,TYPE_13__*) ; 
 scalar_t__ ngx_ssl_ciphers (TYPE_3__*,TYPE_5__*,TYPE_6__*,scalar_t__) ; 
 int /*<<< orphan*/  ngx_ssl_cleanup_ctx ; 
 scalar_t__ ngx_ssl_client_certificate (TYPE_3__*,TYPE_5__*,TYPE_6__*,int) ; 
 scalar_t__ ngx_ssl_create (TYPE_5__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ ngx_ssl_crl (TYPE_3__*,TYPE_5__*,TYPE_6__*) ; 
 scalar_t__ ngx_ssl_dhparam (TYPE_3__*,TYPE_5__*,TYPE_6__*) ; 
 scalar_t__ ngx_ssl_early_data (TYPE_3__*,TYPE_5__*,scalar_t__) ; 
 scalar_t__ ngx_ssl_ecdh_curve (TYPE_3__*,TYPE_5__*,TYPE_6__*) ; 
 scalar_t__ ngx_ssl_session_cache (TYPE_5__*,int /*<<< orphan*/ *,TYPE_13__*,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ngx_ssl_session_ticket_keys (TYPE_3__*,TYPE_5__*,TYPE_13__*) ; 
 scalar_t__ ngx_ssl_stapling (TYPE_3__*,TYPE_5__*,TYPE_6__*,TYPE_6__*,scalar_t__) ; 
 scalar_t__ ngx_ssl_trusted_certificate (TYPE_3__*,TYPE_5__*,TYPE_6__*,int) ; 

__attribute__((used)) static char *
ngx_http_ssl_merge_srv_conf(ngx_conf_t *cf, void *parent, void *child)
{
    ngx_http_ssl_srv_conf_t *prev = parent;
    ngx_http_ssl_srv_conf_t *conf = child;

    ngx_pool_cleanup_t  *cln;

    if (conf->enable == NGX_CONF_UNSET) {
        if (prev->enable == NGX_CONF_UNSET) {
            conf->enable = 0;

        } else {
            conf->enable = prev->enable;
            conf->file = prev->file;
            conf->line = prev->line;
        }
    }

#if (NGX_HTTP_SSL && NGX_SSL_ASYNC)
    if (conf->async_enable == NGX_CONF_UNSET) {
        if (prev->async_enable == NGX_CONF_UNSET) {
            conf->async_enable = 0;

        } else {
            conf->async_enable = prev->async_enable;
            conf->file = prev->file;
            conf->line = prev->line;
        }
    }
#endif
    ngx_conf_merge_value(conf->session_timeout,
                         prev->session_timeout, 300);

    ngx_conf_merge_value(conf->prefer_server_ciphers,
                         prev->prefer_server_ciphers, 0);

    ngx_conf_merge_value(conf->early_data, prev->early_data, 0);

    ngx_conf_merge_bitmask_value(conf->protocols, prev->protocols,
                         (NGX_CONF_BITMASK_SET|NGX_SSL_TLSv1
                          |NGX_SSL_TLSv1_1|NGX_SSL_TLSv1_2));

    ngx_conf_merge_size_value(conf->buffer_size, prev->buffer_size,
                         NGX_SSL_BUFSIZE);

    ngx_conf_merge_uint_value(conf->verify, prev->verify, 0);
    ngx_conf_merge_uint_value(conf->verify_depth, prev->verify_depth, 1);

    ngx_conf_merge_ptr_value(conf->certificates, prev->certificates, NULL);
    ngx_conf_merge_ptr_value(conf->certificate_keys, prev->certificate_keys,
                         NULL);

    ngx_conf_merge_ptr_value(conf->passwords, prev->passwords, NULL);

    ngx_conf_merge_str_value(conf->dhparam, prev->dhparam, "");

    ngx_conf_merge_str_value(conf->client_certificate, prev->client_certificate,
                         "");
    ngx_conf_merge_str_value(conf->trusted_certificate,
                         prev->trusted_certificate, "");
    ngx_conf_merge_str_value(conf->crl, prev->crl, "");

    ngx_conf_merge_str_value(conf->ecdh_curve, prev->ecdh_curve,
                         NGX_DEFAULT_ECDH_CURVE);

    ngx_conf_merge_str_value(conf->ciphers, prev->ciphers, NGX_DEFAULT_CIPHERS);

    ngx_conf_merge_value(conf->stapling, prev->stapling, 0);
    ngx_conf_merge_value(conf->stapling_verify, prev->stapling_verify, 0);
    ngx_conf_merge_str_value(conf->stapling_file, prev->stapling_file, "");
    ngx_conf_merge_str_value(conf->stapling_responder,
                         prev->stapling_responder, "");

    conf->ssl.log = cf->log;

    if (conf->enable) {

        if (conf->certificates == NULL) {
            ngx_log_error(NGX_LOG_EMERG, cf->log, 0,
                          "no \"ssl_certificate\" is defined for "
                          "the \"ssl\" directive in %s:%ui",
                          conf->file, conf->line);
            return NGX_CONF_ERROR;
        }

        if (conf->certificate_keys == NULL) {
            ngx_log_error(NGX_LOG_EMERG, cf->log, 0,
                          "no \"ssl_certificate_key\" is defined for "
                          "the \"ssl\" directive in %s:%ui",
                          conf->file, conf->line);
            return NGX_CONF_ERROR;
        }
#if (NGX_HTTP_SSL && NGX_SSL_ASYNC)
        conf->ssl.async_enable = conf->async_enable;
#endif

        if (conf->certificate_keys->nelts < conf->certificates->nelts) {
            ngx_log_error(NGX_LOG_EMERG, cf->log, 0,
                          "no \"ssl_certificate_key\" is defined "
                          "for certificate \"%V\" and "
                          "the \"ssl\" directive in %s:%ui",
                          ((ngx_str_t *) conf->certificates->elts)
                          + conf->certificates->nelts - 1,
                          conf->file, conf->line);
            return NGX_CONF_ERROR;
        }

    } else {

        if (conf->certificates == NULL) {
            return NGX_CONF_OK;
        }

        if (conf->certificate_keys == NULL
            || conf->certificate_keys->nelts < conf->certificates->nelts)
        {
            ngx_log_error(NGX_LOG_EMERG, cf->log, 0,
                          "no \"ssl_certificate_key\" is defined "
                          "for certificate \"%V\"",
                          ((ngx_str_t *) conf->certificates->elts)
                          + conf->certificates->nelts - 1);
            return NGX_CONF_ERROR;
        }
    }

    if (ngx_ssl_create(&conf->ssl, conf->protocols, conf) != NGX_OK) {
        return NGX_CONF_ERROR;
    }

#ifdef SSL_CTRL_SET_TLSEXT_HOSTNAME

    if (SSL_CTX_set_tlsext_servername_callback(conf->ssl.ctx,
                                               ngx_http_ssl_servername)
        == 0)
    {
        ngx_log_error(NGX_LOG_WARN, cf->log, 0,
            "nginx was built with SNI support, however, now it is linked "
            "dynamically to an OpenSSL library which has no tlsext support, "
            "therefore SNI is not available");
    }

#endif

#ifdef TLSEXT_TYPE_application_layer_protocol_negotiation
    SSL_CTX_set_alpn_select_cb(conf->ssl.ctx, ngx_http_ssl_alpn_select, NULL);
#endif

#ifdef TLSEXT_TYPE_next_proto_neg
    SSL_CTX_set_next_protos_advertised_cb(conf->ssl.ctx,
                                          ngx_http_ssl_npn_advertised, NULL);
#endif

    cln = ngx_pool_cleanup_add(cf->pool, 0);
    if (cln == NULL) {
        return NGX_CONF_ERROR;
    }

    cln->handler = ngx_ssl_cleanup_ctx;
    cln->data = &conf->ssl;

    if (ngx_http_ssl_compile_certificates(cf, conf) != NGX_OK) {
        return NGX_CONF_ERROR;
    }

    if (conf->certificate_values) {

#ifdef SSL_R_CERT_CB_ERROR

        /* install callback to lookup certificates */

        SSL_CTX_set_cert_cb(conf->ssl.ctx, ngx_http_ssl_certificate, conf);

#else
        ngx_log_error(NGX_LOG_EMERG, cf->log, 0,
                      "variables in "
                      "\"ssl_certificate\" and \"ssl_certificate_key\" "
                      "directives are not supported on this platform");
        return NGX_CONF_ERROR;
#endif

    } else {

        /* configure certificates */

        if (ngx_ssl_certificates(cf, &conf->ssl, conf->certificates,
                                 conf->certificate_keys, conf->passwords)
            != NGX_OK)
        {
            return NGX_CONF_ERROR;
        }
    }

    if (ngx_ssl_ciphers(cf, &conf->ssl, &conf->ciphers,
                        conf->prefer_server_ciphers)
        != NGX_OK)
    {
        return NGX_CONF_ERROR;
    }

    conf->ssl.buffer_size = conf->buffer_size;

    if (conf->verify) {

        if (conf->client_certificate.len == 0 && conf->verify != 3) {
            ngx_log_error(NGX_LOG_EMERG, cf->log, 0,
                          "no ssl_client_certificate for ssl_client_verify");
            return NGX_CONF_ERROR;
        }

        if (ngx_ssl_client_certificate(cf, &conf->ssl,
                                       &conf->client_certificate,
                                       conf->verify_depth)
            != NGX_OK)
        {
            return NGX_CONF_ERROR;
        }
    }

    if (ngx_ssl_trusted_certificate(cf, &conf->ssl,
                                    &conf->trusted_certificate,
                                    conf->verify_depth)
        != NGX_OK)
    {
        return NGX_CONF_ERROR;
    }

    if (ngx_ssl_crl(cf, &conf->ssl, &conf->crl) != NGX_OK) {
        return NGX_CONF_ERROR;
    }

    if (ngx_ssl_dhparam(cf, &conf->ssl, &conf->dhparam) != NGX_OK) {
        return NGX_CONF_ERROR;
    }

    if (ngx_ssl_ecdh_curve(cf, &conf->ssl, &conf->ecdh_curve) != NGX_OK) {
        return NGX_CONF_ERROR;
    }

    ngx_conf_merge_value(conf->builtin_session_cache,
                         prev->builtin_session_cache, NGX_SSL_NONE_SCACHE);

    if (conf->shm_zone == NULL) {
        conf->shm_zone = prev->shm_zone;
    }

    if (ngx_ssl_session_cache(&conf->ssl, &ngx_http_ssl_sess_id_ctx,
                              conf->certificates, conf->builtin_session_cache,
                              conf->shm_zone, conf->session_timeout)
        != NGX_OK)
    {
        return NGX_CONF_ERROR;
    }

    ngx_conf_merge_value(conf->session_tickets, prev->session_tickets, 1);

#ifdef SSL_OP_NO_TICKET
    if (!conf->session_tickets) {
        SSL_CTX_set_options(conf->ssl.ctx, SSL_OP_NO_TICKET);
    }
#endif

    ngx_conf_merge_ptr_value(conf->session_ticket_keys,
                         prev->session_ticket_keys, NULL);

    if (ngx_ssl_session_ticket_keys(cf, &conf->ssl, conf->session_ticket_keys)
        != NGX_OK)
    {
        return NGX_CONF_ERROR;
    }

    if (conf->stapling) {

        if (ngx_ssl_stapling(cf, &conf->ssl, &conf->stapling_file,
                             &conf->stapling_responder, conf->stapling_verify)
            != NGX_OK)
        {
            return NGX_CONF_ERROR;
        }

    }

    if (ngx_ssl_early_data(cf, &conf->ssl, conf->early_data) != NGX_OK) {
        return NGX_CONF_ERROR;
    }

    return NGX_CONF_OK;
}