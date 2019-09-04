#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_9__ {scalar_t__ family; int port; int default_port; int /*<<< orphan*/  uri; TYPE_4__ host; TYPE_4__ port_text; scalar_t__ no_port; } ;
typedef  TYPE_2__ ngx_url_t ;
struct TYPE_8__ {int /*<<< orphan*/  len; } ;
struct TYPE_10__ {int /*<<< orphan*/  uri; TYPE_1__ key_start; TYPE_4__ port; TYPE_4__ host_header; } ;
typedef  TYPE_3__ ngx_http_proxy_vars_t ;

/* Variables and functions */
 scalar_t__ AF_UNIX ; 
 int /*<<< orphan*/  ngx_str_null (TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_str_set (TYPE_4__*,char*) ; 

__attribute__((used)) static void
ngx_http_proxy_set_vars(ngx_url_t *u, ngx_http_proxy_vars_t *v)
{
    if (u->family != AF_UNIX) {

        if (u->no_port || u->port == u->default_port) {

            v->host_header = u->host;

            if (u->default_port == 80) {
                ngx_str_set(&v->port, "80");

            } else {
                ngx_str_set(&v->port, "443");
            }

        } else {
            v->host_header.len = u->host.len + 1 + u->port_text.len;
            v->host_header.data = u->host.data;
            v->port = u->port_text;
        }

        v->key_start.len += v->host_header.len;

    } else {
        ngx_str_set(&v->host_header, "localhost");
        ngx_str_null(&v->port);
        v->key_start.len += sizeof("unix:") - 1 + u->host.len + 1;
    }

    v->uri = u->uri;
}