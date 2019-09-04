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
typedef  int time_t ;
typedef  size_t ngx_uint_t ;
struct TYPE_5__ {size_t len; int* data; } ;
typedef  TYPE_1__ ngx_str_t ;
struct TYPE_6__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_2__ ngx_http_request_t ;

/* Variables and functions */
 int* ngx_pcalloc (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void
ngx_http_session_sticky_tmtoa(ngx_http_request_t *r, ngx_str_t *str, time_t t)
{
    time_t      temp;
    ngx_uint_t  len;

    len = 0;
    temp = t;
    while (temp) {
        len++;
        temp /= 10;
    }

    str->len = len;
    str->data = ngx_pcalloc(r->pool, len);
    if (str->data == NULL) {
        return;
    }

    while (t) {
        str->data[--len] = t % 10 + '0';
        t /= 10;
    }
}