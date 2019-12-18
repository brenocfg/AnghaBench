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
typedef  int /*<<< orphan*/  ngx_log_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_clear_error () ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  OPENSSL_INIT_LOAD_CONFIG ; 
 int /*<<< orphan*/  OPENSSL_config (int /*<<< orphan*/ *) ; 
 scalar_t__ OPENSSL_init_ssl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OpenSSL_add_all_algorithms () ; 
 int /*<<< orphan*/  SSL_COMP ; 
 int SSL_COMP_get_compression_methods () ; 
 int SSL_CTX_get_ex_new_index (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int SSL_get_ex_new_index (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_library_init () ; 
 int /*<<< orphan*/  SSL_load_error_strings () ; 
 int STACK_OF (int /*<<< orphan*/ ) ; 
 int X509_get_ex_new_index (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ngx_ssl_certificate_index ; 
 int ngx_ssl_certificate_name_index ; 
 int ngx_ssl_connection_index ; 
 int /*<<< orphan*/  ngx_ssl_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int ngx_ssl_next_certificate_index ; 
 int ngx_ssl_server_conf_index ; 
 int ngx_ssl_session_cache_index ; 
 int ngx_ssl_session_ticket_keys_index ; 
 int ngx_ssl_stapling_index ; 
 int sk_SSL_COMP_num (int) ; 
 int /*<<< orphan*/  sk_SSL_COMP_pop (int) ; 
 int ssl_comp_methods ; 

ngx_int_t
ngx_ssl_init(ngx_log_t *log)
{
#if OPENSSL_VERSION_NUMBER >= 0x10100003L

    if (OPENSSL_init_ssl(OPENSSL_INIT_LOAD_CONFIG, NULL) == 0) {
        ngx_ssl_error(NGX_LOG_ALERT, log, 0, "OPENSSL_init_ssl() failed");
        return NGX_ERROR;
    }

    /*
     * OPENSSL_init_ssl() may leave errors in the error queue
     * while returning success
     */

    ERR_clear_error();

#else

    OPENSSL_config(NULL);

    SSL_library_init();
    SSL_load_error_strings();

    OpenSSL_add_all_algorithms();

#endif

#ifndef SSL_OP_NO_COMPRESSION
    {
    /*
     * Disable gzip compression in OpenSSL prior to 1.0.0 version,
     * this saves about 522K per connection.
     */
    int                  n;
    STACK_OF(SSL_COMP)  *ssl_comp_methods;

    ssl_comp_methods = SSL_COMP_get_compression_methods();
    n = sk_SSL_COMP_num(ssl_comp_methods);

    while (n--) {
        (void) sk_SSL_COMP_pop(ssl_comp_methods);
    }
    }
#endif

    ngx_ssl_connection_index = SSL_get_ex_new_index(0, NULL, NULL, NULL, NULL);

    if (ngx_ssl_connection_index == -1) {
        ngx_ssl_error(NGX_LOG_ALERT, log, 0, "SSL_get_ex_new_index() failed");
        return NGX_ERROR;
    }

    ngx_ssl_server_conf_index = SSL_CTX_get_ex_new_index(0, NULL, NULL, NULL,
                                                         NULL);
    if (ngx_ssl_server_conf_index == -1) {
        ngx_ssl_error(NGX_LOG_ALERT, log, 0,
                      "SSL_CTX_get_ex_new_index() failed");
        return NGX_ERROR;
    }

    ngx_ssl_session_cache_index = SSL_CTX_get_ex_new_index(0, NULL, NULL, NULL,
                                                           NULL);
    if (ngx_ssl_session_cache_index == -1) {
        ngx_ssl_error(NGX_LOG_ALERT, log, 0,
                      "SSL_CTX_get_ex_new_index() failed");
        return NGX_ERROR;
    }

    ngx_ssl_session_ticket_keys_index = SSL_CTX_get_ex_new_index(0, NULL, NULL,
                                                                 NULL, NULL);
    if (ngx_ssl_session_ticket_keys_index == -1) {
        ngx_ssl_error(NGX_LOG_ALERT, log, 0,
                      "SSL_CTX_get_ex_new_index() failed");
        return NGX_ERROR;
    }

    ngx_ssl_certificate_index = SSL_CTX_get_ex_new_index(0, NULL, NULL, NULL,
                                                         NULL);
    if (ngx_ssl_certificate_index == -1) {
        ngx_ssl_error(NGX_LOG_ALERT, log, 0,
                      "SSL_CTX_get_ex_new_index() failed");
        return NGX_ERROR;
    }

    ngx_ssl_next_certificate_index = X509_get_ex_new_index(0, NULL, NULL, NULL,
                                                           NULL);
    if (ngx_ssl_next_certificate_index == -1) {
        ngx_ssl_error(NGX_LOG_ALERT, log, 0, "X509_get_ex_new_index() failed");
        return NGX_ERROR;
    }

    ngx_ssl_certificate_name_index = X509_get_ex_new_index(0, NULL, NULL, NULL,
                                                           NULL);

    if (ngx_ssl_certificate_name_index == -1) {
        ngx_ssl_error(NGX_LOG_ALERT, log, 0, "X509_get_ex_new_index() failed");
        return NGX_ERROR;
    }

    ngx_ssl_stapling_index = X509_get_ex_new_index(0, NULL, NULL, NULL, NULL);

    if (ngx_ssl_stapling_index == -1) {
        ngx_ssl_error(NGX_LOG_ALERT, log, 0, "X509_get_ex_new_index() failed");
        return NGX_ERROR;
    }

    return NGX_OK;
}