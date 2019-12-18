#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
typedef  size_t ngx_uint_t ;
struct TYPE_19__ {char* data; int len; } ;
typedef  TYPE_5__ ngx_str_t ;
struct TYPE_20__ {int len; scalar_t__* level; int /*<<< orphan*/  line; int /*<<< orphan*/  conf_file; TYPE_5__ name; } ;
typedef  TYPE_6__ ngx_path_t ;
struct TYPE_21__ {TYPE_4__* args; TYPE_3__* conf_file; int /*<<< orphan*/  cycle; int /*<<< orphan*/  pool; } ;
typedef  TYPE_7__ ngx_conf_t ;
struct TYPE_22__ {int offset; } ;
typedef  TYPE_8__ ngx_command_t ;
struct TYPE_18__ {size_t nelts; TYPE_5__* elts; } ;
struct TYPE_15__ {int /*<<< orphan*/  data; } ;
struct TYPE_16__ {TYPE_1__ name; } ;
struct TYPE_17__ {int /*<<< orphan*/  line; TYPE_2__ file; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_add_path (TYPE_7__*,TYPE_6__**) ; 
 scalar_t__ ngx_atoi (char*,int) ; 
 scalar_t__ ngx_conf_full_name (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ) ; 
 TYPE_6__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 

char *
ngx_conf_set_path_slot(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    char  *p = conf;

    ssize_t      level;
    ngx_str_t   *value;
    ngx_uint_t   i, n;
    ngx_path_t  *path, **slot;

    slot = (ngx_path_t **) (p + cmd->offset);

    if (*slot) {
        return "is duplicate";
    }

    path = ngx_pcalloc(cf->pool, sizeof(ngx_path_t));
    if (path == NULL) {
        return NGX_CONF_ERROR;
    }

    value = cf->args->elts;

    path->name = value[1];

    if (path->name.data[path->name.len - 1] == '/') {
        path->name.len--;
    }

    if (ngx_conf_full_name(cf->cycle, &path->name, 0) != NGX_OK) {
        return NGX_CONF_ERROR;
    }

    path->conf_file = cf->conf_file->file.name.data;
    path->line = cf->conf_file->line;

    for (i = 0, n = 2; n < cf->args->nelts; i++, n++) {
        level = ngx_atoi(value[n].data, value[n].len);
        if (level == NGX_ERROR || level == 0) {
            return "invalid value";
        }

        path->level[i] = level;
        path->len += level + 1;
    }

    if (path->len > 10 + i) {
        return "invalid value";
    }

    *slot = path;

    if (ngx_add_path(cf, slot) == NGX_ERROR) {
        return NGX_CONF_ERROR;
    }

    return NGX_CONF_OK;
}