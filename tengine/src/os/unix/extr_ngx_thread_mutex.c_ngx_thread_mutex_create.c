#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  pthread_mutexattr_t ;
typedef  int /*<<< orphan*/  ngx_thread_mutex_t ;
typedef  int /*<<< orphan*/  ngx_log_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  scalar_t__ ngx_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  PTHREAD_MUTEX_ERRORCHECK ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,char*) ; 
 scalar_t__ pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutexattr_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutexattr_init (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutexattr_settype (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

ngx_int_t
ngx_thread_mutex_create(ngx_thread_mutex_t *mtx, ngx_log_t *log)
{
    ngx_err_t            err;
    pthread_mutexattr_t  attr;

    err = pthread_mutexattr_init(&attr);
    if (err != 0) {
        ngx_log_error(NGX_LOG_EMERG, log, err,
                      "pthread_mutexattr_init() failed");
        return NGX_ERROR;
    }

    err = pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK);
    if (err != 0) {
        ngx_log_error(NGX_LOG_EMERG, log, err,
                      "pthread_mutexattr_settype"
                      "(PTHREAD_MUTEX_ERRORCHECK) failed");
        return NGX_ERROR;
    }

    err = pthread_mutex_init(mtx, &attr);
    if (err != 0) {
        ngx_log_error(NGX_LOG_EMERG, log, err,
                      "pthread_mutex_init() failed");
        return NGX_ERROR;
    }

    err = pthread_mutexattr_destroy(&attr);
    if (err != 0) {
        ngx_log_error(NGX_LOG_ALERT, log, err,
                      "pthread_mutexattr_destroy() failed");
    }

    return NGX_OK;
}