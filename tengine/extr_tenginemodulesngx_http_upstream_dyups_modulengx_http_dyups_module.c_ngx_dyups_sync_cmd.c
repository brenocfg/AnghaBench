#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
typedef  scalar_t__ ngx_uint_t ;
struct TYPE_14__ {scalar_t__ len; scalar_t__ data; } ;
typedef  TYPE_1__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_pool_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_15__ {int temporary; scalar_t__ last; scalar_t__ end; scalar_t__ pos; scalar_t__ start; } ;
typedef  TYPE_2__ ngx_buf_t ;
struct TYPE_13__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ NGX_DYUPS_ADD ; 
 scalar_t__ NGX_DYUPS_DELETE ; 
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_HTTP_OK ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 scalar_t__ NGX_OK ; 
 TYPE_12__* ngx_cycle ; 
 scalar_t__ ngx_dyups_do_delete (TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ ngx_dyups_do_update (TYPE_1__*,TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_1__*,TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static ngx_int_t
ngx_dyups_sync_cmd(ngx_pool_t *pool, ngx_str_t *name, ngx_str_t *content,
    ngx_uint_t flag)
{
    ngx_int_t     rc;
    ngx_buf_t     body;
    ngx_str_t     rv;

    if (flag == NGX_DYUPS_DELETE) {

        rc = ngx_dyups_do_delete(name, &rv);

        ngx_log_error(NGX_LOG_INFO, ngx_cycle->log, 0,
                       "[dyups] sync del: %V rv: %V rc: %i",
                       name, &rv, rc);

        if (rc != NGX_HTTP_OK) {
            return NGX_ERROR;
        }

        return NGX_OK;

    } else if (flag == NGX_DYUPS_ADD) {

        body.start = body.pos = content->data;
        body.end = body.last = content->data + content->len;
        body.temporary = 1;

        rc = ngx_dyups_do_update(name, &body, &rv);

        ngx_log_error(NGX_LOG_INFO, ngx_cycle->log, 0,
                      "[dyups] sync add: %V rv: %V rc: %i",
                      name, &rv, rc);

        if (rc != NGX_HTTP_OK) {
            return NGX_ERROR;
        }

        return NGX_OK;
    }

    return NGX_ERROR;
}