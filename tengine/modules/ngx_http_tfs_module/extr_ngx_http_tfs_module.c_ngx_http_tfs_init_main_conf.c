#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int tfs_connect_timeout; int tfs_send_timeout; int tfs_read_timeout; int tair_timeout; scalar_t__ send_lowat; scalar_t__ buffer_size; scalar_t__ body_buffer_size; } ;
typedef  TYPE_1__ ngx_http_tfs_main_conf_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;

/* Variables and functions */
 char* NGX_CONF_OK ; 
 int NGX_CONF_UNSET_MSEC ; 
 scalar_t__ NGX_CONF_UNSET_SIZE ; 
 scalar_t__ NGX_HTTP_TFS_DEFAULT_BODY_BUFFER_SIZE ; 
 scalar_t__ ngx_pagesize ; 

__attribute__((used)) static char *
ngx_http_tfs_init_main_conf(ngx_conf_t *cf, void *conf)
{
    ngx_http_tfs_main_conf_t *tmcf = conf;

    if (tmcf->tfs_connect_timeout == NGX_CONF_UNSET_MSEC) {
        tmcf->tfs_connect_timeout = 3000;
    }

    if (tmcf->tfs_send_timeout == NGX_CONF_UNSET_MSEC) {
        tmcf->tfs_send_timeout = 3000;
    }

    if (tmcf->tfs_read_timeout == NGX_CONF_UNSET_MSEC) {
        tmcf->tfs_read_timeout = 3000;
    }

    if (tmcf->tair_timeout == NGX_CONF_UNSET_MSEC) {
        tmcf->tair_timeout = 3000;
    }

    if (tmcf->send_lowat == NGX_CONF_UNSET_SIZE) {
        tmcf->send_lowat = 0;
    }

    if (tmcf->buffer_size == NGX_CONF_UNSET_SIZE) {
        tmcf->buffer_size = (size_t) ngx_pagesize / 2;
    }

    if (tmcf->body_buffer_size == NGX_CONF_UNSET_SIZE) {
        tmcf->body_buffer_size = NGX_HTTP_TFS_DEFAULT_BODY_BUFFER_SIZE;
    }

    return NGX_CONF_OK;
}