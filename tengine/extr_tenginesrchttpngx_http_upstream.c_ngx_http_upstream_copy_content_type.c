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
struct TYPE_8__ {int len; char* data; } ;
struct TYPE_11__ {TYPE_1__ value; } ;
typedef  TYPE_4__ ngx_table_elt_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_9__ {int len; char* data; } ;
struct TYPE_10__ {int content_type_len; TYPE_2__ charset; int /*<<< orphan*/ * content_type_lowcase; TYPE_1__ content_type; } ;
struct TYPE_12__ {TYPE_3__ headers_out; } ;
typedef  TYPE_5__ ngx_http_request_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 
 scalar_t__ ngx_strncasecmp (char*,char*,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_upstream_copy_content_type(ngx_http_request_t *r, ngx_table_elt_t *h,
    ngx_uint_t offset)
{
    u_char  *p, *last;

    r->headers_out.content_type_len = h->value.len;
    r->headers_out.content_type = h->value;
    r->headers_out.content_type_lowcase = NULL;

    for (p = h->value.data; *p; p++) {

        if (*p != ';') {
            continue;
        }

        last = p;

        while (*++p == ' ') { /* void */ }

        if (*p == '\0') {
            return NGX_OK;
        }

        if (ngx_strncasecmp(p, (u_char *) "charset=", 8) != 0) {
            continue;
        }

        p += 8;

        r->headers_out.content_type_len = last - h->value.data;

        if (*p == '"') {
            p++;
        }

        last = h->value.data + h->value.len;

        if (*(last - 1) == '"') {
            last--;
        }

        r->headers_out.charset.len = last - p;
        r->headers_out.charset.data = p;

        return NGX_OK;
    }

    return NGX_OK;
}