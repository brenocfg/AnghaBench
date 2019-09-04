#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_44__   TYPE_9__ ;
typedef  struct TYPE_43__   TYPE_8__ ;
typedef  struct TYPE_42__   TYPE_7__ ;
typedef  struct TYPE_41__   TYPE_6__ ;
typedef  struct TYPE_40__   TYPE_5__ ;
typedef  struct TYPE_39__   TYPE_4__ ;
typedef  struct TYPE_38__   TYPE_3__ ;
typedef  struct TYPE_37__   TYPE_2__ ;
typedef  struct TYPE_36__   TYPE_26__ ;
typedef  struct TYPE_35__   TYPE_22__ ;
typedef  struct TYPE_34__   TYPE_1__ ;
typedef  struct TYPE_33__   TYPE_15__ ;
typedef  struct TYPE_32__   TYPE_12__ ;
typedef  struct TYPE_31__   TYPE_11__ ;
typedef  struct TYPE_30__   TYPE_10__ ;

/* Type definitions */
typedef  char u_char ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_32__ {char* data; int len; } ;
struct TYPE_41__ {int complete_lengths; int complete_values; int /*<<< orphan*/ * values; int /*<<< orphan*/ ** lengths; int /*<<< orphan*/ * flushes; TYPE_4__* source; TYPE_11__* cf; TYPE_12__ value; } ;
typedef  TYPE_6__ ngx_http_script_compile_t ;
struct TYPE_37__ {TYPE_6__ complex; } ;
struct TYPE_42__ {TYPE_6__ replacement; TYPE_2__ pattern; int /*<<< orphan*/  handler; } ;
typedef  TYPE_7__ ngx_http_proxy_rewrite_t ;
struct TYPE_40__ {int /*<<< orphan*/ * buckets; } ;
struct TYPE_35__ {TYPE_5__ hash; } ;
struct TYPE_39__ {int /*<<< orphan*/ * data; } ;
struct TYPE_36__ {int num; size_t size; } ;
struct TYPE_33__ {scalar_t__ store; scalar_t__ buffering; scalar_t__ request_buffering; scalar_t__ ignore_client_abort; scalar_t__ force_ranges; scalar_t__ socket_keepalive; size_t send_lowat; size_t buffer_size; size_t limit_rate; size_t busy_buffers_size_conf; int busy_buffers_size; size_t temp_file_write_size_conf; int temp_file_write_size; size_t max_temp_file_size_conf; int max_temp_file_size; int ignore_headers; int next_upstream; scalar_t__ pass_request_headers; scalar_t__ pass_request_body; scalar_t__ intercept_errors; int /*<<< orphan*/ * upstream; int /*<<< orphan*/  temp_path; TYPE_26__ bufs; int /*<<< orphan*/  next_upstream_timeout; int /*<<< orphan*/  read_timeout; int /*<<< orphan*/  send_timeout; int /*<<< orphan*/  connect_timeout; int /*<<< orphan*/  local; int /*<<< orphan*/  next_upstream_tries; int /*<<< orphan*/  store_access; int /*<<< orphan*/  store_values; int /*<<< orphan*/  store_lengths; } ;
struct TYPE_34__ {scalar_t__ len; } ;
struct TYPE_38__ {TYPE_1__ uri; } ;
struct TYPE_43__ {scalar_t__ redirect; TYPE_22__ headers; int /*<<< orphan*/ * headers_source; int /*<<< orphan*/  body_values; int /*<<< orphan*/ * body_lengths; int /*<<< orphan*/  body_flushes; TYPE_4__ body_source; int /*<<< orphan*/ * proxy_lengths; TYPE_15__ upstream; int /*<<< orphan*/  proxy_values; TYPE_3__ vars; TYPE_12__ location; int /*<<< orphan*/  headers_hash_bucket_size; int /*<<< orphan*/  headers_hash_max_size; int /*<<< orphan*/  http_version; int /*<<< orphan*/  cookie_paths; int /*<<< orphan*/  cookie_domains; TYPE_12__ url; int /*<<< orphan*/ * redirects; int /*<<< orphan*/ * method; } ;
typedef  TYPE_8__ ngx_http_proxy_loc_conf_t ;
struct TYPE_44__ {int /*<<< orphan*/ * handler; scalar_t__ lmt_excpt; scalar_t__ noname; } ;
typedef  TYPE_9__ ngx_http_core_loc_conf_t ;
typedef  int /*<<< orphan*/  ngx_http_complex_value_t ;
struct TYPE_30__ {char* name; int /*<<< orphan*/  bucket_size; int /*<<< orphan*/  max_size; } ;
typedef  TYPE_10__ ngx_hash_init_t ;
struct TYPE_31__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_11__ ngx_conf_t ;

