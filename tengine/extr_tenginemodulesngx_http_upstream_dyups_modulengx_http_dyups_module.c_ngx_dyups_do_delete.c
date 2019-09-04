#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_6__ {scalar_t__ deleted; } ;
typedef  TYPE_1__ ngx_http_dyups_srv_conf_t ;
struct TYPE_7__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_HTTP_NOT_FOUND ; 
 int /*<<< orphan*/  NGX_HTTP_OK ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG ; 
 TYPE_5__* ngx_cycle ; 
 TYPE_1__* ngx_dyups_find_upstream (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_dyups_mark_upstream_delete (TYPE_1__*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ngx_str_set (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static ngx_int_t
ngx_dyups_do_delete(ngx_str_t *name, ngx_str_t *rv)
{
    ngx_int_t                   dumy;
    ngx_http_dyups_srv_conf_t  *duscf;

    duscf = ngx_dyups_find_upstream(name, &dumy);

    if (duscf == NULL || duscf->deleted) {

        ngx_log_error(NGX_LOG_DEBUG, ngx_cycle->log, 0,
                      "[dyups] not find upstream %V %p", name, duscf);

        ngx_str_set(rv, "not found uptream");
        return NGX_HTTP_NOT_FOUND;
    }

    ngx_dyups_mark_upstream_delete(duscf);

    ngx_str_set(rv, "success");

    return NGX_HTTP_OK;
}