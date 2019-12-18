#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void ngx_http_fake_merge_main_conf_t ;
struct TYPE_4__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ ngx_conf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 void* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void *ngx_http_fake_merge_create_main_conf(ngx_conf_t *cf)
{
    ngx_http_fake_merge_main_conf_t   *fmcf;

    fmcf = ngx_pcalloc(cf->pool, sizeof(ngx_http_fake_merge_main_conf_t));
    if (fmcf == NULL) {
        ngx_conf_log_error(NGX_LOG_ALERT, cf, 0, "create module main conf");
        return NULL;
    }

    return fmcf;
}