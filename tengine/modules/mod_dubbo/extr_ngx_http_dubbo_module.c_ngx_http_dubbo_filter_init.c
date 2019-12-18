#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_5__ {int length; } ;
typedef  TYPE_2__ ngx_http_upstream_t ;
struct TYPE_6__ {TYPE_1__* request; } ;
typedef  TYPE_3__ ngx_http_dubbo_ctx_t ;
struct TYPE_4__ {TYPE_2__* upstream; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 

__attribute__((used)) static ngx_int_t
ngx_http_dubbo_filter_init(void *data)
{
    ngx_http_dubbo_ctx_t  *ctx = data;

    ngx_http_upstream_t  *u;

    u = ctx->request->upstream;

    u->length = 1;

    return NGX_OK;
}