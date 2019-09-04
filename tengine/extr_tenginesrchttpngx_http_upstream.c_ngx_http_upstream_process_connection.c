#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  ngx_uint_t ;
struct TYPE_10__ {scalar_t__ len; scalar_t__ data; } ;
struct TYPE_11__ {TYPE_3__ value; } ;
typedef  TYPE_4__ ngx_table_elt_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_12__ {TYPE_2__* upstream; } ;
typedef  TYPE_5__ ngx_http_request_t ;
struct TYPE_8__ {int connection_close; TYPE_4__* connection; } ;
struct TYPE_9__ {TYPE_1__ headers_in; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/ * ngx_strlcasestrn (scalar_t__,scalar_t__,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_upstream_process_connection(ngx_http_request_t *r, ngx_table_elt_t *h,
    ngx_uint_t offset)
{
    r->upstream->headers_in.connection = h;

    if (ngx_strlcasestrn(h->value.data, h->value.data + h->value.len,
                         (u_char *) "close", 5 - 1)
        != NULL)
    {
        r->upstream->headers_in.connection_close = 1;
    }

    return NGX_OK;
}