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
typedef  char u_char ;
typedef  int /*<<< orphan*/  ngx_uint_t ;
struct TYPE_9__ {int len; int /*<<< orphan*/ * data; } ;
struct TYPE_10__ {TYPE_2__ value; } ;
typedef  TYPE_3__ ngx_table_elt_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_11__ {int buffering; TYPE_1__* conf; } ;
typedef  TYPE_4__ ngx_http_upstream_t ;
struct TYPE_12__ {TYPE_4__* upstream; } ;
typedef  TYPE_5__ ngx_http_request_t ;
struct TYPE_8__ {int ignore_headers; scalar_t__ change_buffering; } ;

/* Variables and functions */
 int NGX_HTTP_UPSTREAM_IGN_XA_BUFFERING ; 
 int /*<<< orphan*/  NGX_OK ; 
 char ngx_tolower (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_http_upstream_process_buffering(ngx_http_request_t *r, ngx_table_elt_t *h,
    ngx_uint_t offset)
{
    u_char                c0, c1, c2;
    ngx_http_upstream_t  *u;

    u = r->upstream;

    if (u->conf->ignore_headers & NGX_HTTP_UPSTREAM_IGN_XA_BUFFERING) {
        return NGX_OK;
    }

    if (u->conf->change_buffering) {

        if (h->value.len == 2) {
            c0 = ngx_tolower(h->value.data[0]);
            c1 = ngx_tolower(h->value.data[1]);

            if (c0 == 'n' && c1 == 'o') {
                u->buffering = 0;
            }

        } else if (h->value.len == 3) {
            c0 = ngx_tolower(h->value.data[0]);
            c1 = ngx_tolower(h->value.data[1]);
            c2 = ngx_tolower(h->value.data[2]);

            if (c0 == 'y' && c1 == 'e' && c2 == 's') {
                u->buffering = 1;
            }
        }
    }

    return NGX_OK;
}