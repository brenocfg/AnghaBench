#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_char ;
struct TYPE_9__ {int len; scalar_t__* data; } ;
typedef  TYPE_3__ ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_7__ {int len; scalar_t__* data; } ;
struct TYPE_10__ {TYPE_2__* buf; scalar_t__* pos; TYPE_1__ looked; } ;
typedef  TYPE_4__ ngx_http_sub_ctx_t ;
struct TYPE_8__ {scalar_t__* last; } ;

/* Variables and functions */
 scalar_t__ NGX_AGAIN ; 
 scalar_t__ NGX_DECLINED ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_tolower (scalar_t__) ; 

__attribute__((used)) static ngx_int_t
ngx_http_sub_match(ngx_http_sub_ctx_t *ctx, ngx_int_t start, ngx_str_t *m)
{
    u_char  *p, *last, *pat, *pat_end;

    pat = m->data;
    pat_end = m->data + m->len;

    if (start >= 0) {
        p = ctx->pos + start;

    } else {
        last = ctx->looked.data + ctx->looked.len;
        p = last + start;

        while (p < last && pat < pat_end) {
            if (ngx_tolower(*p) != *pat) {
                return NGX_DECLINED;
            }

            p++;
            pat++;
        }

        p = ctx->pos;
    }

    while (p < ctx->buf->last && pat < pat_end) {
        if (ngx_tolower(*p) != *pat) {
            return NGX_DECLINED;
        }

        p++;
        pat++;
    }

    if (pat != pat_end) {
        /* partial match */
        return NGX_AGAIN;
    }

    return NGX_OK;
}