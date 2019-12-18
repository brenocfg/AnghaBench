#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_5__ {int len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_6__ {int /*<<< orphan*/  flag; } ;
typedef  TYPE_2__ ngx_http_upstream_check_status_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_CHECK_STATUS_DOWN ; 
 int /*<<< orphan*/  NGX_CHECK_STATUS_UP ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 scalar_t__ ngx_strncasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_upstream_check_status_command_status(
    ngx_http_upstream_check_status_ctx_t *ctx, ngx_str_t *value)
{
    if (value->len == (sizeof("down") - 1)
        && ngx_strncasecmp(value->data, (u_char *) "down", value->len) == 0) {

        ctx->flag |= NGX_CHECK_STATUS_DOWN;

    } else if (value->len == (sizeof("up") - 1)
               && ngx_strncasecmp(value->data, (u_char *) "up", value->len)
                  == 0) {

        ctx->flag |= NGX_CHECK_STATUS_UP;

    } else {
        return NGX_ERROR;
    }

    return NGX_OK;
}