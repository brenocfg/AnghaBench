#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_5__ {TYPE_3__* filter_ctx; int /*<<< orphan*/  output_filter; } ;
struct TYPE_6__ {TYPE_1__ output; } ;
typedef  TYPE_2__ ngx_http_upstream_t ;
struct TYPE_7__ {TYPE_2__* upstream; } ;
typedef  TYPE_3__ ngx_http_request_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_http_dubbo_body_output_filter ; 

__attribute__((used)) static ngx_int_t
ngx_http_dubbo_create_request(ngx_http_request_t *r)
{
    ngx_http_upstream_t     *u;

    u = r->upstream;

    u->output.output_filter = ngx_http_dubbo_body_output_filter;
    u->output.filter_ctx = r;

    return NGX_OK;
}