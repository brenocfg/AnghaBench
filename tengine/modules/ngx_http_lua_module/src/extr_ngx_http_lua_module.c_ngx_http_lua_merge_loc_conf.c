#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_9__ ;
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_13__ ;
typedef  struct TYPE_17__   TYPE_12__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ len; } ;
struct TYPE_17__ {TYPE_11__ value; } ;
struct TYPE_27__ {scalar_t__ len; } ;
struct TYPE_15__ {TYPE_9__ value; } ;
struct TYPE_25__ {scalar_t__ len; } ;
struct TYPE_26__ {TYPE_7__ value; } ;
struct TYPE_23__ {scalar_t__ len; } ;
struct TYPE_24__ {TYPE_5__ value; } ;
struct TYPE_21__ {scalar_t__ len; } ;
struct TYPE_22__ {TYPE_3__ value; } ;
struct TYPE_19__ {scalar_t__ len; } ;
struct TYPE_20__ {TYPE_1__ value; } ;
struct TYPE_18__ {int /*<<< orphan*/  log_socket_errors; int /*<<< orphan*/  transform_underscores_in_resp_headers; int /*<<< orphan*/  pool_size; int /*<<< orphan*/  buffer_size; int /*<<< orphan*/  send_lowat; int /*<<< orphan*/  read_timeout; int /*<<< orphan*/  send_timeout; int /*<<< orphan*/  connect_timeout; int /*<<< orphan*/  keepalive_timeout; int /*<<< orphan*/  use_default_type; int /*<<< orphan*/  check_client_abort; int /*<<< orphan*/  http10_buffering; int /*<<< orphan*/  enable_code_cache; int /*<<< orphan*/  force_read_body; int /*<<< orphan*/  ssl_crl; int /*<<< orphan*/  ssl_trusted_certificate; int /*<<< orphan*/  ssl_verify_depth; int /*<<< orphan*/  ssl_ciphers; int /*<<< orphan*/  ssl_protocols; int /*<<< orphan*/  body_filter_src_key; int /*<<< orphan*/  body_filter_handler; TYPE_12__ body_filter_src; int /*<<< orphan*/  header_filter_src_key; int /*<<< orphan*/  header_filter_handler; TYPE_10__ header_filter_src; int /*<<< orphan*/  log_chunkname; int /*<<< orphan*/  log_src_key; int /*<<< orphan*/  log_handler; TYPE_8__ log_src; int /*<<< orphan*/  content_chunkname; int /*<<< orphan*/  content_src_key; int /*<<< orphan*/  content_handler; TYPE_6__ content_src; int /*<<< orphan*/  access_chunkname; int /*<<< orphan*/  access_src_key; int /*<<< orphan*/  access_handler; TYPE_4__ access_src; int /*<<< orphan*/  rewrite_chunkname; int /*<<< orphan*/  rewrite_src_key; int /*<<< orphan*/  rewrite_handler; TYPE_2__ rewrite_src; } ;
typedef  TYPE_13__ ngx_http_lua_loc_conf_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;

/* Variables and functions */
 int NGX_CONF_BITMASK_SET ; 
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_OK ; 
 int NGX_SSL_SSLv3 ; 
 int NGX_SSL_TLSv1 ; 
 int NGX_SSL_TLSv1_1 ; 
 int NGX_SSL_TLSv1_2 ; 
 int /*<<< orphan*/  ngx_conf_merge_bitmask_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_conf_merge_msec_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_conf_merge_size_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ngx_conf_merge_str_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_conf_merge_uint_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_conf_merge_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ngx_http_lua_set_ssl (int /*<<< orphan*/ *,TYPE_13__*) ; 
 scalar_t__ ngx_pagesize ; 

