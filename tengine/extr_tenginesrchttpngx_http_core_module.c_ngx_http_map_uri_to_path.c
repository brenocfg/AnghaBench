#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_17__ ;

/* Type definitions */
typedef  char u_char ;
struct TYPE_24__ {size_t len; char* data; } ;
typedef  TYPE_6__ ngx_str_t ;
struct TYPE_23__ {size_t len; scalar_t__ data; } ;
struct TYPE_25__ {TYPE_5__ uri; scalar_t__ add_uri_to_alias; int /*<<< orphan*/  pool; TYPE_1__* connection; int /*<<< orphan*/  valid_location; } ;
typedef  TYPE_7__ ngx_http_request_t ;
struct TYPE_20__ {size_t len; int /*<<< orphan*/  data; } ;
struct TYPE_26__ {size_t alias; TYPE_4__* root_values; TYPE_3__* root_lengths; TYPE_2__ root; int /*<<< orphan*/  name; } ;
typedef  TYPE_8__ ngx_http_core_loc_conf_t ;
struct TYPE_22__ {int /*<<< orphan*/  elts; } ;
struct TYPE_21__ {int /*<<< orphan*/  elts; } ;
struct TYPE_19__ {int /*<<< orphan*/  log; } ;
struct TYPE_18__ {int /*<<< orphan*/  prefix; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 size_t NGX_MAX_SIZE_T_VALUE ; 
 scalar_t__ NGX_OK ; 
 char* ngx_copy (char*,int /*<<< orphan*/ ,size_t) ; 
 char* ngx_cpystrn (char*,scalar_t__,size_t) ; 
 TYPE_17__* ngx_cycle ; 
 scalar_t__ ngx_get_full_name (int /*<<< orphan*/ ,TYPE_6__*,TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 TYPE_8__* ngx_http_get_module_loc_conf (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_http_script_run (TYPE_7__*,TYPE_6__*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 char* ngx_pnalloc (int /*<<< orphan*/ ,size_t) ; 

u_char *
ngx_http_map_uri_to_path(ngx_http_request_t *r, ngx_str_t *path,
    size_t *root_length, size_t reserved)
{
    u_char                    *last;
    size_t                     alias;
    ngx_http_core_loc_conf_t  *clcf;

    clcf = ngx_http_get_module_loc_conf(r, ngx_http_core_module);

    alias = clcf->alias;

    if (alias && !r->valid_location) {
        ngx_log_error(NGX_LOG_ALERT, r->connection->log, 0,
                      "\"alias\" cannot be used in location \"%V\" "
                      "where URI was rewritten", &clcf->name);
        return NULL;
    }

    if (clcf->root_lengths == NULL) {

        *root_length = clcf->root.len;

        path->len = clcf->root.len + reserved + r->uri.len - alias + 1;

        path->data = ngx_pnalloc(r->pool, path->len);
        if (path->data == NULL) {
            return NULL;
        }

        last = ngx_copy(path->data, clcf->root.data, clcf->root.len);

    } else {

        if (alias == NGX_MAX_SIZE_T_VALUE) {
            reserved += r->add_uri_to_alias ? r->uri.len + 1 : 1;

        } else {
            reserved += r->uri.len - alias + 1;
        }

        if (ngx_http_script_run(r, path, clcf->root_lengths->elts, reserved,
                                clcf->root_values->elts)
            == NULL)
        {
            return NULL;
        }

        if (ngx_get_full_name(r->pool, (ngx_str_t *) &ngx_cycle->prefix, path)
            != NGX_OK)
        {
            return NULL;
        }

        *root_length = path->len - reserved;
        last = path->data + *root_length;

        if (alias == NGX_MAX_SIZE_T_VALUE) {
            if (!r->add_uri_to_alias) {
                *last = '\0';
                return last;
            }

            alias = 0;
        }
    }

    last = ngx_cpystrn(last, r->uri.data + alias, r->uri.len - alias + 1);

    return last;
}