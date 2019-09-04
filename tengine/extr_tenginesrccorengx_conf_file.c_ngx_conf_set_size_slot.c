#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_str_t ;
struct TYPE_10__ {TYPE_1__* args; } ;
typedef  TYPE_2__ ngx_conf_t ;
struct TYPE_11__ {char* (* post_handler ) (TYPE_2__*,TYPE_3__*,size_t*) ;} ;
typedef  TYPE_3__ ngx_conf_post_t ;
struct TYPE_12__ {int offset; TYPE_3__* post; } ;
typedef  TYPE_4__ ngx_command_t ;
struct TYPE_9__ {int /*<<< orphan*/ * elts; } ;

/* Variables and functions */
 char* NGX_CONF_OK ; 
 size_t NGX_CONF_UNSET_SIZE ; 
 scalar_t__ NGX_ERROR ; 
 size_t ngx_parse_size (int /*<<< orphan*/ *) ; 
 char* stub1 (TYPE_2__*,TYPE_3__*,size_t*) ; 

char *
ngx_conf_set_size_slot(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    char  *p = conf;

    size_t           *sp;
    ngx_str_t        *value;
    ngx_conf_post_t  *post;


    sp = (size_t *) (p + cmd->offset);
    if (*sp != NGX_CONF_UNSET_SIZE) {
        return "is duplicate";
    }

    value = cf->args->elts;

    *sp = ngx_parse_size(&value[1]);
    if (*sp == (size_t) NGX_ERROR) {
        return "invalid value";
    }

    if (cmd->post) {
        post = cmd->post;
        return post->post_handler(cf, post, sp);
    }

    return NGX_CONF_OK;
}