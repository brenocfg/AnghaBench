#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_74__   TYPE_9__ ;
typedef  struct TYPE_73__   TYPE_8__ ;
typedef  struct TYPE_72__   TYPE_7__ ;
typedef  struct TYPE_71__   TYPE_6__ ;
typedef  struct TYPE_70__   TYPE_5__ ;
typedef  struct TYPE_69__   TYPE_54__ ;
typedef  struct TYPE_68__   TYPE_52__ ;
typedef  struct TYPE_67__   TYPE_51__ ;
typedef  struct TYPE_66__   TYPE_4__ ;
typedef  struct TYPE_65__   TYPE_3__ ;
typedef  struct TYPE_64__   TYPE_34__ ;
typedef  struct TYPE_63__   TYPE_32__ ;
typedef  struct TYPE_62__   TYPE_2__ ;
typedef  struct TYPE_61__   TYPE_1__ ;
typedef  struct TYPE_60__   TYPE_17__ ;
typedef  struct TYPE_59__   TYPE_16__ ;
typedef  struct TYPE_58__   TYPE_14__ ;
typedef  struct TYPE_57__   TYPE_12__ ;
typedef  struct TYPE_56__   TYPE_11__ ;
typedef  struct TYPE_55__   TYPE_10__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_shm_zone_t ;
struct TYPE_72__ {size_t nelts; TYPE_5__* elts; struct TYPE_72__* next; } ;
struct TYPE_63__ {TYPE_7__ part; } ;
struct TYPE_69__ {scalar_t__ nelts; } ;
struct TYPE_70__ {int /*<<< orphan*/  log; int /*<<< orphan*/  conf_file; int /*<<< orphan*/  pool; TYPE_32__ shared_memory; TYPE_32__ open_files; TYPE_54__ listening; scalar_t__* conf_ctx; } ;
typedef  TYPE_5__ ngx_open_file_t ;
struct TYPE_71__ {size_t ctx_index; scalar_t__ type; TYPE_9__* ctx; } ;
typedef  TYPE_6__ ngx_module_t ;
typedef  int /*<<< orphan*/  ngx_listening_t ;
typedef  TYPE_7__ ngx_list_part_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_73__ {int /*<<< orphan*/  read_event_handler; TYPE_11__** loc_conf; void** srv_conf; int /*<<< orphan*/  main_conf; } ;
typedef  TYPE_8__ ngx_http_request_t ;
struct TYPE_74__ {char* (* merge_srv_conf ) (TYPE_17__*,void*,void*) ;char* (* merge_loc_conf ) (TYPE_17__*,void*,void*) ;void* (* create_loc_conf ) (TYPE_17__*) ;void* (* create_srv_conf ) (TYPE_17__*) ;} ;
typedef  TYPE_9__ ngx_http_module_t ;
struct TYPE_55__ {int /*<<< orphan*/ * lua; int /*<<< orphan*/  (* init_worker_handler ) (int /*<<< orphan*/ ,TYPE_10__*,int /*<<< orphan*/ *) ;TYPE_4__* vm_cleanup; } ;
typedef  TYPE_10__ ngx_http_lua_main_conf_t ;
struct TYPE_56__ {TYPE_3__* error_log; } ;
typedef  TYPE_11__ ngx_http_lua_loc_conf_t ;
struct TYPE_57__ {int /*<<< orphan*/ * cur_co_ctx; int /*<<< orphan*/  context; } ;
typedef  TYPE_12__ ngx_http_lua_ctx_t ;
typedef  TYPE_11__ ngx_http_core_loc_conf_t ;
struct TYPE_58__ {TYPE_11__** loc_conf; void** srv_conf; int /*<<< orphan*/  main_conf; } ;
typedef  TYPE_14__ ngx_http_conf_ctx_t ;
typedef  TYPE_5__ ngx_cycle_t ;
struct TYPE_59__ {TYPE_51__* pool; TYPE_2__* log; } ;
typedef  TYPE_16__ ngx_connection_t ;
struct TYPE_61__ {int /*<<< orphan*/  name; } ;
struct TYPE_60__ {TYPE_51__* temp_pool; int /*<<< orphan*/  pool; struct TYPE_60__* conf_file; TYPE_1__ file; int /*<<< orphan*/  log; TYPE_5__* cycle; TYPE_14__* ctx; } ;
typedef  TYPE_17__ ngx_conf_t ;
typedef  TYPE_17__ ngx_conf_file_t ;
typedef  int /*<<< orphan*/  cf_file ;
struct TYPE_68__ {int /*<<< orphan*/  log; } ;
struct TYPE_67__ {int /*<<< orphan*/  log; } ;
struct TYPE_66__ {int /*<<< orphan*/  (* handler ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  data; } ;
struct TYPE_65__ {int log_level; int /*<<< orphan*/  file; } ;
struct TYPE_64__ {size_t index; } ;
struct TYPE_62__ {int log_level; int /*<<< orphan*/  file; int /*<<< orphan*/  handler; } ;

/* Variables and functions */
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/  NGX_CYCLE_POOL_SIZE ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_LUA_CONTEXT_INIT_WORKER ; 
 scalar_t__ NGX_HTTP_MODULE ; 
 int NGX_LOG_DEBUG_CONNECTION ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ NGX_PROCESS_HELPER ; 
 scalar_t__ ngx_array_init (TYPE_54__*,int /*<<< orphan*/ ,int,int) ; 
 TYPE_51__* ngx_create_pool (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_52__* ngx_cycle ; 
 int /*<<< orphan*/  ngx_destroy_pool (TYPE_51__*) ; 
 int /*<<< orphan*/  ngx_http_block_reading ; 
 TYPE_6__ ngx_http_core_module ; 
 TYPE_10__* ngx_http_cycle_get_module_main_conf (TYPE_5__*,TYPE_6__) ; 
 TYPE_11__* ngx_http_get_module_loc_conf (TYPE_8__*,TYPE_6__) ; 
 int /*<<< orphan*/  ngx_http_lua_close_fake_connection (TYPE_16__*) ; 
 TYPE_12__* ngx_http_lua_create_ctx (TYPE_8__*) ; 
 TYPE_16__* ngx_http_lua_create_fake_connection (int /*<<< orphan*/ *) ; 
 TYPE_8__* ngx_http_lua_create_fake_request (TYPE_16__*) ; 
 int /*<<< orphan*/  ngx_http_lua_log_init_worker_error ; 
 TYPE_6__ ngx_http_lua_module ; 
 int /*<<< orphan*/  ngx_http_lua_set_req (int /*<<< orphan*/ *,TYPE_8__*) ; 
 int ngx_http_max_module ; 
 TYPE_34__ ngx_http_module ; 
 scalar_t__ ngx_list_init (TYPE_32__*,int /*<<< orphan*/ ,int,int) ; 
 TYPE_5__* ngx_list_push (TYPE_32__*) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_memcpy (TYPE_5__*,TYPE_5__*,int) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_17__*,int) ; 
 TYPE_6__** ngx_modules ; 
 TYPE_5__* ngx_palloc (int /*<<< orphan*/ ,int) ; 
 void* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_pid ; 
 scalar_t__ ngx_process ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 void* stub2 (TYPE_17__*) ; 
 void* stub3 (TYPE_17__*) ; 
 char* stub4 (TYPE_17__*,void*,void*) ; 
 void* stub5 (TYPE_17__*) ; 
 void* stub6 (TYPE_17__*) ; 
 char* stub7 (TYPE_17__*,void*,void*) ; 
 int /*<<< orphan*/  stub8 (int /*<<< orphan*/ ,TYPE_10__*,int /*<<< orphan*/ *) ; 

ngx_int_t
ngx_http_lua_init_worker(ngx_cycle_t *cycle)
{
    char                        *rv;
    void                        *cur, *prev;
    ngx_uint_t                   i;
    ngx_conf_t                   conf;
    ngx_conf_file_t              cf_file;
    ngx_cycle_t                 *fake_cycle;
    ngx_module_t               **modules;
    ngx_open_file_t             *file, *ofile;
    ngx_list_part_t             *part;
    ngx_connection_t            *c = NULL;
    ngx_http_module_t           *module;
    ngx_http_request_t          *r = NULL;
    ngx_http_lua_ctx_t          *ctx;
    ngx_http_conf_ctx_t         *conf_ctx, http_ctx;
    ngx_http_lua_loc_conf_t     *top_llcf;
    ngx_http_lua_main_conf_t    *lmcf;
    ngx_http_core_loc_conf_t    *clcf, *top_clcf;

    lmcf = ngx_http_cycle_get_module_main_conf(cycle, ngx_http_lua_module);

    if (lmcf == NULL || lmcf->lua == NULL) {
        return NGX_OK;
    }

    /* lmcf != NULL && lmcf->lua != NULL */

#if !(NGX_WIN32)
    if (ngx_process == NGX_PROCESS_HELPER
#   ifdef HAVE_PRIVILEGED_PROCESS_PATCH
        && !ngx_is_privileged_agent
#   endif
       )
    {
        /* disable init_worker_by_lua* and destroy lua VM in cache processes */

        ngx_log_debug2(NGX_LOG_DEBUG_HTTP, ngx_cycle->log, 0,
                       "lua close the global Lua VM %p in the "
                       "cache helper process %P", lmcf->lua, ngx_pid);

        lmcf->vm_cleanup->handler(lmcf->vm_cleanup->data);
        lmcf->vm_cleanup->handler = NULL;

        return NGX_OK;
    }

#ifdef HAVE_NGX_LUA_PIPE
    if (ngx_http_lua_pipe_add_signal_handler(cycle) != NGX_OK) {
        return NGX_ERROR;
    }
#endif

#endif  /* NGX_WIN32 */

#if (NGX_HTTP_LUA_HAVE_SA_RESTART)
    if (lmcf->set_sa_restart) {
        ngx_http_lua_set_sa_restart(ngx_cycle->log);
    }
#endif

    if (lmcf->init_worker_handler == NULL) {
        return NGX_OK;
    }

    conf_ctx = (ngx_http_conf_ctx_t *) cycle->conf_ctx[ngx_http_module.index];
    http_ctx.main_conf = conf_ctx->main_conf;

    top_clcf = conf_ctx->loc_conf[ngx_http_core_module.ctx_index];
    top_llcf = conf_ctx->loc_conf[ngx_http_lua_module.ctx_index];

    ngx_memzero(&conf, sizeof(ngx_conf_t));

    conf.temp_pool = ngx_create_pool(NGX_CYCLE_POOL_SIZE, cycle->log);
    if (conf.temp_pool == NULL) {
        return NGX_ERROR;
    }

    conf.temp_pool->log = cycle->log;

    /* we fake a temporary ngx_cycle_t here because some
     * modules' merge conf handler may produce side effects in
     * cf->cycle (like ngx_proxy vs cf->cycle->paths).
     * also, we cannot allocate our temp cycle on the stack
     * because some modules like ngx_http_core_module reference
     * addresses within cf->cycle (i.e., via "&cf->cycle->new_log")
     */

    fake_cycle = ngx_palloc(cycle->pool, sizeof(ngx_cycle_t));
    if (fake_cycle == NULL) {
        goto failed;
    }

    ngx_memcpy(fake_cycle, cycle, sizeof(ngx_cycle_t));

#if defined(nginx_version) && nginx_version >= 9007

    ngx_queue_init(&fake_cycle->reusable_connections_queue);

#endif

    if (ngx_array_init(&fake_cycle->listening, cycle->pool,
                       cycle->listening.nelts || 1,
                       sizeof(ngx_listening_t))
        != NGX_OK)
    {
        goto failed;
    }

#if defined(nginx_version) && nginx_version >= 1003007

    if (ngx_array_init(&fake_cycle->paths, cycle->pool, cycle->paths.nelts || 1,
                       sizeof(ngx_path_t *))
        != NGX_OK)
    {
        goto failed;
    }

#endif

    part = &cycle->open_files.part;
    ofile = part->elts;

    if (ngx_list_init(&fake_cycle->open_files, cycle->pool, part->nelts || 1,
                      sizeof(ngx_open_file_t))
        != NGX_OK)
    {
        goto failed;
    }

    for (i = 0; /* void */ ; i++) {

        if (i >= part->nelts) {
            if (part->next == NULL) {
                break;
            }
            part = part->next;
            ofile = part->elts;
            i = 0;
        }

        file = ngx_list_push(&fake_cycle->open_files);
        if (file == NULL) {
            goto failed;
        }

        ngx_memcpy(file, ofile, sizeof(ngx_open_file_t));
    }

    if (ngx_list_init(&fake_cycle->shared_memory, cycle->pool, 1,
                      sizeof(ngx_shm_zone_t))
        != NGX_OK)
    {
        goto failed;
    }

    conf.ctx = &http_ctx;
    conf.cycle = fake_cycle;
    conf.pool = fake_cycle->pool;
    conf.log = cycle->log;

    ngx_memzero(&cf_file, sizeof(cf_file));
    cf_file.file.name = cycle->conf_file;
    conf.conf_file = &cf_file;

    http_ctx.loc_conf = ngx_pcalloc(conf.pool,
                                    sizeof(void *) * ngx_http_max_module);
    if (http_ctx.loc_conf == NULL) {
        return NGX_ERROR;
    }

    http_ctx.srv_conf = ngx_pcalloc(conf.pool,
                                    sizeof(void *) * ngx_http_max_module);
    if (http_ctx.srv_conf == NULL) {
        return NGX_ERROR;
    }

#if defined(nginx_version) && nginx_version >= 1009011
    modules = cycle->modules;
#else
    modules = ngx_modules;
#endif

    for (i = 0; modules[i]; i++) {
        if (modules[i]->type != NGX_HTTP_MODULE) {
            continue;
        }

        module = modules[i]->ctx;

        if (module->create_srv_conf) {
            cur = module->create_srv_conf(&conf);
            if (cur == NULL) {
                return NGX_ERROR;
            }

            http_ctx.srv_conf[modules[i]->ctx_index] = cur;

            if (module->merge_srv_conf) {
                prev = module->create_srv_conf(&conf);
                if (prev == NULL) {
                    return NGX_ERROR;
                }

                rv = module->merge_srv_conf(&conf, prev, cur);
                if (rv != NGX_CONF_OK) {
                    goto failed;
                }
            }
        }

        if (module->create_loc_conf) {
            cur = module->create_loc_conf(&conf);
            if (cur == NULL) {
                return NGX_ERROR;
            }

            http_ctx.loc_conf[modules[i]->ctx_index] = cur;

            if (module->merge_loc_conf) {
                if (modules[i] == &ngx_http_lua_module) {
                    prev = top_llcf;

                } else if (modules[i] == &ngx_http_core_module) {
                    prev = top_clcf;

                } else {
                    prev = module->create_loc_conf(&conf);
                    if (prev == NULL) {
                        return NGX_ERROR;
                    }
                }

                rv = module->merge_loc_conf(&conf, prev, cur);
                if (rv != NGX_CONF_OK) {
                    goto failed;
                }
            }
        }
    }

    ngx_destroy_pool(conf.temp_pool);
    conf.temp_pool = NULL;

    c = ngx_http_lua_create_fake_connection(NULL);
    if (c == NULL) {
        goto failed;
    }

    c->log->handler = ngx_http_lua_log_init_worker_error;

    r = ngx_http_lua_create_fake_request(c);
    if (r == NULL) {
        goto failed;
    }

    r->main_conf = http_ctx.main_conf;
    r->srv_conf = http_ctx.srv_conf;
    r->loc_conf = http_ctx.loc_conf;

    clcf = ngx_http_get_module_loc_conf(r, ngx_http_core_module);

#if defined(nginx_version) && nginx_version >= 1003014

#   if nginx_version >= 1009000

    ngx_set_connection_log(r->connection, clcf->error_log);

#   else

    ngx_http_set_connection_log(r->connection, clcf->error_log);

#   endif

#else

    c->log->file = clcf->error_log->file;

    if (!(c->log->log_level & NGX_LOG_DEBUG_CONNECTION)) {
        c->log->log_level = clcf->error_log->log_level;
    }

#endif

    ctx = ngx_http_lua_create_ctx(r);
    if (ctx == NULL) {
        goto failed;
    }

    ctx->context = NGX_HTTP_LUA_CONTEXT_INIT_WORKER;
    ctx->cur_co_ctx = NULL;
    r->read_event_handler = ngx_http_block_reading;

    ngx_http_lua_set_req(lmcf->lua, r);

    (void) lmcf->init_worker_handler(cycle->log, lmcf, lmcf->lua);

    ngx_destroy_pool(c->pool);
    return NGX_OK;

failed:

    if (conf.temp_pool) {
        ngx_destroy_pool(conf.temp_pool);
    }

    if (c) {
        ngx_http_lua_close_fake_connection(c);
    }

    return NGX_ERROR;
}