#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_14__ {int len; int /*<<< orphan*/  data; } ;
struct TYPE_12__ {TYPE_4__ name; int /*<<< orphan*/  value; } ;
typedef  TYPE_2__ ngx_http_v2_header_t ;
struct TYPE_13__ {TYPE_1__* connection; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_11__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_DECLINED ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 int /*<<< orphan*/  ngx_http_v2_parse_authority (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_v2_parse_method (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_v2_parse_path (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_v2_parse_scheme (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_memcmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_v2_pseudo_header(ngx_http_request_t *r, ngx_http_v2_header_t *header)
{
    header->name.len--;
    header->name.data++;

    switch (header->name.len) {
    case 4:
        if (ngx_memcmp(header->name.data, "path", sizeof("path") - 1)
            == 0)
        {
            return ngx_http_v2_parse_path(r, &header->value);
        }

        break;

    case 6:
        if (ngx_memcmp(header->name.data, "method", sizeof("method") - 1)
            == 0)
        {
            return ngx_http_v2_parse_method(r, &header->value);
        }

        if (ngx_memcmp(header->name.data, "scheme", sizeof("scheme") - 1)
            == 0)
        {
            return ngx_http_v2_parse_scheme(r, &header->value);
        }

        break;

    case 9:
        if (ngx_memcmp(header->name.data, "authority", sizeof("authority") - 1)
            == 0)
        {
            return ngx_http_v2_parse_authority(r, &header->value);
        }

        break;
    }

    ngx_log_error(NGX_LOG_INFO, r->connection->log, 0,
                  "client sent unknown pseudo-header \":%V\"",
                  &header->name);

    return NGX_DECLINED;
}