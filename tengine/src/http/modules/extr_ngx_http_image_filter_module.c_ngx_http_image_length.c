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
struct TYPE_8__ {TYPE_1__* content_length; scalar_t__ content_length_n; } ;
struct TYPE_9__ {TYPE_2__ headers_out; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_10__ {scalar_t__ pos; scalar_t__ last; } ;
typedef  TYPE_4__ ngx_buf_t ;
struct TYPE_7__ {scalar_t__ hash; } ;

/* Variables and functions */

__attribute__((used)) static void
ngx_http_image_length(ngx_http_request_t *r, ngx_buf_t *b)
{
    r->headers_out.content_length_n = b->last - b->pos;

    if (r->headers_out.content_length) {
        r->headers_out.content_length->hash = 0;
    }

    r->headers_out.content_length = NULL;
}