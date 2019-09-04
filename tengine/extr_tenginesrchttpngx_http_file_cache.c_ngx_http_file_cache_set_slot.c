#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_22__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  char u_char ;
typedef  int time_t ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ off_t ;
typedef  size_t ngx_uint_t ;
struct TYPE_28__ {int len; char* data; } ;
typedef  TYPE_5__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_path_t ;
typedef  void* ngx_msec_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_29__ {size_t use_temp_path; int inactive; scalar_t__ max_size; TYPE_9__* shm_zone; TYPE_22__* path; void* manager_threshold; void* manager_sleep; scalar_t__ manager_files; void* loader_threshold; void* loader_sleep; scalar_t__ loader_files; } ;
typedef  TYPE_6__ ngx_http_file_cache_t ;
struct TYPE_30__ {TYPE_4__* conf_file; TYPE_1__* args; int /*<<< orphan*/  cycle; int /*<<< orphan*/  pool; } ;
typedef  TYPE_7__ ngx_conf_t ;
struct TYPE_31__ {int offset; int /*<<< orphan*/  post; TYPE_5__ name; } ;
typedef  TYPE_8__ ngx_command_t ;
typedef  int /*<<< orphan*/  ngx_array_t ;
struct TYPE_32__ {TYPE_6__* data; int /*<<< orphan*/  init; } ;
struct TYPE_25__ {int /*<<< orphan*/  data; } ;
struct TYPE_26__ {TYPE_2__ name; } ;
struct TYPE_27__ {int /*<<< orphan*/  line; TYPE_3__ file; } ;
struct TYPE_24__ {int len; int /*<<< orphan*/  line; int /*<<< orphan*/  conf_file; TYPE_6__* data; int /*<<< orphan*/  loader; int /*<<< orphan*/  manager; scalar_t__* level; TYPE_5__ name; } ;
struct TYPE_23__ {size_t nelts; TYPE_5__* elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 scalar_t__ NGX_MAX_OFF_T_VALUE ; 
 size_t NGX_MAX_PATH_LEVEL ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_add_path (TYPE_7__*,TYPE_22__**) ; 
 TYPE_6__** ngx_array_push (int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_atoi (char*,int) ; 
 scalar_t__ ngx_conf_full_name (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ ,char*,TYPE_5__*) ; 
 int /*<<< orphan*/  ngx_http_file_cache_init ; 
 int /*<<< orphan*/  ngx_http_file_cache_loader ; 
 int /*<<< orphan*/  ngx_http_file_cache_manager ; 
 int ngx_pagesize ; 
 scalar_t__ ngx_parse_offset (TYPE_5__*) ; 
 scalar_t__ ngx_parse_size (TYPE_5__*) ; 
 void* ngx_parse_time (TYPE_5__*,int) ; 
 void* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 TYPE_9__* ngx_shared_memory_add (TYPE_7__*,TYPE_5__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_strchr (char*,char) ; 
 scalar_t__ ngx_strcmp (char*,char*) ; 
 scalar_t__ ngx_strncmp (char*,char*,int) ; 

char *
ngx_http_file_cache_set_slot(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    char  *confp = conf;

    off_t                   max_size;
    u_char                 *last, *p;
    time_t                  inactive;
    ssize_t                 size;
    ngx_str_t               s, name, *value;
    ngx_int_t               loader_files, manager_files;
    ngx_msec_t              loader_sleep, manager_sleep, loader_threshold,
                            manager_threshold;
    ngx_uint_t              i, n, use_temp_path;
    ngx_array_t            *caches;
    ngx_http_file_cache_t  *cache, **ce;

    cache = ngx_pcalloc(cf->pool, sizeof(ngx_http_file_cache_t));
    if (cache == NULL) {
        return NGX_CONF_ERROR;
    }

    cache->path = ngx_pcalloc(cf->pool, sizeof(ngx_path_t));
    if (cache->path == NULL) {
        return NGX_CONF_ERROR;
    }

    use_temp_path = 1;

    inactive = 600;

    loader_files = 100;
    loader_sleep = 50;
    loader_threshold = 200;

    manager_files = 100;
    manager_sleep = 50;
    manager_threshold = 200;

    name.len = 0;
    size = 0;
    max_size = NGX_MAX_OFF_T_VALUE;

    value = cf->args->elts;

    cache->path->name = value[1];

    if (cache->path->name.data[cache->path->name.len - 1] == '/') {
        cache->path->name.len--;
    }

    if (ngx_conf_full_name(cf->cycle, &cache->path->name, 0) != NGX_OK) {
        return NGX_CONF_ERROR;
    }

    for (i = 2; i < cf->args->nelts; i++) {

        if (ngx_strncmp(value[i].data, "levels=", 7) == 0) {

            p = value[i].data + 7;
            last = value[i].data + value[i].len;

            for (n = 0; n < NGX_MAX_PATH_LEVEL && p < last; n++) {

                if (*p > '0' && *p < '3') {

                    cache->path->level[n] = *p++ - '0';
                    cache->path->len += cache->path->level[n] + 1;

                    if (p == last) {
                        break;
                    }

                    if (*p++ == ':' && n < NGX_MAX_PATH_LEVEL - 1 && p < last) {
                        continue;
                    }

                    goto invalid_levels;
                }

                goto invalid_levels;
            }

            if (cache->path->len < 10 + NGX_MAX_PATH_LEVEL) {
                continue;
            }

        invalid_levels:

            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                               "invalid \"levels\" \"%V\"", &value[i]);
            return NGX_CONF_ERROR;
        }

        if (ngx_strncmp(value[i].data, "use_temp_path=", 14) == 0) {

            if (ngx_strcmp(&value[i].data[14], "on") == 0) {
                use_temp_path = 1;

            } else if (ngx_strcmp(&value[i].data[14], "off") == 0) {
                use_temp_path = 0;

            } else {
                ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                                   "invalid use_temp_path value \"%V\", "
                                   "it must be \"on\" or \"off\"",
                                   &value[i]);
                return NGX_CONF_ERROR;
            }

            continue;
        }

        if (ngx_strncmp(value[i].data, "keys_zone=", 10) == 0) {

            name.data = value[i].data + 10;

            p = (u_char *) ngx_strchr(name.data, ':');

            if (p == NULL) {
                ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                                   "invalid keys zone size \"%V\"", &value[i]);
                return NGX_CONF_ERROR;
            }

            name.len = p - name.data;

            s.data = p + 1;
            s.len = value[i].data + value[i].len - s.data;

            size = ngx_parse_size(&s);

            if (size == NGX_ERROR) {
                ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                                   "invalid keys zone size \"%V\"", &value[i]);
                return NGX_CONF_ERROR;
            }

            if (size < (ssize_t) (2 * ngx_pagesize)) {
                ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                                   "keys zone \"%V\" is too small", &value[i]);
                return NGX_CONF_ERROR;
            }

