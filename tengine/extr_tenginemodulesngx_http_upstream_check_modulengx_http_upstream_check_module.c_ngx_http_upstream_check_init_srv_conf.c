#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_15__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_str_t ;
struct TYPE_22__ {int /*<<< orphan*/ * srv_conf; } ;
typedef  TYPE_5__ ngx_http_upstream_srv_conf_t ;
struct TYPE_21__ {scalar_t__ status_alive; } ;
struct TYPE_19__ {scalar_t__ len; scalar_t__ data; } ;
struct TYPE_23__ {scalar_t__ port; scalar_t__ fall_count; scalar_t__ rise_count; scalar_t__ check_interval; scalar_t__ check_timeout; scalar_t__ check_keepalive_requests; TYPE_4__ code; TYPE_2__ send; TYPE_1__* fastcgi_params; TYPE_8__* check_type_conf; } ;
typedef  TYPE_6__ ngx_http_upstream_check_srv_conf_t ;
struct TYPE_24__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_7__ ngx_conf_t ;
struct TYPE_20__ {scalar_t__ data; scalar_t__ len; } ;
struct TYPE_25__ {scalar_t__ default_status_alive; TYPE_3__ default_send; } ;
typedef  TYPE_8__ ngx_check_conf_t ;
struct TYPE_26__ {scalar_t__ pos; scalar_t__ last; } ;
typedef  TYPE_9__ ngx_buf_t ;
struct TYPE_18__ {int nelts; int /*<<< orphan*/  elts; } ;
struct TYPE_17__ {scalar_t__ data; scalar_t__ len; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_CONF_UNSET_MSEC ; 
 TYPE_8__* NGX_CONF_UNSET_PTR ; 
 scalar_t__ NGX_CONF_UNSET_UINT ; 
 TYPE_15__ fastcgi_default_request ; 
 TYPE_6__* ngx_http_conf_upstream_srv_conf (TYPE_5__*,int /*<<< orphan*/ ) ; 
 TYPE_8__* ngx_http_get_check_type_conf (int /*<<< orphan*/ *) ; 
 TYPE_9__* ngx_http_upstream_check_create_fastcgi_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_http_upstream_check_module ; 
 int /*<<< orphan*/  ngx_str_set (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static char *
ngx_http_upstream_check_init_srv_conf(ngx_conf_t *cf, void *conf)
{
    ngx_str_t                           s;
    ngx_buf_t                          *b;
    ngx_check_conf_t                   *check;
    ngx_http_upstream_srv_conf_t       *us = conf;
    ngx_http_upstream_check_srv_conf_t *ucscf;

    if (us->srv_conf == NULL) {
        return NGX_CONF_OK;
    }

    ucscf = ngx_http_conf_upstream_srv_conf(us, ngx_http_upstream_check_module);

    if (ucscf->port == NGX_CONF_UNSET_UINT) {
        ucscf->port = 0;
    }

    if (ucscf->fall_count == NGX_CONF_UNSET_UINT) {
        ucscf->fall_count = 2;
    }

    if (ucscf->rise_count == NGX_CONF_UNSET_UINT) {
        ucscf->rise_count = 5;
    }

    if (ucscf->check_interval == NGX_CONF_UNSET_MSEC) {
        ucscf->check_interval = 0;
    }

    if (ucscf->check_timeout == NGX_CONF_UNSET_MSEC) {
        ucscf->check_timeout = 1000;
    }

    if (ucscf->check_keepalive_requests == NGX_CONF_UNSET_UINT) {
        ucscf->check_keepalive_requests = 1;
    }

    if (ucscf->check_type_conf == NGX_CONF_UNSET_PTR) {
        ucscf->check_type_conf = NULL;
    }

    check = ucscf->check_type_conf;

    if (check) {
        if (ucscf->send.len == 0) {
            ngx_str_set(&s, "fastcgi");

            if (check == ngx_http_get_check_type_conf(&s)) {

                if (ucscf->fastcgi_params->nelts == 0) {
                    ucscf->send.data = fastcgi_default_request.data;
                    ucscf->send.len = fastcgi_default_request.len;

                } else {
                    b = ngx_http_upstream_check_create_fastcgi_request(
                            cf->pool, ucscf->fastcgi_params->elts,
                            ucscf->fastcgi_params->nelts / 2);
                    if (b == NULL) {
                        return NGX_CONF_ERROR;
                    }

                    ucscf->send.data = b->pos;
                    ucscf->send.len = b->last - b->pos;
                }
            } else {
                ucscf->send.data = check->default_send.data;
                ucscf->send.len = check->default_send.len;
            }
        }


        if (ucscf->code.status_alive == 0) {
            ucscf->code.status_alive = check->default_status_alive;
        }
    }

    return NGX_CONF_OK;
}