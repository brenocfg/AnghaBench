#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ len; scalar_t__ data; } ;
typedef  TYPE_4__ ngx_str_t ;
struct TYPE_15__ {TYPE_6__* conf_file; TYPE_1__* cycle; } ;
typedef  TYPE_5__ ngx_conf_t ;
struct TYPE_12__ {int /*<<< orphan*/ * data; } ;
struct TYPE_13__ {TYPE_2__ name; int /*<<< orphan*/  fd; } ;
struct TYPE_16__ {scalar_t__ start; scalar_t__ pos; scalar_t__ last; scalar_t__ end; int temporary; struct TYPE_16__* buffer; scalar_t__ line; TYPE_3__ file; } ;
typedef  TYPE_6__ ngx_conf_file_t ;
typedef  TYPE_6__ ngx_buf_t ;
struct TYPE_11__ {TYPE_4__ conf_param; } ;

/* Variables and functions */
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/  NGX_INVALID_FILE ; 
 char* ngx_conf_parse (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_6__*,int) ; 

char *
ngx_conf_param(ngx_conf_t *cf)
{
    char             *rv;
    ngx_str_t        *param;
    ngx_buf_t         b;
    ngx_conf_file_t   conf_file;

    param = &cf->cycle->conf_param;

    if (param->len == 0) {
        return NGX_CONF_OK;
    }

    ngx_memzero(&conf_file, sizeof(ngx_conf_file_t));

    ngx_memzero(&b, sizeof(ngx_buf_t));

    b.start = param->data;
    b.pos = param->data;
    b.last = param->data + param->len;
    b.end = b.last;
    b.temporary = 1;

    conf_file.file.fd = NGX_INVALID_FILE;
    conf_file.file.name.data = NULL;
    conf_file.line = 0;

    cf->conf_file = &conf_file;
    cf->conf_file->buffer = &b;

    rv = ngx_conf_parse(cf, NULL);

    cf->conf_file = NULL;

    return rv;
}