            continue;
        }

        if (ngx_strncmp(value[i].data, "inactive=", 9) == 0) {

            s.len = value[i].len - 9;
            s.data = value[i].data + 9;

            inactive = ngx_parse_time(&s, 1);
            if (inactive == (time_t) NGX_ERROR) {
                ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                                   "invalid inactive value \"%V\"", &value[i]);
                return NGX_CONF_ERROR;
            }

            continue;
        }

        if (ngx_strncmp(value[i].data, "max_size=", 9) == 0) {

            s.len = value[i].len - 9;
            s.data = value[i].data + 9;

            max_size = ngx_parse_offset(&s);
            if (max_size < 0) {
                ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                                   "invalid max_size value \"%V\"", &value[i]);
                return NGX_CONF_ERROR;
            }

            continue;
        }

        if (ngx_strncmp(value[i].data, "loader_files=", 13) == 0) {

            loader_files = ngx_atoi(value[i].data + 13, value[i].len - 13);
            if (loader_files == NGX_ERROR) {
                ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "invalid loader_files value \"%V\"", &value[i]);
                return NGX_CONF_ERROR;
            }

            continue;
        }

        if (ngx_strncmp(value[i].data, "loader_sleep=", 13) == 0) {

            s.len = value[i].len - 13;
            s.data = value[i].data + 13;

            loader_sleep = ngx_parse_time(&s, 0);
            if (loader_sleep == (ngx_msec_t) NGX_ERROR) {
                ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "invalid loader_sleep value \"%V\"", &value[i]);
                return NGX_CONF_ERROR;
            }

            continue;
        }

        if (ngx_strncmp(value[i].data, "loader_threshold=", 17) == 0) {

            s.len = value[i].len - 17;
            s.data = value[i].data + 17;

            loader_threshold = ngx_parse_time(&s, 0);
            if (loader_threshold == (ngx_msec_t) NGX_ERROR) {
                ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "invalid loader_threshold value \"%V\"", &value[i]);
                return NGX_CONF_ERROR;
            }

            continue;
        }

        if (ngx_strncmp(value[i].data, "manager_files=", 14) == 0) {

            manager_files = ngx_atoi(value[i].data + 14, value[i].len - 14);
            if (manager_files == NGX_ERROR) {
                ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "invalid manager_files value \"%V\"", &value[i]);
                return NGX_CONF_ERROR;
            }

            continue;
        }

        if (ngx_strncmp(value[i].data, "manager_sleep=", 14) == 0) {

            s.len = value[i].len - 14;
            s.data = value[i].data + 14;

            manager_sleep = ngx_parse_time(&s, 0);
            if (manager_sleep == (ngx_msec_t) NGX_ERROR) {
                ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "invalid manager_sleep value \"%V\"", &value[i]);
                return NGX_CONF_ERROR;
            }

            continue;
        }

        if (ngx_strncmp(value[i].data, "manager_threshold=", 18) == 0) {

            s.len = value[i].len - 18;
            s.data = value[i].data + 18;

            manager_threshold = ngx_parse_time(&s, 0);
            if (manager_threshold == (ngx_msec_t) NGX_ERROR) {
                ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "invalid manager_threshold value \"%V\"", &value[i]);
                return NGX_CONF_ERROR;
            }

            continue;
        }

        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "invalid parameter \"%V\"", &value[i]);
        return NGX_CONF_ERROR;
    }

    if (name.len == 0 || size == 0) {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "\"%V\" must have \"keys_zone\" parameter",
                           &cmd->name);
        return NGX_CONF_ERROR;
    }

    cache->path->manager = ngx_http_file_cache_manager;
    cache->path->loader = ngx_http_file_cache_loader;
    cache->path->data = cache;
    cache->path->conf_file = cf->conf_file->file.name.data;
    cache->path->line = cf->conf_file->line;
    cache->loader_files = loader_files;
    cache->loader_sleep = loader_sleep;
    cache->loader_threshold = loader_threshold;
    cache->manager_files = manager_files;
    cache->manager_sleep = manager_sleep;
    cache->manager_threshold = manager_threshold;

    if (ngx_add_path(cf, &cache->path) != NGX_OK) {
        return NGX_CONF_ERROR;
    }

    cache->shm_zone = ngx_shared_memory_add(cf, &name, size, cmd->post);
    if (cache->shm_zone == NULL) {
        return NGX_CONF_ERROR;
    }

    if (cache->shm_zone->data) {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "duplicate zone \"%V\"", &name);
        return NGX_CONF_ERROR;
    }


    cache->shm_zone->init = ngx_http_file_cache_init;
    cache->shm_zone->data = cache;

    cache->use_temp_path = use_temp_path;

    cache->inactive = inactive;
    cache->max_size = max_size;

    caches = (ngx_array_t *) (confp + cmd->offset);

    ce = ngx_array_push(caches);
    if (ce == NULL) {
        return NGX_CONF_ERROR;
    }

    *ce = cache;

    return NGX_CONF_OK;
}