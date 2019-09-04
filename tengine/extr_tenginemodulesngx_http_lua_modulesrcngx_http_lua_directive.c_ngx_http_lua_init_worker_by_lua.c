#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_9__ {int /*<<< orphan*/  len; int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ ngx_str_t ;
struct TYPE_10__ {TYPE_2__ init_worker_src; scalar_t__ init_worker_handler; } ;
typedef  TYPE_3__ ngx_http_lua_main_conf_t ;
typedef  scalar_t__ ngx_http_lua_main_conf_handler_pt ;
struct TYPE_11__ {int /*<<< orphan*/  pool; TYPE_1__* args; } ;
typedef  TYPE_4__ ngx_conf_t ;
struct TYPE_12__ {int /*<<< orphan*/ * post; } ;
typedef  TYPE_5__ ngx_command_t ;
struct TYPE_8__ {TYPE_2__* elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/  dd (char*) ; 
 int /*<<< orphan*/ * ngx_http_lua_init_worker_by_file ; 
 int /*<<< orphan*/ * ngx_http_lua_rebase_path (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_strlen (int /*<<< orphan*/ *) ; 

char *
ngx_http_lua_init_worker_by_lua(ngx_conf_t *cf, ngx_command_t *cmd,
    void *conf)
{
    u_char                      *name;
    ngx_str_t                   *value;
    ngx_http_lua_main_conf_t    *lmcf = conf;

    dd("enter");

    /*  must specify a content handler */
    if (cmd->post == NULL) {
        return NGX_CONF_ERROR;
    }

    if (lmcf->init_worker_handler) {
        return "is duplicate";
    }

    value = cf->args->elts;

    lmcf->init_worker_handler = (ngx_http_lua_main_conf_handler_pt) cmd->post;

    if (cmd->post == ngx_http_lua_init_worker_by_file) {
        name = ngx_http_lua_rebase_path(cf->pool, value[1].data,
                                        value[1].len);
        if (name == NULL) {
            return NGX_CONF_ERROR;
        }

        lmcf->init_worker_src.data = name;
        lmcf->init_worker_src.len = ngx_strlen(name);

    } else {
        lmcf->init_worker_src = value[1];
    }

    return NGX_CONF_OK;
}