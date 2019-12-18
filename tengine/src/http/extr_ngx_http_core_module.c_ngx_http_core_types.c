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
struct TYPE_5__ {int /*<<< orphan*/ * types; } ;
typedef  TYPE_1__ ngx_http_core_loc_conf_t ;
typedef  int /*<<< orphan*/  ngx_hash_key_t ;
struct TYPE_6__ {void* handler_conf; int /*<<< orphan*/  handler; int /*<<< orphan*/  pool; } ;
typedef  TYPE_2__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 int /*<<< orphan*/ * ngx_array_create (int /*<<< orphan*/ ,int,int) ; 
 char* ngx_conf_parse (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_core_type ; 

__attribute__((used)) static char *
ngx_http_core_types(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_core_loc_conf_t *clcf = conf;

    char        *rv;
    ngx_conf_t   save;

    if (clcf->types == NULL) {
        clcf->types = ngx_array_create(cf->pool, 64, sizeof(ngx_hash_key_t));
        if (clcf->types == NULL) {
            return NGX_CONF_ERROR;
        }
    }

    save = *cf;
    cf->handler = ngx_http_core_type;
    cf->handler_conf = conf;

    rv = ngx_conf_parse(cf, NULL);

    *cf = save;

    return rv;
}