#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
struct TYPE_18__ {char* data; scalar_t__ len; } ;
struct TYPE_16__ {TYPE_5__ name; TYPE_4__* server; } ;
typedef  TYPE_3__ ngx_stream_server_name_t ;
struct TYPE_15__ {int /*<<< orphan*/ * data; scalar_t__ len; } ;
struct TYPE_13__ {scalar_t__ nelts; TYPE_3__* elts; } ;
struct TYPE_17__ {TYPE_2__ server_name; TYPE_12__ server_names; int /*<<< orphan*/  preread_timeout; int /*<<< orphan*/  preread_buffer_size; int /*<<< orphan*/  tcp_nodelay; int /*<<< orphan*/  proxy_protocol_timeout; int /*<<< orphan*/ * error_log; int /*<<< orphan*/  line; int /*<<< orphan*/  file_name; int /*<<< orphan*/ * handler; int /*<<< orphan*/ * resolver; int /*<<< orphan*/  resolver_timeout; } ;
typedef  TYPE_4__ ngx_stream_core_srv_conf_t ;
typedef  TYPE_5__ ngx_str_t ;
struct TYPE_19__ {int /*<<< orphan*/  pool; TYPE_1__* cycle; int /*<<< orphan*/  log; } ;
typedef  TYPE_6__ ngx_conf_t ;
struct TYPE_14__ {int /*<<< orphan*/  new_log; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 TYPE_3__* ngx_array_push (TYPE_12__*) ; 
 int /*<<< orphan*/  ngx_conf_merge_msec_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_conf_merge_size_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_conf_merge_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_pstrdup (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/ * ngx_resolver_create (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_str_set (TYPE_5__*,char*) ; 

__attribute__((used)) static char *
ngx_stream_core_merge_srv_conf(ngx_conf_t *cf, void *parent, void *child)
{
    ngx_stream_core_srv_conf_t *prev = parent;
    ngx_stream_core_srv_conf_t *conf = child;
#if (NGX_STREAM_SNI)
    ngx_str_t                   name;
    ngx_stream_server_name_t   *sn;
#endif


    ngx_conf_merge_msec_value(conf->resolver_timeout,
                              prev->resolver_timeout, 30000);

    if (conf->resolver == NULL) {

        if (prev->resolver == NULL) {

            /*
             * create dummy resolver in stream {} context
             * to inherit it in all servers
             */

            prev->resolver = ngx_resolver_create(cf, NULL, 0);
            if (prev->resolver == NULL) {
                return NGX_CONF_ERROR;
            }
        }

        conf->resolver = prev->resolver;
    }

    if (conf->handler == NULL) {
        ngx_log_error(NGX_LOG_EMERG, cf->log, 0,
                      "no handler for server in %s:%ui",
                      conf->file_name, conf->line);
        return NGX_CONF_ERROR;
    }

    if (conf->error_log == NULL) {
        if (prev->error_log) {
            conf->error_log = prev->error_log;
        } else {
            conf->error_log = &cf->cycle->new_log;
        }
    }

    ngx_conf_merge_msec_value(conf->proxy_protocol_timeout,
                              prev->proxy_protocol_timeout, 30000);

    ngx_conf_merge_value(conf->tcp_nodelay, prev->tcp_nodelay, 1);

    ngx_conf_merge_size_value(conf->preread_buffer_size,
                              prev->preread_buffer_size, 16384);

    ngx_conf_merge_msec_value(conf->preread_timeout,
                              prev->preread_timeout, 30000);

#if (NGX_STREAM_SNI)
    if (conf->server_names.nelts == 0) {
        /* the array has 4 empty preallocated elements, so push cannot fail */
        sn = ngx_array_push(&conf->server_names);
        sn->server = conf;
        ngx_str_set(&sn->name, "");
    }

    sn = conf->server_names.elts;
    name = sn[0].name;

    if (name.data[0] == '.') {
        name.len--;
        name.data++;
    }

    conf->server_name.len = name.len;
    conf->server_name.data = ngx_pstrdup(cf->pool, &name);
    if (conf->server_name.data == NULL) {
        return NGX_CONF_ERROR;
    }
#endif

    return NGX_CONF_OK;
}