/* Variables and functions */
 int NGX_CONF_BITMASK_SET ; 
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_CONF_UNSET ; 
 size_t NGX_CONF_UNSET_SIZE ; 
 int NGX_HTTP_UPSTREAM_FT_ERROR ; 
 int NGX_HTTP_UPSTREAM_FT_OFF ; 
 int NGX_HTTP_UPSTREAM_FT_TIMEOUT ; 
 int NGX_HTTP_VERSION_10 ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_align (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_array_create (int /*<<< orphan*/ ,int,int) ; 
 TYPE_7__* ngx_array_push (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_cacheline_size ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_11__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_conf_merge_bitmask_value (int,int,int) ; 
 int /*<<< orphan*/  ngx_conf_merge_bufs_value (TYPE_26__,TYPE_26__,int,scalar_t__) ; 
 int /*<<< orphan*/  ngx_conf_merge_msec_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ngx_conf_merge_path_value (TYPE_11__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_conf_merge_ptr_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_conf_merge_size_value (size_t,size_t,size_t) ; 
 int /*<<< orphan*/  ngx_conf_merge_uint_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_conf_merge_value (scalar_t__,scalar_t__,int) ; 
 char* ngx_cpymem (char*,char*,int) ; 
 TYPE_9__* ngx_http_conf_get_module_loc_conf (TYPE_11__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 int /*<<< orphan*/ * ngx_http_proxy_handler ; 
 int /*<<< orphan*/  ngx_http_proxy_headers ; 
 int /*<<< orphan*/  ngx_http_proxy_hide_headers ; 
 scalar_t__ ngx_http_proxy_init_headers (TYPE_11__*,TYPE_8__*,TYPE_22__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_proxy_rewrite_complex_handler ; 
 int /*<<< orphan*/  ngx_http_proxy_temp_path ; 
 scalar_t__ ngx_http_script_compile (TYPE_6__*) ; 
 scalar_t__ ngx_http_upstream_hide_headers_hash (TYPE_11__*,TYPE_15__*,TYPE_15__*,int /*<<< orphan*/ ,TYPE_10__*) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_6__*,int) ; 
 scalar_t__ ngx_pagesize ; 
 char* ngx_pnalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_str_set (TYPE_12__*,char*) ; 

__attribute__((used)) static char *
ngx_http_proxy_merge_loc_conf(ngx_conf_t *cf, void *parent, void *child)
{
    ngx_http_proxy_loc_conf_t *prev = parent;
    ngx_http_proxy_loc_conf_t *conf = child;

    u_char                     *p;
    size_t                      size;
    ngx_int_t                   rc;
    ngx_hash_init_t             hash;
    ngx_http_core_loc_conf_t   *clcf;
    ngx_http_proxy_rewrite_t   *pr;
    ngx_http_script_compile_t   sc;

#if (NGX_HTTP_CACHE)

    if (conf->upstream.store > 0) {
        conf->upstream.cache = 0;
    }

    if (conf->upstream.cache > 0) {
        conf->upstream.store = 0;
    }

#endif

    if (conf->upstream.store == NGX_CONF_UNSET) {
        ngx_conf_merge_value(conf->upstream.store,
                              prev->upstream.store, 0);

        conf->upstream.store_lengths = prev->upstream.store_lengths;
        conf->upstream.store_values = prev->upstream.store_values;
    }

    ngx_conf_merge_uint_value(conf->upstream.store_access,
                              prev->upstream.store_access, 0600);

    ngx_conf_merge_uint_value(conf->upstream.next_upstream_tries,
                              prev->upstream.next_upstream_tries, 0);

    ngx_conf_merge_value(conf->upstream.buffering,
                              prev->upstream.buffering, 1);

    ngx_conf_merge_value(conf->upstream.request_buffering,
                              prev->upstream.request_buffering, 1);

    ngx_conf_merge_value(conf->upstream.ignore_client_abort,
                              prev->upstream.ignore_client_abort, 0);

    ngx_conf_merge_value(conf->upstream.force_ranges,
                              prev->upstream.force_ranges, 0);

    ngx_conf_merge_ptr_value(conf->upstream.local,
                              prev->upstream.local, NULL);

    ngx_conf_merge_value(conf->upstream.socket_keepalive,
                              prev->upstream.socket_keepalive, 0);

    ngx_conf_merge_msec_value(conf->upstream.connect_timeout,
                              prev->upstream.connect_timeout, 60000);

    ngx_conf_merge_msec_value(conf->upstream.send_timeout,
                              prev->upstream.send_timeout, 60000);

    ngx_conf_merge_msec_value(conf->upstream.read_timeout,
                              prev->upstream.read_timeout, 60000);

    ngx_conf_merge_msec_value(conf->upstream.next_upstream_timeout,
                              prev->upstream.next_upstream_timeout, 0);

    ngx_conf_merge_size_value(conf->upstream.send_lowat,
                              prev->upstream.send_lowat, 0);

    ngx_conf_merge_size_value(conf->upstream.buffer_size,
                              prev->upstream.buffer_size,
                              (size_t) ngx_pagesize);

    ngx_conf_merge_size_value(conf->upstream.limit_rate,
                              prev->upstream.limit_rate, 0);

    ngx_conf_merge_bufs_value(conf->upstream.bufs, prev->upstream.bufs,
                              8, ngx_pagesize);

    if (conf->upstream.bufs.num < 2) {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "there must be at least 2 \"proxy_buffers\"");
        return NGX_CONF_ERROR;
    }


    size = conf->upstream.buffer_size;
    if (size < conf->upstream.bufs.size) {
        size = conf->upstream.bufs.size;
    }


    ngx_conf_merge_size_value(conf->upstream.busy_buffers_size_conf,
                              prev->upstream.busy_buffers_size_conf,
                              NGX_CONF_UNSET_SIZE);

    if (conf->upstream.busy_buffers_size_conf == NGX_CONF_UNSET_SIZE) {
        conf->upstream.busy_buffers_size = 2 * size;
    } else {
        conf->upstream.busy_buffers_size =
                                         conf->upstream.busy_buffers_size_conf;
    }

    if (conf->upstream.busy_buffers_size < size) {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
             "\"proxy_busy_buffers_size\" must be equal to or greater than "
             "the maximum of the value of \"proxy_buffer_size\" and "
             "one of the \"proxy_buffers\"");

        return NGX_CONF_ERROR;
    }

    if (conf->upstream.busy_buffers_size
        > (conf->upstream.bufs.num - 1) * conf->upstream.bufs.size)
    {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
             "\"proxy_busy_buffers_size\" must be less than "
             "the size of all \"proxy_buffers\" minus one buffer");

        return NGX_CONF_ERROR;
    }


    ngx_conf_merge_size_value(conf->upstream.temp_file_write_size_conf,
                              prev->upstream.temp_file_write_size_conf,
                              NGX_CONF_UNSET_SIZE);

    if (conf->upstream.temp_file_write_size_conf == NGX_CONF_UNSET_SIZE) {
        conf->upstream.temp_file_write_size = 2 * size;
    } else {
        conf->upstream.temp_file_write_size =
                                      conf->upstream.temp_file_write_size_conf;
    }

    if (conf->upstream.temp_file_write_size < size) {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
             "\"proxy_temp_file_write_size\" must be equal to or greater "
             "than the maximum of the value of \"proxy_buffer_size\" and "
             "one of the \"proxy_buffers\"");

        return NGX_CONF_ERROR;
    }

    ngx_conf_merge_size_value(conf->upstream.max_temp_file_size_conf,
                              prev->upstream.max_temp_file_size_conf,
                              NGX_CONF_UNSET_SIZE);

    if (conf->upstream.max_temp_file_size_conf == NGX_CONF_UNSET_SIZE) {
        conf->upstream.max_temp_file_size = 1024 * 1024 * 1024;
    } else {
        conf->upstream.max_temp_file_size =
                                        conf->upstream.max_temp_file_size_conf;
    }

    if (conf->upstream.max_temp_file_size != 0
        && conf->upstream.max_temp_file_size < size)
    {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
             "\"proxy_max_temp_file_size\" must be equal to zero to disable "
             "temporary files usage or must be equal to or greater than "
             "the maximum of the value of \"proxy_buffer_size\" and "
             "one of the \"proxy_buffers\"");

        return NGX_CONF_ERROR;
    }


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

    if (ngx_conf_merge_path_value(cf, &conf->upstream.temp_path,
                              prev->upstream.temp_path,
                              &ngx_http_proxy_temp_path)
        != NGX_OK)
    {
        return NGX_CONF_ERROR;
    }


