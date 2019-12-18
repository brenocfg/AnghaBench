#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
struct TYPE_17__ {int verify; } ;
typedef  TYPE_4__ ngx_http_ssl_srv_conf_t ;
struct TYPE_18__ {int stat_writing; int /*<<< orphan*/  read_event_handler; scalar_t__ stat_reading; TYPE_1__* http_connection; TYPE_6__* connection; } ;
typedef  TYPE_5__ ngx_http_request_t ;
struct TYPE_19__ {TYPE_3__* write; TYPE_12__* read; TYPE_2__* ssl; int /*<<< orphan*/  log; } ;
typedef  TYPE_6__ ngx_connection_t ;
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_16__ {void* handler; } ;
struct TYPE_15__ {int /*<<< orphan*/  connection; int /*<<< orphan*/  session_ctx; } ;
struct TYPE_14__ {scalar_t__ ssl; } ;
struct TYPE_13__ {void* handler; scalar_t__ timer_set; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_HTTPS_CERT_ERROR ; 
 int /*<<< orphan*/  NGX_HTTPS_NO_CERT ; 
 int /*<<< orphan*/  NGX_HTTP_TO_HTTPS ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 int /*<<< orphan*/  SSL_get0_session (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SSL_get_peer_certificate (int /*<<< orphan*/ ) ; 
 long SSL_get_verify_result (int /*<<< orphan*/ ) ; 
 long X509_V_OK ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_verify_cert_error_string (long) ; 
 int /*<<< orphan*/  ngx_atomic_fetch_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_del_timer (TYPE_12__*) ; 
 int /*<<< orphan*/  ngx_http_block_reading ; 
 int /*<<< orphan*/  ngx_http_finalize_request (TYPE_5__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* ngx_http_get_module_srv_conf (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_handler (TYPE_5__*) ; 
 void* ngx_http_request_handler ; 
 int /*<<< orphan*/  ngx_http_ssl_module ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ngx_ssl_remove_cached_session (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_ssl_verify_error_optional (long) ; 
 int /*<<< orphan*/  ngx_stat_reading ; 
 int /*<<< orphan*/  ngx_stat_writing ; 

void
ngx_http_process_request(ngx_http_request_t *r)
{
    ngx_connection_t  *c;

    c = r->connection;

#if (NGX_HTTP_SSL && !T_NGX_HTTP_SSL_VCE)

    if (r->http_connection->ssl) {
        long                      rc;
        X509                     *cert;
        ngx_http_ssl_srv_conf_t  *sscf;

        if (c->ssl == NULL) {
            ngx_log_error(NGX_LOG_INFO, c->log, 0,
                          "client sent plain HTTP request to HTTPS port");
            ngx_http_finalize_request(r, NGX_HTTP_TO_HTTPS);
            return;
        }

        sscf = ngx_http_get_module_srv_conf(r, ngx_http_ssl_module);

        if (sscf->verify) {
            rc = SSL_get_verify_result(c->ssl->connection);

            if (rc != X509_V_OK
                && (sscf->verify != 3 || !ngx_ssl_verify_error_optional(rc)))
            {
                ngx_log_error(NGX_LOG_INFO, c->log, 0,
                              "client SSL certificate verify error: (%l:%s)",
                              rc, X509_verify_cert_error_string(rc));

                ngx_ssl_remove_cached_session(c->ssl->session_ctx,
                                       (SSL_get0_session(c->ssl->connection)));

                ngx_http_finalize_request(r, NGX_HTTPS_CERT_ERROR);
                return;
            }

            if (sscf->verify == 1) {
                cert = SSL_get_peer_certificate(c->ssl->connection);

                if (cert == NULL) {
                    ngx_log_error(NGX_LOG_INFO, c->log, 0,
                                  "client sent no required SSL certificate");

                    ngx_ssl_remove_cached_session(c->ssl->session_ctx,
                                       (SSL_get0_session(c->ssl->connection)));

                    ngx_http_finalize_request(r, NGX_HTTPS_NO_CERT);
                    return;
                }

                X509_free(cert);
            }
        }
    }

#endif

    if (c->read->timer_set) {
        ngx_del_timer(c->read);
    }

#if (NGX_STAT_STUB)
    (void) ngx_atomic_fetch_add(ngx_stat_reading, -1);
    r->stat_reading = 0;
    (void) ngx_atomic_fetch_add(ngx_stat_writing, 1);
    r->stat_writing = 1;
#endif

    c->read->handler = ngx_http_request_handler;
    c->write->handler = ngx_http_request_handler;
    r->read_event_handler = ngx_http_block_reading;

    ngx_http_handler(r);
}