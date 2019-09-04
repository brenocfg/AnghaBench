#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_18__ ;

/* Type definitions */
struct sockaddr {scalar_t__ sa_family; } ;
typedef  size_t ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_21__ {struct sockaddr sockaddr; } ;
struct TYPE_23__ {TYPE_1__ sockaddr; } ;
typedef  TYPE_3__ ngx_http_listen_opt_t ;
typedef  int /*<<< orphan*/  ngx_http_core_srv_conf_t ;
struct TYPE_24__ {TYPE_18__* ports; } ;
typedef  TYPE_4__ ngx_http_core_main_conf_t ;
struct TYPE_22__ {int /*<<< orphan*/ * elts; } ;
struct TYPE_25__ {scalar_t__ family; TYPE_2__ addrs; int /*<<< orphan*/  port; } ;
typedef  TYPE_5__ ngx_http_conf_port_t ;
struct TYPE_26__ {int /*<<< orphan*/  temp_pool; } ;
typedef  TYPE_6__ ngx_conf_t ;
typedef  int /*<<< orphan*/  in_port_t ;
struct TYPE_20__ {size_t nelts; TYPE_5__* elts; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 TYPE_18__* ngx_array_create (int /*<<< orphan*/ ,int,int) ; 
 TYPE_5__* ngx_array_push (TYPE_18__*) ; 
 int /*<<< orphan*/  ngx_http_add_address (TYPE_6__*,int /*<<< orphan*/ *,TYPE_5__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_http_add_addresses (TYPE_6__*,int /*<<< orphan*/ *,TYPE_5__*,TYPE_3__*) ; 
 TYPE_4__* ngx_http_conf_get_module_main_conf (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 int /*<<< orphan*/  ngx_inet_get_port (struct sockaddr*) ; 

ngx_int_t
ngx_http_add_listen(ngx_conf_t *cf, ngx_http_core_srv_conf_t *cscf,
    ngx_http_listen_opt_t *lsopt)
{
    in_port_t                   p;
    ngx_uint_t                  i;
    struct sockaddr            *sa;
    ngx_http_conf_port_t       *port;
    ngx_http_core_main_conf_t  *cmcf;

    cmcf = ngx_http_conf_get_module_main_conf(cf, ngx_http_core_module);

    if (cmcf->ports == NULL) {
        cmcf->ports = ngx_array_create(cf->temp_pool, 2,
                                       sizeof(ngx_http_conf_port_t));
        if (cmcf->ports == NULL) {
            return NGX_ERROR;
        }
    }

    sa = &lsopt->sockaddr.sockaddr;
    p = ngx_inet_get_port(sa);

    port = cmcf->ports->elts;
    for (i = 0; i < cmcf->ports->nelts; i++) {

        if (p != port[i].port || sa->sa_family != port[i].family) {
            continue;
        }

        /* a port is already in the port list */

        return ngx_http_add_addresses(cf, cscf, &port[i], lsopt);
    }

    /* add a port to the port list */

    port = ngx_array_push(cmcf->ports);
    if (port == NULL) {
        return NGX_ERROR;
    }

    port->family = sa->sa_family;
    port->port = p;
    port->addrs.elts = NULL;

    return ngx_http_add_address(cf, cscf, port, lsopt);
}