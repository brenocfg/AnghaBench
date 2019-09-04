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
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_5__ {size_t len; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ ngx_str_t ;
typedef  int ngx_int_t ;
struct TYPE_6__ {int port; int /*<<< orphan*/  ip; } ;
typedef  TYPE_2__ ngx_http_tfs_inet_t ;

/* Variables and functions */
 int /*<<< orphan*/  INADDR_NONE ; 
 int NGX_ERROR ; 
 int NGX_OK ; 
 int ngx_atoi (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  ngx_inet_addr (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * ngx_strlchr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char) ; 

ngx_int_t
ngx_http_tfs_parse_inet(ngx_str_t *u, ngx_http_tfs_inet_t *addr)
{
    u_char    *port, *last;
    size_t     len;
    ngx_int_t  n;

    last = u->data + u->len;

    port = ngx_strlchr(u->data, last, ':');

    if (port) {
        port++;

        len = last - port;

        if (len == 0) {
            return NGX_ERROR;
        }

        n = ngx_atoi(port, len);

        if (n < 1 || n > 65535) {
            return NGX_ERROR;
        }

        addr->port = n;

        addr->ip = ngx_inet_addr(u->data, u->len - len - 1);
        if (addr->ip == INADDR_NONE) {
            return NGX_ERROR;
        }

    } else {
        return NGX_ERROR;
    }

    return NGX_OK;
}