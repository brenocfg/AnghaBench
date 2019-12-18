#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ ngx_int_t ;
struct TYPE_13__ {int /*<<< orphan*/ * buckets; } ;
struct TYPE_12__ {TYPE_1__ hash; } ;
struct TYPE_17__ {int ignore_headers; int next_upstream; int /*<<< orphan*/ * upstream; int /*<<< orphan*/  ssl; int /*<<< orphan*/  ssl_verify; int /*<<< orphan*/  ssl_server_name; int /*<<< orphan*/ * ssl_name; int /*<<< orphan*/  ssl_session_reuse; int /*<<< orphan*/  intercept_errors; int /*<<< orphan*/  buffer_size; int /*<<< orphan*/  next_upstream_timeout; int /*<<< orphan*/  read_timeout; int /*<<< orphan*/  send_timeout; int /*<<< orphan*/  connect_timeout; int /*<<< orphan*/  next_upstream_tries; int /*<<< orphan*/  socket_keepalive; int /*<<< orphan*/  local; } ;
struct TYPE_14__ {int ssl_protocols; int /*<<< orphan*/  host_set; TYPE_10__ headers; int /*<<< orphan*/ * headers_source; TYPE_5__ upstream; int /*<<< orphan*/  host; scalar_t__ ssl; int /*<<< orphan*/  ssl_passwords; int /*<<< orphan*/  ssl_certificate_key; int /*<<< orphan*/  ssl_certificate; int /*<<< orphan*/  ssl_crl; int /*<<< orphan*/  ssl_trusted_certificate; int /*<<< orphan*/  ssl_verify_depth; int /*<<< orphan*/  ssl_ciphers; } ;
typedef  TYPE_2__ ngx_http_grpc_loc_conf_t ;
struct TYPE_15__ {int /*<<< orphan*/ * handler; scalar_t__ lmt_excpt; scalar_t__ noname; } ;
typedef  TYPE_3__ ngx_http_core_loc_conf_t ;
struct TYPE_16__ {int max_size; char* name; int /*<<< orphan*/  bucket_size; } ;
typedef  TYPE_4__ ngx_hash_init_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;

