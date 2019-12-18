#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_55__   TYPE_9__ ;
typedef  struct TYPE_54__   TYPE_8__ ;
typedef  struct TYPE_53__   TYPE_7__ ;
typedef  struct TYPE_52__   TYPE_6__ ;
typedef  struct TYPE_51__   TYPE_5__ ;
typedef  struct TYPE_50__   TYPE_4__ ;
typedef  struct TYPE_49__   TYPE_3__ ;
typedef  struct TYPE_48__   TYPE_33__ ;
typedef  struct TYPE_47__   TYPE_2__ ;
typedef  struct TYPE_46__   TYPE_25__ ;
typedef  struct TYPE_45__   TYPE_20__ ;
typedef  struct TYPE_44__   TYPE_1__ ;
typedef  struct TYPE_43__   TYPE_19__ ;
typedef  struct TYPE_42__   TYPE_18__ ;
typedef  struct TYPE_41__   TYPE_17__ ;
typedef  struct TYPE_40__   TYPE_16__ ;
typedef  struct TYPE_39__   TYPE_15__ ;
typedef  struct TYPE_38__   TYPE_14__ ;
typedef  struct TYPE_37__   TYPE_13__ ;
typedef  struct TYPE_36__   TYPE_12__ ;
typedef  struct TYPE_35__   TYPE_11__ ;
typedef  struct TYPE_34__   TYPE_10__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_50__ {scalar_t__ data; scalar_t__ len; } ;
struct TYPE_49__ {scalar_t__ len; } ;
struct TYPE_54__ {scalar_t__ lowcase_key; TYPE_4__ value; TYPE_3__ key; } ;
typedef  TYPE_8__ ngx_table_elt_t ;
typedef  int /*<<< orphan*/  ngx_multi_request_t ;
struct TYPE_55__ {size_t nelts; TYPE_8__* elts; struct TYPE_55__* next; } ;
typedef  TYPE_9__ ngx_list_part_t ;
struct TYPE_45__ {scalar_t__ data; scalar_t__ len; } ;
struct TYPE_34__ {TYPE_20__ value; TYPE_20__ key; } ;
typedef  TYPE_10__ ngx_keyval_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_35__ {scalar_t__ data; scalar_t__ len; scalar_t__ not_found; } ;
typedef  TYPE_11__ ngx_http_variable_value_t ;
struct TYPE_44__ {TYPE_9__ part; } ;
struct TYPE_47__ {TYPE_1__ headers; } ;
struct TYPE_36__ {TYPE_5__* connection; TYPE_2__ headers_in; int /*<<< orphan*/  pool; } ;
typedef  TYPE_12__ ngx_http_request_t ;
struct TYPE_37__ {int /*<<< orphan*/  method; int /*<<< orphan*/  service_version; int /*<<< orphan*/  service_name; TYPE_6__* args_in; scalar_t__ pass_all_headers; scalar_t__ pass_body; } ;
typedef  TYPE_13__ ngx_http_dubbo_loc_conf_t ;
struct TYPE_38__ {TYPE_16__* connection; } ;
typedef  TYPE_14__ ngx_http_dubbo_ctx_t ;
struct TYPE_39__ {scalar_t__ key_var_index; scalar_t__ value_var_index; TYPE_20__ value; TYPE_20__ key; } ;
typedef  TYPE_15__ ngx_http_dubbo_arg_t ;
struct TYPE_40__ {int /*<<< orphan*/  log; int /*<<< orphan*/  temp_pool; } ;
typedef  TYPE_16__ ngx_dubbo_connection_t ;
struct TYPE_53__ {int /*<<< orphan*/ * m; } ;
struct TYPE_41__ {TYPE_7__ value; int /*<<< orphan*/  type; } ;
typedef  TYPE_17__ ngx_dubbo_arg_t ;
typedef  int /*<<< orphan*/  ngx_connection_t ;
struct TYPE_42__ {TYPE_33__* buf; struct TYPE_42__* next; } ;
typedef  TYPE_18__ ngx_chain_t ;
struct TYPE_43__ {scalar_t__ last; scalar_t__ pos; } ;
typedef  TYPE_19__ ngx_buf_t ;
typedef  int /*<<< orphan*/  ngx_array_t ;
struct TYPE_52__ {size_t nelts; TYPE_15__* elts; } ;
struct TYPE_51__ {int /*<<< orphan*/  log; } ;
struct TYPE_48__ {scalar_t__ pos; scalar_t__ last; scalar_t__ file_pos; scalar_t__ file_last; int /*<<< orphan*/  file; scalar_t__ in_file; } ;
struct TYPE_46__ {scalar_t__ data; scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUBBO_ARG_MAP ; 
 scalar_t__ NGX_CONF_UNSET ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int /*<<< orphan*/  NGX_LOG_WARN ; 
 scalar_t__ NGX_OK ; 
 void* ngx_array_create (int /*<<< orphan*/ ,size_t,int) ; 
 scalar_t__ ngx_array_push (int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_buf_size (TYPE_33__*) ; 
 scalar_t__ ngx_cpymem (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/ * ngx_create_multi_request (int /*<<< orphan*/ *,TYPE_12__*) ; 
 TYPE_19__* ngx_create_temp_buf (int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ ngx_dubbo_encode_request (TYPE_16__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_14__* ngx_http_dubbo_get_ctx (TYPE_12__*) ; 
 int /*<<< orphan*/  ngx_http_dubbo_module ; 
 TYPE_25__ ngx_http_dubbo_str_body ; 
 TYPE_11__* ngx_http_get_indexed_variable (TYPE_12__*,scalar_t__) ; 
 TYPE_13__* ngx_http_get_module_loc_conf (TYPE_12__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ngx_read_file (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ngx_str_null (TYPE_20__*) ; 

__attribute__((used)) static ngx_int_t
ngx_http_dubbo_create_dubbo_request(ngx_http_request_t *r, ngx_connection_t *pc, ngx_multi_request_t **multi_rptr, ngx_chain_t *in)
{
    ngx_http_dubbo_ctx_t        *ctx;
    ngx_multi_request_t         *multi_r;
    ngx_dubbo_connection_t      *dubbo_c;
    ngx_http_dubbo_loc_conf_t   *dlcf;

    ngx_array_t                 *args;
    ngx_dubbo_arg_t             *arg;
    ngx_keyval_t                *kv;
    ngx_uint_t                   n;

    size_t                       len = 0;
    ngx_int_t                    size;
    ngx_buf_t                   *body = NULL;
    ngx_chain_t                 *cl;

    ngx_http_variable_value_t   *vv;
    size_t                       i;

    ctx = ngx_http_dubbo_get_ctx(r);
    dubbo_c = ctx->connection;

    //read body
    for (cl = in; cl; cl = cl->next) {
        len += ngx_buf_size(cl->buf);
    }

    if (len > 0) {
        body = ngx_create_temp_buf(r->pool, len);
        if (body == NULL) {
            return NGX_ERROR;
        }
        for (cl = in; cl; cl = cl->next) {
            if (cl->buf->in_file) {
                size = ngx_read_file(cl->buf->file, body->last,
                        cl->buf->file_last - cl->buf->file_pos, cl->buf->file_pos);

                if (size == NGX_ERROR) {
                    return NGX_ERROR;
                }

                body->last += size;
            } else {
                body->last = ngx_cpymem(body->last, cl->buf->pos, cl->buf->last - cl->buf->pos);
            }
        }
    }

    if (dubbo_c == NULL) {
        return NGX_ERROR;
    }

    multi_r = ngx_create_multi_request(pc, r);
    if (multi_r == NULL) {
        return NGX_ERROR;
    }

    *multi_rptr = multi_r;
    
    dlcf = ngx_http_get_module_loc_conf(r, ngx_http_dubbo_module);

    args = ngx_array_create(dubbo_c->temp_pool, 1, sizeof(ngx_dubbo_arg_t));
    if (args == NULL) {
        return NGX_ERROR;
    }

    arg = (ngx_dubbo_arg_t*)ngx_array_push(args);
    if (arg == NULL) {
        return NGX_ERROR;
    }

    if (dlcf->args_in == NULL) {
        n = 1;
    } else {
        n = dlcf->args_in->nelts;
    }

    arg->type = DUBBO_ARG_MAP;
    arg->value.m = ngx_array_create(dubbo_c->temp_pool, n, sizeof(ngx_keyval_t));

    if (body && dlcf->pass_body) {
        kv = (ngx_keyval_t*)ngx_array_push(arg->value.m);
        if (kv == NULL) {
            return NGX_ERROR;
        }

        kv->key.data = ngx_http_dubbo_str_body.data;
        kv->key.len = ngx_http_dubbo_str_body.len;
        kv->value.data = body->pos;
        kv->value.len = body->last - body->pos;
    }

    if (dlcf->pass_all_headers) {
        //pass all
        ngx_uint_t                              i;
        ngx_list_part_t                        *part;
        ngx_table_elt_t                        *header;

        part = &r->headers_in.headers.part;
        header = part->elts;

        for (i = 0; /* void */ ; i++) {
            if (i >= part->nelts) {
                if (part->next == NULL) {
                    break;
                }

                part = part->next;
                header = part->elts;
                i = 0;
            }

            kv = (ngx_keyval_t*)ngx_array_push(arg->value.m);
            if (kv == NULL) {
                return NGX_ERROR;
            }

            kv->key.data = header[i].lowcase_key;
            kv->key.len = header[i].key.len;
            kv->value.data = header[i].value.data;
            kv->value.len = header[i].value.len;
        }
    }

    if (dlcf->args_in != NULL) {
        //pass set
        ngx_http_dubbo_arg_t *args_in = dlcf->args_in->elts;
        for (i = 0; i < dlcf->args_in->nelts; i++) {
            kv = (ngx_keyval_t*)ngx_array_push(arg->value.m);
            if (kv == NULL) {
                return NGX_ERROR;
            }

            //get key value
            if (args_in[i].key_var_index != NGX_CONF_UNSET) {
                vv = ngx_http_get_indexed_variable(r, args_in[i].key_var_index);
                if (vv == NULL || vv->not_found) {
                    ngx_log_error(NGX_LOG_WARN, r->connection->log, 0
                            , "dubbo: cannot found pass set key from variable index %ui, %V"
                            , args_in[i].key_var_index, &args_in[i].key);
                    ngx_str_null(&kv->key);
                } else {
                    kv->key.data = vv->data;
                    kv->key.len = vv->len;
                }
            } else {
                kv->key = args_in[i].key;
            }

            if (args_in[i].value_var_index != NGX_CONF_UNSET) {
                vv = ngx_http_get_indexed_variable(r, args_in[i].value_var_index);
                if (vv == NULL || vv->not_found) {
                    ngx_log_error(NGX_LOG_WARN, r->connection->log, 0
                            , "dubbo: cannot found pass set key from variable index %ui, %V"
                            , args_in[i].value_var_index, &args_in[i].value);
                    ngx_str_null(&kv->value);
                } else {
                    kv->value.data = vv->data;
                    kv->value.len = vv->len;
                }
            } else {
                kv->value = args_in[i].value;
            }
        }
    }

    if (NGX_ERROR == ngx_dubbo_encode_request(dubbo_c, &dlcf->service_name, &dlcf->service_version, &dlcf->method, args, multi_r)) {
        ngx_log_error(NGX_LOG_ERR, dubbo_c->log, 0,
                      "dubbo: encode request failed");
        return NGX_ERROR;
    }

    return NGX_OK;
}