#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int len; char* data; } ;
struct TYPE_9__ {TYPE_5__ value; } ;
typedef  TYPE_3__ ngx_table_elt_t ;
typedef  int ngx_int_t ;
struct TYPE_8__ {TYPE_3__* depth; } ;
struct TYPE_10__ {TYPE_1__* connection; TYPE_2__ headers_in; } ;
typedef  TYPE_4__ ngx_http_request_t ;
struct TYPE_7__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int NGX_HTTP_DAV_INFINITY_DEPTH ; 
 int NGX_HTTP_DAV_INVALID_DEPTH ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_5__*) ; 
 scalar_t__ ngx_strcmp (char*,char*) ; 

__attribute__((used)) static ngx_int_t
ngx_http_dav_depth(ngx_http_request_t *r, ngx_int_t dflt)
{
    ngx_table_elt_t  *depth;

    depth = r->headers_in.depth;

    if (depth == NULL) {
        return dflt;
    }

    if (depth->value.len == 1) {

        if (depth->value.data[0] == '0') {
            return 0;
        }

        if (depth->value.data[0] == '1') {
            return 1;
        }

    } else {

        if (depth->value.len == sizeof("infinity") - 1
            && ngx_strcmp(depth->value.data, "infinity") == 0)
        {
            return NGX_HTTP_DAV_INFINITY_DEPTH;
        }
    }

    ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                  "client sent invalid \"Depth\" header: \"%V\"",
                  &depth->value);

    return NGX_HTTP_DAV_INVALID_DEPTH;
}