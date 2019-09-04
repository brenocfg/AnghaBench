#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_7__ {scalar_t__ connect_port_n; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_8__ {TYPE_1__* allow_ports; scalar_t__ allow_port_all; } ;
typedef  TYPE_3__ ngx_http_proxy_connect_loc_conf_t ;
typedef  scalar_t__ in_port_t ;
struct TYPE_6__ {scalar_t__** elts; size_t nelts; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_HTTP_FORBIDDEN ; 
 int /*<<< orphan*/  NGX_OK ; 

__attribute__((used)) static ngx_int_t
ngx_http_proxy_connect_allow_handler(ngx_http_request_t *r,
    ngx_http_proxy_connect_loc_conf_t *plcf)
{
    ngx_uint_t  i, allow;
    in_port_t   (*ports)[2];

    allow = 0;

    if (plcf->allow_port_all) {
        allow = 1;

    } else if (plcf->allow_ports) {
        ports = plcf->allow_ports->elts;

        for (i = 0; i < plcf->allow_ports->nelts; i++) {
            /*
             * connect_port == port
             * OR
             * port <= connect_port <= eport
             */
            if ((ports[i][1] == 0 && r->connect_port_n == ports[i][0])
                || (ports[i][0] <= r->connect_port_n && r->connect_port_n <= ports[i][1]))
            {
                allow = 1;
                break;
            }
        }

    } else {
        if (r->connect_port_n == 443 || r->connect_port_n == 563) {
            allow = 1;
        }
    }

    if (allow == 0) {
        return NGX_HTTP_FORBIDDEN;
    }

    return NGX_OK;
}