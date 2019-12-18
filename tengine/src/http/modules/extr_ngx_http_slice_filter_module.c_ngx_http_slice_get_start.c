#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  char u_char ;
typedef  char off_t ;
struct TYPE_7__ {int len; char* data; } ;
struct TYPE_8__ {TYPE_2__ value; } ;
typedef  TYPE_3__ ngx_table_elt_t ;
struct TYPE_6__ {TYPE_3__* range; scalar_t__ if_range; } ;
struct TYPE_9__ {TYPE_1__ headers_in; } ;
typedef  TYPE_4__ ngx_http_request_t ;

/* Variables and functions */
 int NGX_MAX_OFF_T_VALUE ; 
 scalar_t__ ngx_strchr (char*,char) ; 
 scalar_t__ ngx_strncasecmp (char*,char*,int) ; 

__attribute__((used)) static off_t
ngx_http_slice_get_start(ngx_http_request_t *r)
{
    off_t             start, cutoff, cutlim;
    u_char           *p;
    ngx_table_elt_t  *h;

    if (r->headers_in.if_range) {
        return 0;
    }

    h = r->headers_in.range;

    if (h == NULL
        || h->value.len < 7
        || ngx_strncasecmp(h->value.data, (u_char *) "bytes=", 6) != 0)
    {
        return 0;
    }

    p = h->value.data + 6;

    if (ngx_strchr(p, ',')) {
        return 0;
    }

    while (*p == ' ') { p++; }

    if (*p == '-') {
        return 0;
    }

    cutoff = NGX_MAX_OFF_T_VALUE / 10;
    cutlim = NGX_MAX_OFF_T_VALUE % 10;

    start = 0;

    while (*p >= '0' && *p <= '9') {
        if (start >= cutoff && (start > cutoff || *p - '0' > cutlim)) {
            return 0;
        }

        start = start * 10 + (*p++ - '0');
    }

    return start;
}