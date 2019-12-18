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
typedef  void ngx_stream_geoip_conf_t ;
struct TYPE_5__ {void* data; int /*<<< orphan*/  handler; } ;
typedef  TYPE_1__ ngx_pool_cleanup_t ;
struct TYPE_6__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_2__ ngx_conf_t ;

/* Variables and functions */
 void* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* ngx_pool_cleanup_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_stream_geoip_cleanup ; 

__attribute__((used)) static void *
ngx_stream_geoip_create_conf(ngx_conf_t *cf)
{
    ngx_pool_cleanup_t       *cln;
    ngx_stream_geoip_conf_t  *conf;

    conf = ngx_pcalloc(cf->pool, sizeof(ngx_stream_geoip_conf_t));
    if (conf == NULL) {
        return NULL;
    }

    cln = ngx_pool_cleanup_add(cf->pool, 0);
    if (cln == NULL) {
        return NULL;
    }

    cln->handler = ngx_stream_geoip_cleanup;
    cln->data = conf;

    return conf;
}