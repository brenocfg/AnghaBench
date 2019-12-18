#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_40__   TYPE_9__ ;
typedef  struct TYPE_39__   TYPE_8__ ;
typedef  struct TYPE_38__   TYPE_7__ ;
typedef  struct TYPE_37__   TYPE_6__ ;
typedef  struct TYPE_36__   TYPE_5__ ;
typedef  struct TYPE_35__   TYPE_4__ ;
typedef  struct TYPE_34__   TYPE_3__ ;
typedef  struct TYPE_33__   TYPE_2__ ;
typedef  struct TYPE_32__   TYPE_23__ ;
typedef  struct TYPE_31__   TYPE_1__ ;
typedef  struct TYPE_30__   TYPE_14__ ;
typedef  struct TYPE_29__   TYPE_11__ ;
typedef  struct TYPE_28__   TYPE_10__ ;

/* Type definitions */
typedef  int ngx_uint_t ;
struct TYPE_37__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
typedef  TYPE_6__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_http_sub_tables_t ;
struct TYPE_32__ {TYPE_6__ value; int /*<<< orphan*/ * lengths; } ;
struct TYPE_38__ {TYPE_23__ match; int /*<<< orphan*/  value; } ;
typedef  TYPE_7__ ngx_http_sub_pair_t ;
struct TYPE_39__ {TYPE_6__ match; int /*<<< orphan*/ * value; } ;
typedef  TYPE_8__ ngx_http_sub_match_t ;
struct TYPE_40__ {scalar_t__ dynamic; int /*<<< orphan*/  last_modified; TYPE_2__* pairs; TYPE_3__* matches; TYPE_14__* tables; int /*<<< orphan*/  types; } ;
typedef  TYPE_9__ ngx_http_sub_loc_conf_t ;
struct TYPE_36__ {int /*<<< orphan*/ * data; } ;
struct TYPE_35__ {int /*<<< orphan*/ * data; } ;
struct TYPE_28__ {int /*<<< orphan*/  out; int /*<<< orphan*/ * last_out; TYPE_14__* tables; scalar_t__ offset; TYPE_5__ looked; TYPE_4__ saved; TYPE_3__* matches; } ;
typedef  TYPE_10__ ngx_http_sub_ctx_t ;
struct TYPE_31__ {scalar_t__ content_length_n; } ;
struct TYPE_29__ {int filter_need_in_memory; struct TYPE_29__* main; int /*<<< orphan*/  pool; TYPE_1__ headers_out; } ;
typedef  TYPE_11__ ngx_http_request_t ;
typedef  int /*<<< orphan*/  ngx_array_t ;
struct TYPE_34__ {int nelts; TYPE_8__* elts; } ;
struct TYPE_33__ {int nelts; TYPE_7__* elts; } ;
struct TYPE_30__ {scalar_t__ min_match_len; scalar_t__ max_match_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_http_clear_content_length (TYPE_11__*) ; 
 int /*<<< orphan*/  ngx_http_clear_etag (TYPE_11__*) ; 
 int /*<<< orphan*/  ngx_http_clear_last_modified (TYPE_11__*) ; 
 scalar_t__ ngx_http_complex_value (TYPE_11__*,TYPE_23__*,TYPE_6__*) ; 
 TYPE_9__* ngx_http_get_module_loc_conf (TYPE_11__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_next_header_filter (TYPE_11__*) ; 
 int /*<<< orphan*/  ngx_http_set_ctx (TYPE_11__*,TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_sub_filter_module ; 
 int /*<<< orphan*/  ngx_http_sub_init_tables (TYPE_14__*,TYPE_8__*,int) ; 
 int /*<<< orphan*/ * ngx_http_test_content_type (TYPE_11__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_weak_etag (TYPE_11__*) ; 
 void* ngx_palloc (int /*<<< orphan*/ ,int) ; 
 void* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 void* ngx_pnalloc (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ngx_strlow (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static ngx_int_t
ngx_http_sub_header_filter(ngx_http_request_t *r)
{
    ngx_str_t                *m;
    ngx_uint_t                i, j, n;
    ngx_http_sub_ctx_t       *ctx;
    ngx_http_sub_pair_t      *pairs;
    ngx_http_sub_match_t     *matches;
    ngx_http_sub_loc_conf_t  *slcf;

    slcf = ngx_http_get_module_loc_conf(r, ngx_http_sub_filter_module);

    if (slcf->pairs == NULL
        || r->headers_out.content_length_n == 0
        || ngx_http_test_content_type(r, &slcf->types) == NULL)
    {
        return ngx_http_next_header_filter(r);
    }

    ctx = ngx_pcalloc(r->pool, sizeof(ngx_http_sub_ctx_t));
    if (ctx == NULL) {
        return NGX_ERROR;
    }

    if (slcf->dynamic == 0) {
        ctx->tables = slcf->tables;
        ctx->matches = slcf->matches;

    } else {
        pairs = slcf->pairs->elts;
        n = slcf->pairs->nelts;

        matches = ngx_pcalloc(r->pool, sizeof(ngx_http_sub_match_t) * n);
        if (matches == NULL) {
            return NGX_ERROR;
        }

        j = 0;
        for (i = 0; i < n; i++) {
            matches[j].value = &pairs[i].value;

            if (pairs[i].match.lengths == NULL) {
                matches[j].match = pairs[i].match.value;
                j++;
                continue;
            }

            m = &matches[j].match;
            if (ngx_http_complex_value(r, &pairs[i].match, m) != NGX_OK) {
                return NGX_ERROR;
            }

            if (m->len == 0) {
                continue;
            }

            ngx_strlow(m->data, m->data, m->len);
            j++;
        }

        if (j == 0) {
            return ngx_http_next_header_filter(r);
        }

        ctx->matches = ngx_palloc(r->pool, sizeof(ngx_array_t));
        if (ctx->matches == NULL) {
            return NGX_ERROR;
        }

        ctx->matches->elts = matches;
        ctx->matches->nelts = j;

        ctx->tables = ngx_palloc(r->pool, sizeof(ngx_http_sub_tables_t));
        if (ctx->tables == NULL) {
            return NGX_ERROR;
        }

        ngx_http_sub_init_tables(ctx->tables, ctx->matches->elts,
                                 ctx->matches->nelts);
    }

    ctx->saved.data = ngx_pnalloc(r->pool, ctx->tables->max_match_len - 1);
    if (ctx->saved.data == NULL) {
        return NGX_ERROR;
    }

    ctx->looked.data = ngx_pnalloc(r->pool, ctx->tables->max_match_len - 1);
    if (ctx->looked.data == NULL) {
        return NGX_ERROR;
    }

    ngx_http_set_ctx(r, ctx, ngx_http_sub_filter_module);

    ctx->offset = ctx->tables->min_match_len - 1;
    ctx->last_out = &ctx->out;

    r->filter_need_in_memory = 1;

    if (r == r->main) {
        ngx_http_clear_content_length(r);

        if (!slcf->last_modified) {
            ngx_http_clear_last_modified(r);
            ngx_http_clear_etag(r);

        } else {
            ngx_http_weak_etag(r);
        }
    }

    return ngx_http_next_header_filter(r);
}