#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ ngx_str_t ;
struct TYPE_11__ {TYPE_1__* args; } ;
typedef  TYPE_3__ ngx_conf_t ;
struct TYPE_12__ {int offset; } ;
typedef  TYPE_4__ ngx_command_t ;
struct TYPE_13__ {scalar_t__ num; size_t size; } ;
typedef  TYPE_5__ ngx_bufs_t ;
struct TYPE_9__ {TYPE_2__* elts; } ;

/* Variables and functions */
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_ERROR ; 
 scalar_t__ ngx_atoi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t ngx_parse_size (TYPE_2__*) ; 

char *
ngx_conf_set_bufs_slot(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    char *p = conf;

    ngx_str_t   *value;
    ngx_bufs_t  *bufs;


    bufs = (ngx_bufs_t *) (p + cmd->offset);
    if (bufs->num) {
        return "is duplicate";
    }

    value = cf->args->elts;

    bufs->num = ngx_atoi(value[1].data, value[1].len);
    if (bufs->num == NGX_ERROR || bufs->num == 0) {
        return "invalid value";
    }

    bufs->size = ngx_parse_size(&value[2]);
    if (bufs->size == (size_t) NGX_ERROR || bufs->size == 0) {
        return "invalid value";
    }

    return NGX_CONF_OK;
}