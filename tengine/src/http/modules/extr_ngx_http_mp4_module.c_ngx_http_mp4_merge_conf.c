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
struct TYPE_2__ {int /*<<< orphan*/  max_buffer_size; int /*<<< orphan*/  buffer_size; } ;
typedef  TYPE_1__ ngx_http_mp4_conf_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;

/* Variables and functions */
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/  ngx_conf_merge_size_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static char *
ngx_http_mp4_merge_conf(ngx_conf_t *cf, void *parent, void *child)
{
    ngx_http_mp4_conf_t *prev = parent;
    ngx_http_mp4_conf_t *conf = child;

    ngx_conf_merge_size_value(conf->buffer_size, prev->buffer_size, 512 * 1024);
    ngx_conf_merge_size_value(conf->max_buffer_size, prev->max_buffer_size,
                              10 * 1024 * 1024);

    return NGX_CONF_OK;
}