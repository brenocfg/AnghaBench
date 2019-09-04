#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_15__ {TYPE_7__* location; int /*<<< orphan*/  headers; } ;
struct TYPE_13__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_16__ {TYPE_4__ headers_out; TYPE_2__ uri; int /*<<< orphan*/  pool; } ;
typedef  TYPE_5__ ngx_http_request_t ;
struct TYPE_12__ {int len; } ;
struct TYPE_17__ {TYPE_1__ root; int /*<<< orphan*/ * root_lengths; int /*<<< orphan*/  alias; } ;
typedef  TYPE_6__ ngx_http_core_loc_conf_t ;
struct TYPE_14__ {int /*<<< orphan*/ * data; int /*<<< orphan*/  len; } ;
struct TYPE_18__ {int hash; TYPE_3__ value; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_http_clear_location (TYPE_5__*) ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 TYPE_6__* ngx_http_get_module_loc_conf (TYPE_5__*,int /*<<< orphan*/ ) ; 
 TYPE_7__* ngx_list_push (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_pnalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_str_set (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static ngx_int_t
ngx_http_dav_location(ngx_http_request_t *r, u_char *path)
{
    u_char                    *location;
    ngx_http_core_loc_conf_t  *clcf;

    r->headers_out.location = ngx_list_push(&r->headers_out.headers);
    if (r->headers_out.location == NULL) {
        return NGX_ERROR;
    }

    clcf = ngx_http_get_module_loc_conf(r, ngx_http_core_module);

    if (!clcf->alias && clcf->root_lengths == NULL) {
        location = path + clcf->root.len;

    } else {
        location = ngx_pnalloc(r->pool, r->uri.len);
        if (location == NULL) {
            ngx_http_clear_location(r);
            return NGX_ERROR;
        }

        ngx_memcpy(location, r->uri.data, r->uri.len);
    }

    r->headers_out.location->hash = 1;
    ngx_str_set(&r->headers_out.location->key, "Location");
    r->headers_out.location->value.len = r->uri.len;
    r->headers_out.location->value.data = location;

    return NGX_OK;
}