/* Variables and functions */
 int NGX_CONF_BITMASK_SET ; 
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 int NGX_HTTP_UPSTREAM_FT_ERROR ; 
 int NGX_HTTP_UPSTREAM_FT_OFF ; 
 int NGX_HTTP_UPSTREAM_FT_TIMEOUT ; 
 scalar_t__ NGX_OK ; 
 int NGX_SSL_TLSv1 ; 
 int NGX_SSL_TLSv1_1 ; 
 int NGX_SSL_TLSv1_2 ; 
 int /*<<< orphan*/  ngx_align (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_cacheline_size ; 
 int /*<<< orphan*/  ngx_conf_merge_bitmask_value (int,int,int) ; 
 int /*<<< orphan*/  ngx_conf_merge_msec_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_conf_merge_ptr_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_conf_merge_size_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ngx_conf_merge_str_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_conf_merge_uint_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_conf_merge_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* ngx_http_conf_get_module_loc_conf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 int /*<<< orphan*/ * ngx_http_grpc_handler ; 
 int /*<<< orphan*/  ngx_http_grpc_headers ; 
 int /*<<< orphan*/  ngx_http_grpc_hide_headers ; 
 scalar_t__ ngx_http_grpc_init_headers (int /*<<< orphan*/ *,TYPE_2__*,TYPE_10__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_grpc_set_ssl (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ ngx_http_upstream_hide_headers_hash (int /*<<< orphan*/ *,TYPE_5__*,TYPE_5__*,int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ ngx_pagesize ; 

__attribute__((used)) static char *
ngx_http_grpc_merge_loc_conf(ngx_conf_t *cf, void *parent, void *child)
{
    ngx_http_grpc_loc_conf_t *prev = parent;
    ngx_http_grpc_loc_conf_t *conf = child;

    ngx_int_t                  rc;
    ngx_hash_init_t            hash;
    ngx_http_core_loc_conf_t  *clcf;

    ngx_conf_merge_ptr_value(conf->upstream.local,
                              prev->upstream.local, NULL);

    ngx_conf_merge_value(conf->upstream.socket_keepalive,
                              prev->upstream.socket_keepalive, 0);

    ngx_conf_merge_uint_value(conf->upstream.next_upstream_tries,
                              prev->upstream.next_upstream_tries, 0);

    ngx_conf_merge_msec_value(conf->upstream.connect_timeout,
                              prev->upstream.connect_timeout, 60000);

    ngx_conf_merge_msec_value(conf->upstream.send_timeout,
                              prev->upstream.send_timeout, 60000);

    ngx_conf_merge_msec_value(conf->upstream.read_timeout,
                              prev->upstream.read_timeout, 60000);

    ngx_conf_merge_msec_value(conf->upstream.next_upstream_timeout,
                              prev->upstream.next_upstream_timeout, 0);

    ngx_conf_merge_size_value(conf->upstream.buffer_size,
                              prev->upstream.buffer_size,
                              (size_t) ngx_pagesize);

    ngx_conf_merge_bitmask_value(conf->upstream.ignore_headers,
                              prev->upstream.ignore_headers,
                              NGX_CONF_BITMASK_SET);

    ngx_conf_merge_bitmask_value(conf->upstream.next_upstream,
                              prev->upstream.next_upstream,
                              (NGX_CONF_BITMASK_SET
                               |NGX_HTTP_UPSTREAM_FT_ERROR
                               |NGX_HTTP_UPSTREAM_FT_TIMEOUT));

    if (conf->upstream.next_upstream & NGX_HTTP_UPSTREAM_FT_OFF) {
        conf->upstream.next_upstream = NGX_CONF_BITMASK_SET
                                       |NGX_HTTP_UPSTREAM_FT_OFF;
    }

    ngx_conf_merge_value(conf->upstream.intercept_errors,
                              prev->upstream.intercept_errors, 0);

#if (NGX_HTTP_SSL)

    ngx_conf_merge_value(conf->upstream.ssl_session_reuse,
                              prev->upstream.ssl_session_reuse, 1);

    ngx_conf_merge_bitmask_value(conf->ssl_protocols, prev->ssl_protocols,
                                 (NGX_CONF_BITMASK_SET|NGX_SSL_TLSv1
                                  |NGX_SSL_TLSv1_1|NGX_SSL_TLSv1_2));

    ngx_conf_merge_str_value(conf->ssl_ciphers, prev->ssl_ciphers,
                             "DEFAULT");

    if (conf->upstream.ssl_name == NULL) {
        conf->upstream.ssl_name = prev->upstream.ssl_name;
    }

    ngx_conf_merge_value(conf->upstream.ssl_server_name,
                              prev->upstream.ssl_server_name, 0);
    ngx_conf_merge_value(conf->upstream.ssl_verify,
                              prev->upstream.ssl_verify, 0);
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

    if (conf->ssl && ngx_http_grpc_set_ssl(cf, conf) != NGX_OK) {
        return NGX_CONF_ERROR;
    }

#endif

    hash.max_size = 512;
    hash.bucket_size = ngx_align(64, ngx_cacheline_size);
    hash.name = "grpc_headers_hash";

    if (ngx_http_upstream_hide_headers_hash(cf, &conf->upstream,
            &prev->upstream, ngx_http_grpc_hide_headers, &hash)
        != NGX_OK)
    {
        return NGX_CONF_ERROR;
    }

    clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);

    if (clcf->noname && conf->upstream.upstream == NULL) {
        conf->upstream.upstream = prev->upstream.upstream;
        conf->host = prev->host;
#if (NGX_HTTP_SSL)
        conf->upstream.ssl = prev->upstream.ssl;
#endif
    }

    if (clcf->lmt_excpt && clcf->handler == NULL && conf->upstream.upstream) {
        clcf->handler = ngx_http_grpc_handler;
    }

    if (conf->headers_source == NULL) {
        conf->headers = prev->headers;
        conf->headers_source = prev->headers_source;
        conf->host_set = prev->host_set;
    }

    rc = ngx_http_grpc_init_headers(cf, conf, &conf->headers,
                                    ngx_http_grpc_headers);
    if (rc != NGX_OK) {
        return NGX_CONF_ERROR;
    }

    /*
     * special handling to preserve conf->headers in the "http" section
     * to inherit it to all servers
     */

    if (prev->headers.hash.buckets == NULL
        && conf->headers_source == prev->headers_source)
    {
        prev->headers = conf->headers;
        prev->host_set = conf->host_set;
    }

    return NGX_CONF_OK;
}