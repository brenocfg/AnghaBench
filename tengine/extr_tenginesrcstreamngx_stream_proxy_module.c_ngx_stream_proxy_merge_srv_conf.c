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
struct TYPE_2__ {int /*<<< orphan*/  socket_keepalive; int /*<<< orphan*/  local; int /*<<< orphan*/  proxy_protocol; int /*<<< orphan*/  next_upstream; int /*<<< orphan*/  next_upstream_tries; int /*<<< orphan*/  responses; int /*<<< orphan*/  requests; int /*<<< orphan*/  download_rate; int /*<<< orphan*/  upload_rate; int /*<<< orphan*/  buffer_size; int /*<<< orphan*/  next_upstream_timeout; int /*<<< orphan*/  timeout; int /*<<< orphan*/  connect_timeout; } ;
typedef  TYPE_1__ ngx_stream_proxy_srv_conf_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;

/* Variables and functions */
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/  NGX_MAX_INT32_VALUE ; 
 int /*<<< orphan*/  ngx_conf_merge_msec_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_conf_merge_ptr_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_conf_merge_size_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_conf_merge_uint_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_conf_merge_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static char *
ngx_stream_proxy_merge_srv_conf(ngx_conf_t *cf, void *parent, void *child)
{
    ngx_stream_proxy_srv_conf_t *prev = parent;
    ngx_stream_proxy_srv_conf_t *conf = child;

    ngx_conf_merge_msec_value(conf->connect_timeout,
                              prev->connect_timeout, 60000);

    ngx_conf_merge_msec_value(conf->timeout,
                              prev->timeout, 10 * 60000);

    ngx_conf_merge_msec_value(conf->next_upstream_timeout,
                              prev->next_upstream_timeout, 0);

    ngx_conf_merge_size_value(conf->buffer_size,
                              prev->buffer_size, 16384);

    ngx_conf_merge_size_value(conf->upload_rate,
                              prev->upload_rate, 0);

    ngx_conf_merge_size_value(conf->download_rate,
                              prev->download_rate, 0);

    ngx_conf_merge_uint_value(conf->requests,
                              prev->requests, 0);

    ngx_conf_merge_uint_value(conf->responses,
                              prev->responses, NGX_MAX_INT32_VALUE);

    ngx_conf_merge_uint_value(conf->next_upstream_tries,
                              prev->next_upstream_tries, 0);

    ngx_conf_merge_value(conf->next_upstream, prev->next_upstream, 1);

    ngx_conf_merge_value(conf->proxy_protocol, prev->proxy_protocol, 0);

    ngx_conf_merge_ptr_value(conf->local, prev->local, NULL);

    ngx_conf_merge_value(conf->socket_keepalive,
                              prev->socket_keepalive, 0);

#if (NGX_STREAM_SSL)

    ngx_conf_merge_value(conf->ssl_enable, prev->ssl_enable, 0);

    ngx_conf_merge_value(conf->ssl_session_reuse,
                              prev->ssl_session_reuse, 1);

    ngx_conf_merge_bitmask_value(conf->ssl_protocols, prev->ssl_protocols,
                              (NGX_CONF_BITMASK_SET|NGX_SSL_TLSv1
                               |NGX_SSL_TLSv1_1|NGX_SSL_TLSv1_2));

    ngx_conf_merge_str_value(conf->ssl_ciphers, prev->ssl_ciphers, "DEFAULT");

    if (conf->ssl_name == NULL) {
        conf->ssl_name = prev->ssl_name;
    }

    ngx_conf_merge_value(conf->ssl_server_name, prev->ssl_server_name, 0);

    ngx_conf_merge_value(conf->ssl_verify, prev->ssl_verify, 0);

    ngx_conf_merge_uint_value(conf->ssl_verify_depth,
                              prev->ssl_verify_depth, 1);

    ngx_conf_merge_str_value(conf->ssl_trusted_certificate,
                              prev->ssl_trusted_certificate, "");

    ngx_conf_merge_str_value(conf->ssl_crl, prev->ssl_crl, "");

    ngx_conf_merge_str_value(conf->ssl_certificate,
                              prev->ssl_certificate, "");

    ngx_conf_merge_str_value(conf->ssl_certificate_key,
                              prev->ssl_certificate_key, "");

    ngx_conf_merge_ptr_value(conf->ssl_passwords, prev->ssl_passwords, NULL);

    if (conf->ssl_enable && ngx_stream_proxy_set_ssl(cf, conf) != NGX_OK) {
        return NGX_CONF_ERROR;
    }

#endif

    return NGX_CONF_OK;
}