#if (NGX_HTTP_CACHE)

    if (conf->upstream.cache == NGX_CONF_UNSET) {
        ngx_conf_merge_value(conf->upstream.cache,
                              prev->upstream.cache, 0);

        conf->upstream.cache_zone = prev->upstream.cache_zone;
        conf->upstream.cache_value = prev->upstream.cache_value;
    }

    if (conf->upstream.cache_zone && conf->upstream.cache_zone->data == NULL) {
        ngx_shm_zone_t  *shm_zone;

        shm_zone = conf->upstream.cache_zone;

        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "\"proxy_cache\" zone \"%V\" is unknown",
                           &shm_zone->shm.name);

        return NGX_CONF_ERROR;
    }

    ngx_conf_merge_uint_value(conf->upstream.cache_min_uses,
                              prev->upstream.cache_min_uses, 1);

    ngx_conf_merge_off_value(conf->upstream.cache_max_range_offset,
                              prev->upstream.cache_max_range_offset,
                              NGX_MAX_OFF_T_VALUE);

    ngx_conf_merge_bitmask_value(conf->upstream.cache_use_stale,
                              prev->upstream.cache_use_stale,
                              (NGX_CONF_BITMASK_SET
                               |NGX_HTTP_UPSTREAM_FT_OFF));

    if (conf->upstream.cache_use_stale & NGX_HTTP_UPSTREAM_FT_OFF) {
        conf->upstream.cache_use_stale = NGX_CONF_BITMASK_SET
                                         |NGX_HTTP_UPSTREAM_FT_OFF;
    }

    if (conf->upstream.cache_use_stale & NGX_HTTP_UPSTREAM_FT_ERROR) {
        conf->upstream.cache_use_stale |= NGX_HTTP_UPSTREAM_FT_NOLIVE;
    }

    if (conf->upstream.cache_methods == 0) {
        conf->upstream.cache_methods = prev->upstream.cache_methods;
    }

    conf->upstream.cache_methods |= NGX_HTTP_GET|NGX_HTTP_HEAD;

    ngx_conf_merge_ptr_value(conf->upstream.cache_bypass,
                             prev->upstream.cache_bypass, NULL);

    ngx_conf_merge_ptr_value(conf->upstream.no_cache,
                             prev->upstream.no_cache, NULL);

    ngx_conf_merge_ptr_value(conf->upstream.cache_valid,
                             prev->upstream.cache_valid, NULL);

    if (conf->cache_key.value.data == NULL) {
        conf->cache_key = prev->cache_key;
    }

    ngx_conf_merge_value(conf->upstream.cache_lock,
                              prev->upstream.cache_lock, 0);

    ngx_conf_merge_msec_value(conf->upstream.cache_lock_timeout,
                              prev->upstream.cache_lock_timeout, 5000);

    ngx_conf_merge_msec_value(conf->upstream.cache_lock_age,
                              prev->upstream.cache_lock_age, 5000);

    ngx_conf_merge_value(conf->upstream.cache_revalidate,
                              prev->upstream.cache_revalidate, 0);

    ngx_conf_merge_value(conf->upstream.cache_convert_head,
                              prev->upstream.cache_convert_head, 1);

    ngx_conf_merge_value(conf->upstream.cache_background_update,
                              prev->upstream.cache_background_update, 0);

