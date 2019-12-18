#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  char u_char ;
typedef  size_t ngx_uint_t ;
struct TYPE_13__ {scalar_t__ len; char* data; } ;
struct TYPE_10__ {TYPE_5__ value; int /*<<< orphan*/  key; } ;
typedef  TYPE_2__ ngx_table_elt_t ;
struct TYPE_11__ {scalar_t__ len; char* data; } ;
typedef  TYPE_3__ ngx_str_t ;
typedef  size_t ngx_int_t ;
struct TYPE_12__ {size_t nelts; TYPE_1__* pool; TYPE_2__** elts; } ;
typedef  TYPE_4__ ngx_array_t ;
struct TYPE_9__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 size_t NGX_DECLINED ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,TYPE_5__*) ; 
 scalar_t__ ngx_strncasecmp (char*,char*,scalar_t__) ; 

ngx_int_t
ngx_http_parse_multi_header_lines(ngx_array_t *headers, ngx_str_t *name,
    ngx_str_t *value)
{
    ngx_uint_t         i;
    u_char            *start, *last, *end, ch;
    ngx_table_elt_t  **h;

    h = headers->elts;

    for (i = 0; i < headers->nelts; i++) {

        ngx_log_debug2(NGX_LOG_DEBUG_HTTP, headers->pool->log, 0,
                       "parse header: \"%V: %V\"", &h[i]->key, &h[i]->value);

        if (name->len > h[i]->value.len) {
            continue;
        }

        start = h[i]->value.data;
        end = h[i]->value.data + h[i]->value.len;

        while (start < end) {

            if (ngx_strncasecmp(start, name->data, name->len) != 0) {
                goto skip;
            }

            for (start += name->len; start < end && *start == ' '; start++) {
                /* void */
            }

            if (value == NULL) {
                if (start == end || *start == ',') {
                    return i;
                }

                goto skip;
            }

            if (start == end || *start++ != '=') {
                /* the invalid header value */
                goto skip;
            }

            while (start < end && *start == ' ') { start++; }

            for (last = start; last < end && *last != ';'; last++) {
                /* void */
            }

            value->len = last - start;
            value->data = start;

            return i;

        skip:

            while (start < end) {
                ch = *start++;
                if (ch == ';' || ch == ',') {
                    break;
                }
            }

            while (start < end && *start == ' ') { start++; }
        }
    }

    return NGX_DECLINED;
}