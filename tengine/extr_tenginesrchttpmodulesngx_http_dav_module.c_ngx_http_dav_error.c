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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_log_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_EACCES ; 
 int /*<<< orphan*/  NGX_EEXIST ; 
 int /*<<< orphan*/  NGX_ENAMETOOLONG ; 
 int /*<<< orphan*/  NGX_ENOENT ; 
 int /*<<< orphan*/  NGX_ENOSPC ; 
 int /*<<< orphan*/  NGX_ENOTDIR ; 
 int /*<<< orphan*/  NGX_EPERM ; 
 int /*<<< orphan*/  NGX_HTTP_FORBIDDEN ; 
 int /*<<< orphan*/  NGX_HTTP_INSUFFICIENT_STORAGE ; 
 int /*<<< orphan*/  NGX_HTTP_INTERNAL_SERVER_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_NOT_ALLOWED ; 
 int /*<<< orphan*/  NGX_LOG_CRIT ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ngx_int_t
ngx_http_dav_error(ngx_log_t *log, ngx_err_t err, ngx_int_t not_found,
    char *failed, u_char *path)
{
    ngx_int_t   rc;
    ngx_uint_t  level;

    if (err == NGX_ENOENT || err == NGX_ENOTDIR || err == NGX_ENAMETOOLONG) {
        level = NGX_LOG_ERR;
        rc = not_found;

    } else if (err == NGX_EACCES || err == NGX_EPERM) {
        level = NGX_LOG_ERR;
        rc = NGX_HTTP_FORBIDDEN;

    } else if (err == NGX_EEXIST) {
        level = NGX_LOG_ERR;
        rc = NGX_HTTP_NOT_ALLOWED;

    } else if (err == NGX_ENOSPC) {
        level = NGX_LOG_CRIT;
        rc = NGX_HTTP_INSUFFICIENT_STORAGE;

    } else {
        level = NGX_LOG_CRIT;
        rc = NGX_HTTP_INTERNAL_SERVER_ERROR;
    }

    ngx_log_error(level, log, err, "%s \"%s\" failed", failed, path);

    return rc;
}