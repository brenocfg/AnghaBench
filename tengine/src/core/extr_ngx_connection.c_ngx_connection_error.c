#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_err_t ;
struct TYPE_3__ {int log_error; int /*<<< orphan*/  log; } ;
typedef  TYPE_1__ ngx_connection_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ECONNABORTED ; 
 int /*<<< orphan*/  NGX_ECONNREFUSED ; 
 int /*<<< orphan*/  NGX_ECONNRESET ; 
 int /*<<< orphan*/  NGX_EHOSTDOWN ; 
 int /*<<< orphan*/  NGX_EHOSTUNREACH ; 
 int /*<<< orphan*/  NGX_EINVAL ; 
 int /*<<< orphan*/  NGX_ENETDOWN ; 
 int /*<<< orphan*/  NGX_ENETUNREACH ; 
 int /*<<< orphan*/  NGX_ENOTCONN ; 
 int /*<<< orphan*/  NGX_EPIPE ; 
 int /*<<< orphan*/  NGX_ERROR ; 
#define  NGX_ERROR_IGNORE_ECONNRESET 130 
#define  NGX_ERROR_IGNORE_EINVAL 129 
#define  NGX_ERROR_INFO 128 
 int /*<<< orphan*/  NGX_ETIMEDOUT ; 
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

ngx_int_t
ngx_connection_error(ngx_connection_t *c, ngx_err_t err, char *text)
{
    ngx_uint_t  level;

    /* Winsock may return NGX_ECONNABORTED instead of NGX_ECONNRESET */

    if ((err == NGX_ECONNRESET
#if (NGX_WIN32)
         || err == NGX_ECONNABORTED
#endif
        ) && c->log_error == NGX_ERROR_IGNORE_ECONNRESET)
    {
        return 0;
    }

#if (NGX_SOLARIS)
    if (err == NGX_EINVAL && c->log_error == NGX_ERROR_IGNORE_EINVAL) {
        return 0;
    }
#endif

    if (err == 0
        || err == NGX_ECONNRESET
#if (NGX_WIN32)
        || err == NGX_ECONNABORTED
#else
        || err == NGX_EPIPE
#endif
        || err == NGX_ENOTCONN
        || err == NGX_ETIMEDOUT
        || err == NGX_ECONNREFUSED
        || err == NGX_ENETDOWN
        || err == NGX_ENETUNREACH
        || err == NGX_EHOSTDOWN
        || err == NGX_EHOSTUNREACH)
    {
        switch (c->log_error) {

        case NGX_ERROR_IGNORE_EINVAL:
        case NGX_ERROR_IGNORE_ECONNRESET:
        case NGX_ERROR_INFO:
            level = NGX_LOG_INFO;
            break;

        default:
            level = NGX_LOG_ERR;
        }

    } else {
        level = NGX_LOG_ALERT;
    }

    ngx_log_error(level, c->log, err, text);

    return NGX_ERROR;
}