#endif

    if (conf->method == NULL) {
        conf->method = prev->method;
    }

    ngx_conf_merge_value(conf->upstream.pass_request_headers,
                              prev->upstream.pass_request_headers, 1);
    ngx_conf_merge_value(conf->upstream.pass_request_body,
                              prev->upstream.pass_request_body, 1);

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

    if (conf->ssl && ngx_http_proxy_set_ssl(cf, conf) != NGX_OK) {
        return NGX_CONF_ERROR;
    }

#endif

    ngx_conf_merge_value(conf->redirect, prev->redirect, 1);

    if (conf->redirect) {

        if (conf->redirects == NULL) {
            conf->redirects = prev->redirects;
        }

        if (conf->redirects == NULL && conf->url.data) {

            conf->redirects = ngx_array_create(cf->pool, 1,
                                             sizeof(ngx_http_proxy_rewrite_t));
            if (conf->redirects == NULL) {
                return NGX_CONF_ERROR;
            }

            pr = ngx_array_push(conf->redirects);
            if (pr == NULL) {
                return NGX_CONF_ERROR;
            }

            ngx_memzero(&pr->pattern.complex,
                        sizeof(ngx_http_complex_value_t));

            ngx_memzero(&pr->replacement, sizeof(ngx_http_complex_value_t));

            pr->handler = ngx_http_proxy_rewrite_complex_handler;

            if (conf->vars.uri.len) {
                pr->pattern.complex.value = conf->url;
                pr->replacement.value = conf->location;

            } else {
                pr->pattern.complex.value.len = conf->url.len
                                                + sizeof("/") - 1;

                p = ngx_pnalloc(cf->pool, pr->pattern.complex.value.len);
                if (p == NULL) {
                    return NGX_CONF_ERROR;
                }

                pr->pattern.complex.value.data = p;

                p = ngx_cpymem(p, conf->url.data, conf->url.len);
                *p = '/';

                ngx_str_set(&pr->replacement.value, "/");
            }
        }
    }

    ngx_conf_merge_ptr_value(conf->cookie_domains, prev->cookie_domains, NULL);

    ngx_conf_merge_ptr_value(conf->cookie_paths, prev->cookie_paths, NULL);

    ngx_conf_merge_uint_value(conf->http_version, prev->http_version,
                              NGX_HTTP_VERSION_10);

    ngx_conf_merge_uint_value(conf->headers_hash_max_size,
                              prev->headers_hash_max_size, 512);

    ngx_conf_merge_uint_value(conf->headers_hash_bucket_size,
                              prev->headers_hash_bucket_size, 64);

    conf->headers_hash_bucket_size = ngx_align(conf->headers_hash_bucket_size,
                                               ngx_cacheline_size);

    hash.max_size = conf->headers_hash_max_size;
    hash.bucket_size = conf->headers_hash_bucket_size;
    hash.name = "proxy_headers_hash";

    if (ngx_http_upstream_hide_headers_hash(cf, &conf->upstream,
            &prev->upstream, ngx_http_proxy_hide_headers, &hash)
        != NGX_OK)
    {
        return NGX_CONF_ERROR;
    }

    clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);

    if (clcf->noname
        && conf->upstream.upstream == NULL && conf->proxy_lengths == NULL)
    {
        conf->upstream.upstream = prev->upstream.upstream;
        conf->location = prev->location;
        conf->vars = prev->vars;

        conf->proxy_lengths = prev->proxy_lengths;
        conf->proxy_values = prev->proxy_values;

#if (NGX_HTTP_SSL)
        conf->upstream.ssl = prev->upstream.ssl;
#endif
    }

    if (clcf->lmt_excpt && clcf->handler == NULL
        && (conf->upstream.upstream || conf->proxy_lengths))
    {
        clcf->handler = ngx_http_proxy_handler;
    }

    if (conf->body_source.data == NULL) {
        conf->body_flushes = prev->body_flushes;
        conf->body_source = prev->body_source;
        conf->body_lengths = prev->body_lengths;
        conf->body_values = prev->body_values;
    }

    if (conf->body_source.data && conf->body_lengths == NULL) {

        ngx_memzero(&sc, sizeof(ngx_http_script_compile_t));

        sc.cf = cf;
        sc.source = &conf->body_source;
        sc.flushes = &conf->body_flushes;
        sc.lengths = &conf->body_lengths;
        sc.values = &conf->body_values;
        sc.complete_lengths = 1;
        sc.complete_values = 1;

        if (ngx_http_script_compile(&sc) != NGX_OK) {
            return NGX_CONF_ERROR;
        }
    }

    if (conf->headers_source == NULL) {
        conf->headers = prev->headers;
#if (NGX_HTTP_CACHE)
        conf->headers_cache = prev->headers_cache;
#endif
        conf->headers_source = prev->headers_source;
    }

    rc = ngx_http_proxy_init_headers(cf, conf, &conf->headers,
                                     ngx_http_proxy_headers);
    if (rc != NGX_OK) {
        return NGX_CONF_ERROR;
    }

#if (NGX_HTTP_CACHE)

    if (conf->upstream.cache) {
        rc = ngx_http_proxy_init_headers(cf, conf, &conf->headers_cache,
                                         ngx_http_proxy_cache_headers);
        if (rc != NGX_OK) {
            return NGX_CONF_ERROR;
        }
    }

#endif

    /*
     * special handling to preserve conf->headers in the "http" section
     * to inherit it to all servers
     */

    if (prev->headers.hash.buckets == NULL
        && conf->headers_source == prev->headers_source)
    {
        prev->headers = conf->headers;
#if (NGX_HTTP_CACHE)
        prev->headers_cache = conf->headers_cache;
#endif
    }

    return NGX_CONF_OK;
}