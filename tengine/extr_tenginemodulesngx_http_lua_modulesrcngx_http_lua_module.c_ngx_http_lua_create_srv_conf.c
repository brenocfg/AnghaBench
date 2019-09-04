#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void ngx_http_lua_srv_conf_t ;
struct TYPE_3__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ ngx_conf_t ;

/* Variables and functions */
 void* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void *
ngx_http_lua_create_srv_conf(ngx_conf_t *cf)
{
    ngx_http_lua_srv_conf_t     *lscf;

    lscf = ngx_pcalloc(cf->pool, sizeof(ngx_http_lua_srv_conf_t));
    if (lscf == NULL) {
        return NULL;
    }

    /* set by ngx_pcalloc:
     *      lscf->srv.ssl_cert_handler = NULL;
     *      lscf->srv.ssl_cert_src = { 0, NULL };
     *      lscf->srv.ssl_cert_src_key = NULL;
     *
     *      lscf->srv.ssl_session_store_handler = NULL;
     *      lscf->srv.ssl_session_store_src = { 0, NULL };
     *      lscf->srv.ssl_session_store_src_key = NULL;
     *
     *      lscf->srv.ssl_session_fetch_handler = NULL;
     *      lscf->srv.ssl_session_fetch_src = { 0, NULL };
     *      lscf->srv.ssl_session_fetch_src_key = NULL;
     *
     *      lscf->balancer.handler = NULL;
     *      lscf->balancer.src = { 0, NULL };
     *      lscf->balancer.src_key = NULL;
     */

    return lscf;
}