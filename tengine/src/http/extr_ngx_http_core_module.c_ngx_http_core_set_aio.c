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

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_thread_pool_t ;
struct TYPE_15__ {char* data; int len; } ;
typedef  TYPE_2__ ngx_str_t ;
struct TYPE_16__ {scalar_t__ aio; int /*<<< orphan*/ * thread_pool; TYPE_4__* thread_pool_value; } ;
typedef  TYPE_3__ ngx_http_core_loc_conf_t ;
struct TYPE_17__ {int /*<<< orphan*/ * lengths; } ;
typedef  TYPE_4__ ngx_http_complex_value_t ;
struct TYPE_18__ {TYPE_4__* complex_value; TYPE_2__* value; TYPE_6__* cf; } ;
typedef  TYPE_5__ ngx_http_compile_complex_value_t ;
struct TYPE_19__ {int /*<<< orphan*/  pool; TYPE_1__* args; } ;
typedef  TYPE_6__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_14__ {TYPE_2__* elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_CONF_UNSET ; 
 scalar_t__ NGX_HTTP_AIO_OFF ; 
 void* NGX_HTTP_AIO_ON ; 
 scalar_t__ NGX_HTTP_AIO_THREADS ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 int /*<<< orphan*/  NGX_LOG_WARN ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ngx_http_compile_complex_value (TYPE_5__*) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_5__*,int) ; 
 TYPE_4__* ngx_palloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ngx_strcmp (char*,char*) ; 
 scalar_t__ ngx_strncmp (char*,char*,int) ; 
 int /*<<< orphan*/ * ngx_thread_pool_add (TYPE_6__*,TYPE_2__*) ; 

__attribute__((used)) static char *
ngx_http_core_set_aio(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_core_loc_conf_t *clcf = conf;

    ngx_str_t  *value;

    if (clcf->aio != NGX_CONF_UNSET) {
        return "is duplicate";
    }

#if (NGX_THREADS)
    clcf->thread_pool = NULL;
    clcf->thread_pool_value = NULL;
#endif

    value = cf->args->elts;

    if (ngx_strcmp(value[1].data, "off") == 0) {
        clcf->aio = NGX_HTTP_AIO_OFF;
        return NGX_CONF_OK;
    }

    if (ngx_strcmp(value[1].data, "on") == 0) {
#if (NGX_HAVE_FILE_AIO)
        clcf->aio = NGX_HTTP_AIO_ON;
        return NGX_CONF_OK;
#else
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "\"aio on\" "
                           "is unsupported on this platform");
        return NGX_CONF_ERROR;
#endif
    }

#if (NGX_HAVE_AIO_SENDFILE)

    if (ngx_strcmp(value[1].data, "sendfile") == 0) {
        clcf->aio = NGX_HTTP_AIO_ON;

        ngx_conf_log_error(NGX_LOG_WARN, cf, 0,
                           "the \"sendfile\" parameter of "
                           "the \"aio\" directive is deprecated");
        return NGX_CONF_OK;
    }

#endif

    if (ngx_strncmp(value[1].data, "threads", 7) == 0
        && (value[1].len == 7 || value[1].data[7] == '='))
    {
#if (NGX_THREADS)
        ngx_str_t                          name;
        ngx_thread_pool_t                 *tp;
        ngx_http_complex_value_t           cv;
        ngx_http_compile_complex_value_t   ccv;

        clcf->aio = NGX_HTTP_AIO_THREADS;

        if (value[1].len >= 8) {
            name.len = value[1].len - 8;
            name.data = value[1].data + 8;

            ngx_memzero(&ccv, sizeof(ngx_http_compile_complex_value_t));

            ccv.cf = cf;
            ccv.value = &name;
            ccv.complex_value = &cv;

            if (ngx_http_compile_complex_value(&ccv) != NGX_OK) {
                return NGX_CONF_ERROR;
            }

            if (cv.lengths != NULL) {
                clcf->thread_pool_value = ngx_palloc(cf->pool,
                                    sizeof(ngx_http_complex_value_t));
                if (clcf->thread_pool_value == NULL) {
                    return NGX_CONF_ERROR;
                }

                *clcf->thread_pool_value = cv;

                return NGX_CONF_OK;
            }

            tp = ngx_thread_pool_add(cf, &name);

        } else {
            tp = ngx_thread_pool_add(cf, NULL);
        }

        if (tp == NULL) {
            return NGX_CONF_ERROR;
        }

        clcf->thread_pool = tp;

        return NGX_CONF_OK;
#else
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "\"aio threads\" "
                           "is unsupported on this platform");
        return NGX_CONF_ERROR;
#endif
    }

    return "invalid value";
}