__attribute__((used)) static char *
ngx_http_lua_merge_loc_conf(ngx_conf_t *cf, void *parent, void *child)
{
    ngx_http_lua_loc_conf_t *prev = parent;
    ngx_http_lua_loc_conf_t *conf = child;

    if (conf->rewrite_src.value.len == 0) {
        conf->rewrite_src = prev->rewrite_src;
        conf->rewrite_handler = prev->rewrite_handler;
        conf->rewrite_src_key = prev->rewrite_src_key;
        conf->rewrite_chunkname = prev->rewrite_chunkname;
    }

    if (conf->access_src.value.len == 0) {
        conf->access_src = prev->access_src;
        conf->access_handler = prev->access_handler;
        conf->access_src_key = prev->access_src_key;
        conf->access_chunkname = prev->access_chunkname;
    }

    if (conf->content_src.value.len == 0) {
        conf->content_src = prev->content_src;
        conf->content_handler = prev->content_handler;
        conf->content_src_key = prev->content_src_key;
        conf->content_chunkname = prev->content_chunkname;
    }

    if (conf->log_src.value.len == 0) {
        conf->log_src = prev->log_src;
        conf->log_handler = prev->log_handler;
        conf->log_src_key = prev->log_src_key;
        conf->log_chunkname = prev->log_chunkname;
    }

    if (conf->header_filter_src.value.len == 0) {
        conf->header_filter_src = prev->header_filter_src;
        conf->header_filter_handler = prev->header_filter_handler;
        conf->header_filter_src_key = prev->header_filter_src_key;
    }

    if (conf->body_filter_src.value.len == 0) {
        conf->body_filter_src = prev->body_filter_src;
        conf->body_filter_handler = prev->body_filter_handler;
        conf->body_filter_src_key = prev->body_filter_src_key;
    }

#if (NGX_HTTP_SSL)

#   if defined(nginx_version) && nginx_version >= 1001013

    ngx_conf_merge_bitmask_value(conf->ssl_protocols, prev->ssl_protocols,
                                 (NGX_CONF_BITMASK_SET|NGX_SSL_SSLv3
                                  |NGX_SSL_TLSv1|NGX_SSL_TLSv1_1
                                  |NGX_SSL_TLSv1_2));

#   endif

    ngx_conf_merge_str_value(conf->ssl_ciphers, prev->ssl_ciphers,
                             "DEFAULT");

    ngx_conf_merge_uint_value(conf->ssl_verify_depth,
                              prev->ssl_verify_depth, 1);
    ngx_conf_merge_str_value(conf->ssl_trusted_certificate,
                             prev->ssl_trusted_certificate, "");
    ngx_conf_merge_str_value(conf->ssl_crl, prev->ssl_crl, "");

    if (ngx_http_lua_set_ssl(cf, conf) != NGX_OK) {
        return NGX_CONF_ERROR;
    }

#endif

    ngx_conf_merge_value(conf->force_read_body, prev->force_read_body, 0);
    ngx_conf_merge_value(conf->enable_code_cache, prev->enable_code_cache, 1);
    ngx_conf_merge_value(conf->http10_buffering, prev->http10_buffering, 1);
    ngx_conf_merge_value(conf->check_client_abort, prev->check_client_abort, 0);
    ngx_conf_merge_value(conf->use_default_type, prev->use_default_type, 1);

    ngx_conf_merge_msec_value(conf->keepalive_timeout,
                              prev->keepalive_timeout, 60000);

    ngx_conf_merge_msec_value(conf->connect_timeout,
                              prev->connect_timeout, 60000);

    ngx_conf_merge_msec_value(conf->send_timeout,
                              prev->send_timeout, 60000);

    ngx_conf_merge_msec_value(conf->read_timeout,
                              prev->read_timeout, 60000);

    ngx_conf_merge_size_value(conf->send_lowat,
                              prev->send_lowat, 0);

    ngx_conf_merge_size_value(conf->buffer_size,
                              prev->buffer_size,
                              (size_t) ngx_pagesize);

    ngx_conf_merge_uint_value(conf->pool_size, prev->pool_size, 30);

    ngx_conf_merge_value(conf->transform_underscores_in_resp_headers,
                         prev->transform_underscores_in_resp_headers, 1);

    ngx_conf_merge_value(conf->log_socket_errors, prev->log_socket_errors, 1);

    return NGX_CONF_OK;
}