#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_str_t ;
struct TYPE_8__ {void* handler_conf; int /*<<< orphan*/  handler; TYPE_3__* conf_file; } ;
typedef  TYPE_2__ ngx_conf_t ;
struct TYPE_7__ {int /*<<< orphan*/  fd; } ;
struct TYPE_9__ {int /*<<< orphan*/ * buffer; TYPE_1__ file; } ;
typedef  TYPE_3__ ngx_conf_file_t ;
typedef  int /*<<< orphan*/  ngx_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_INVALID_FILE ; 
 char* ngx_conf_parse (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_dyups_parse_upstream_name_handler ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_3__*,int) ; 

__attribute__((used)) static char *
ngx_dyups_parse_upstream_name(ngx_conf_t *cf, ngx_buf_t *buf, ngx_str_t *name)
{
    ngx_conf_file_t     conf_file;
    ngx_buf_t           b;

    b = *buf;   /* avoid modifying @buf */

    ngx_memzero(&conf_file, sizeof(ngx_conf_file_t));
    conf_file.file.fd = NGX_INVALID_FILE;
    conf_file.buffer = &b;

    cf->conf_file = &conf_file;
    cf->handler = ngx_dyups_parse_upstream_name_handler;
    cf->handler_conf = (void *) name;   /* return value */

    return ngx_conf_parse(cf, NULL);
}