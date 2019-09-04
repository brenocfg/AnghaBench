#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  scalar_t__ off_t ;
struct TYPE_5__ {scalar_t__ header_size; TYPE_1__* connection; } ;
typedef  TYPE_2__ ngx_http_request_t ;
typedef  int /*<<< orphan*/  ngx_http_log_op_t ;
struct TYPE_4__ {scalar_t__ sent; } ;

/* Variables and functions */
 int /*<<< orphan*/ * ngx_sprintf (int /*<<< orphan*/ *,char*,scalar_t__) ; 

__attribute__((used)) static u_char *
ngx_http_log_body_bytes_sent(ngx_http_request_t *r, u_char *buf,
    ngx_http_log_op_t *op)
{
    off_t  length;

    length = r->connection->sent - r->header_size;

    if (length > 0) {
        return ngx_sprintf(buf, "%O", length);
    }

    *buf = '0';

    return buf + 1;
}