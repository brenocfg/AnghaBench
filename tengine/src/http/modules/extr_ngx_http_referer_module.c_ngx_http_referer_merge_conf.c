#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_17__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_27__ {int /*<<< orphan*/  name; scalar_t__ regex; } ;
typedef  TYPE_6__ ngx_http_server_name_t ;
struct TYPE_25__ {int /*<<< orphan*/ * wc_tail; int /*<<< orphan*/ * wc_head; int /*<<< orphan*/  hash; } ;
struct TYPE_28__ {int no_referer; int blocked_referer; int server_names; TYPE_17__* keys; int /*<<< orphan*/  server_name_regex; int /*<<< orphan*/  regex; TYPE_4__ hash; int /*<<< orphan*/  referer_hash_bucket_size; int /*<<< orphan*/  referer_hash_max_size; } ;
typedef  TYPE_7__ ngx_http_referer_conf_t ;
struct TYPE_22__ {size_t nelts; TYPE_6__* elts; } ;
struct TYPE_29__ {TYPE_1__ server_names; } ;
typedef  TYPE_8__ ngx_http_core_srv_conf_t ;
typedef  int /*<<< orphan*/  ngx_hash_wildcard_t ;
typedef  int /*<<< orphan*/  ngx_hash_key_t ;
struct TYPE_30__ {char* name; int /*<<< orphan*/ * hash; int /*<<< orphan*/ * temp_pool; int /*<<< orphan*/  pool; int /*<<< orphan*/  bucket_size; int /*<<< orphan*/  max_size; int /*<<< orphan*/  key; } ;
typedef  TYPE_9__ ngx_hash_init_t ;
struct TYPE_20__ {int /*<<< orphan*/ * temp_pool; int /*<<< orphan*/  pool; int /*<<< orphan*/  log; } ;
typedef  TYPE_10__ ngx_conf_t ;
struct TYPE_26__ {scalar_t__ nelts; int /*<<< orphan*/  elts; } ;
struct TYPE_24__ {scalar_t__ nelts; int /*<<< orphan*/  elts; } ;
struct TYPE_23__ {scalar_t__ nelts; int /*<<< orphan*/  elts; } ;
struct TYPE_21__ {TYPE_5__ dns_wc_tail; TYPE_3__ dns_wc_head; TYPE_2__ keys; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 int NGX_CONF_UNSET ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_align (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_cacheline_size ; 
 int /*<<< orphan*/  ngx_conf_merge_ptr_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_conf_merge_uint_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_conf_merge_value (int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_hash_init (TYPE_9__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ngx_hash_key_lc ; 
 scalar_t__ ngx_hash_wildcard_init (TYPE_9__*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ngx_http_add_referer (TYPE_10__*,TYPE_17__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_http_add_regex_server_name (TYPE_10__*,TYPE_7__*,scalar_t__) ; 
 int /*<<< orphan*/  ngx_http_cmp_referer_wildcards ; 
 TYPE_8__* ngx_http_conf_get_module_srv_conf (TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_qsort (int /*<<< orphan*/ ,size_t,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
ngx_http_referer_merge_conf(ngx_conf_t *cf, void *parent, void *child)
{
    ngx_http_referer_conf_t *prev = parent;
    ngx_http_referer_conf_t *conf = child;

    ngx_uint_t                 n;
    ngx_hash_init_t            hash;
    ngx_http_server_name_t    *sn;
    ngx_http_core_srv_conf_t  *cscf;

    if (conf->keys == NULL) {
        conf->hash = prev->hash;

#if (NGX_PCRE)
        ngx_conf_merge_ptr_value(conf->regex, prev->regex, NULL);
        ngx_conf_merge_ptr_value(conf->server_name_regex,
                                 prev->server_name_regex, NULL);
#endif
        ngx_conf_merge_value(conf->no_referer, prev->no_referer, 0);
        ngx_conf_merge_value(conf->blocked_referer, prev->blocked_referer, 0);
        ngx_conf_merge_uint_value(conf->referer_hash_max_size,
                                  prev->referer_hash_max_size, 2048);
        ngx_conf_merge_uint_value(conf->referer_hash_bucket_size,
                                  prev->referer_hash_bucket_size, 64);

        return NGX_CONF_OK;
    }

    if (conf->server_names == 1) {
        cscf = ngx_http_conf_get_module_srv_conf(cf, ngx_http_core_module);

        sn = cscf->server_names.elts;
        for (n = 0; n < cscf->server_names.nelts; n++) {

#if (NGX_PCRE)
            if (sn[n].regex) {

                if (ngx_http_add_regex_server_name(cf, conf, sn[n].regex)
                    != NGX_OK)
                {
                    return NGX_CONF_ERROR;
                }

                continue;
            }
#endif

            if (ngx_http_add_referer(cf, conf->keys, &sn[n].name, NULL)
                != NGX_OK)
            {
                return NGX_CONF_ERROR;
            }
        }
    }

    if ((conf->no_referer == 1 || conf->blocked_referer == 1)
        && conf->keys->keys.nelts == 0
        && conf->keys->dns_wc_head.nelts == 0
        && conf->keys->dns_wc_tail.nelts == 0)
    {
        ngx_log_error(NGX_LOG_EMERG, cf->log, 0,
                      "the \"none\" or \"blocked\" referers are specified "
                      "in the \"valid_referers\" directive "
                      "without any valid referer");
        return NGX_CONF_ERROR;
    }

    ngx_conf_merge_uint_value(conf->referer_hash_max_size,
                              prev->referer_hash_max_size, 2048);
    ngx_conf_merge_uint_value(conf->referer_hash_bucket_size,
                              prev->referer_hash_bucket_size, 64);
    conf->referer_hash_bucket_size = ngx_align(conf->referer_hash_bucket_size,
                                               ngx_cacheline_size);

    hash.key = ngx_hash_key_lc;
    hash.max_size = conf->referer_hash_max_size;
    hash.bucket_size = conf->referer_hash_bucket_size;
    hash.name = "referer_hash";
    hash.pool = cf->pool;

    if (conf->keys->keys.nelts) {
        hash.hash = &conf->hash.hash;
        hash.temp_pool = NULL;

        if (ngx_hash_init(&hash, conf->keys->keys.elts, conf->keys->keys.nelts)
            != NGX_OK)
        {
            return NGX_CONF_ERROR;
        }
    }

    if (conf->keys->dns_wc_head.nelts) {

        ngx_qsort(conf->keys->dns_wc_head.elts,
                  (size_t) conf->keys->dns_wc_head.nelts,
                  sizeof(ngx_hash_key_t),
                  ngx_http_cmp_referer_wildcards);

        hash.hash = NULL;
        hash.temp_pool = cf->temp_pool;

        if (ngx_hash_wildcard_init(&hash, conf->keys->dns_wc_head.elts,
                                   conf->keys->dns_wc_head.nelts)
            != NGX_OK)
        {
            return NGX_CONF_ERROR;
        }

        conf->hash.wc_head = (ngx_hash_wildcard_t *) hash.hash;
    }

    if (conf->keys->dns_wc_tail.nelts) {

        ngx_qsort(conf->keys->dns_wc_tail.elts,
                  (size_t) conf->keys->dns_wc_tail.nelts,
                  sizeof(ngx_hash_key_t),
                  ngx_http_cmp_referer_wildcards);

        hash.hash = NULL;
        hash.temp_pool = cf->temp_pool;

        if (ngx_hash_wildcard_init(&hash, conf->keys->dns_wc_tail.elts,
                                   conf->keys->dns_wc_tail.nelts)
            != NGX_OK)
        {
            return NGX_CONF_ERROR;
        }

        conf->hash.wc_tail = (ngx_hash_wildcard_t *) hash.hash;
    }

#if (NGX_PCRE)
    ngx_conf_merge_ptr_value(conf->regex, prev->regex, NULL);
    ngx_conf_merge_ptr_value(conf->server_name_regex, prev->server_name_regex,
                             NULL);
#endif

    if (conf->no_referer == NGX_CONF_UNSET) {
        conf->no_referer = 0;
    }

    if (conf->blocked_referer == NGX_CONF_UNSET) {
        conf->blocked_referer = 0;
    }

    conf->keys = NULL;

    return NGX_CONF_OK;
}