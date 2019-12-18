#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_10__ {int header_only; int /*<<< orphan*/  method_name; int /*<<< orphan*/  method; int /*<<< orphan*/  args; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_11__ {TYPE_1__* mirror; } ;
typedef  TYPE_3__ ngx_http_mirror_loc_conf_t ;
struct TYPE_9__ {size_t nelts; int /*<<< orphan*/ * elts; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_DECLINED ; 
 int /*<<< orphan*/  NGX_HTTP_INTERNAL_SERVER_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_SUBREQUEST_BACKGROUND ; 
 scalar_t__ NGX_OK ; 
 TYPE_3__* ngx_http_get_module_loc_conf (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_mirror_module ; 
 scalar_t__ ngx_http_subrequest (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_http_mirror_handler_internal(ngx_http_request_t *r)
{
    ngx_str_t                   *name;
    ngx_uint_t                   i;
    ngx_http_request_t          *sr;
    ngx_http_mirror_loc_conf_t  *mlcf;

    mlcf = ngx_http_get_module_loc_conf(r, ngx_http_mirror_module);

    name = mlcf->mirror->elts;

    for (i = 0; i < mlcf->mirror->nelts; i++) {
        if (ngx_http_subrequest(r, &name[i], &r->args, &sr, NULL,
                                NGX_HTTP_SUBREQUEST_BACKGROUND)
            != NGX_OK)
        {
            return NGX_HTTP_INTERNAL_SERVER_ERROR;
        }

        sr->header_only = 1;
        sr->method = r->method;
        sr->method_name = r->method_name;
    }

    return NGX_DECLINED;
}