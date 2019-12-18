#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int ngx_uint_t ;
struct TYPE_4__ {scalar_t__ count; } ;
typedef  TYPE_1__ ngx_http_lua_log_ringbuf_t ;
struct TYPE_5__ {TYPE_1__* intercept_error_log_data; } ;

/* Variables and functions */
 int NGX_DONE ; 
 int NGX_ERROR ; 
 TYPE_3__* ngx_cycle ; 
 int /*<<< orphan*/  ngx_http_lua_log_ringbuf_read (TYPE_1__*,int*,void**,int*,double*) ; 
 int /*<<< orphan*/ * ngx_snprintf (int /*<<< orphan*/ *,size_t,char*) ; 

int
ngx_http_lua_ffi_errlog_get_msg(char **log, int *loglevel, u_char *err,
    size_t *errlen, double *log_time)
{
#ifdef HAVE_INTERCEPT_ERROR_LOG_PATCH
    ngx_uint_t           loglen;

    ngx_http_lua_log_ringbuf_t     *ringbuf;

    ringbuf = ngx_cycle->intercept_error_log_data;

    if (ringbuf == NULL) {
        *errlen = ngx_snprintf(err, *errlen,
                               "directive \"lua_capture_error_log\" is not set")
                  - err;
        return NGX_ERROR;
    }

    if (ringbuf->count == 0) {
        return NGX_DONE;
    }

    ngx_http_lua_log_ringbuf_read(ringbuf, loglevel, (void **) log, &loglen,
                                  log_time);
    return loglen;
#else
    *errlen = ngx_snprintf(err, *errlen,
                           "missing the capture error log patch for nginx")
              - err;
    return NGX_ERROR;
#endif
}