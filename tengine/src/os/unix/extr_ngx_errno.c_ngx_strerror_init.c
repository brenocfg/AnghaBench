#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int ngx_err_t ;
struct TYPE_2__ {size_t len; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 int NGX_SYS_NERR ; 
 int errno ; 
 void* malloc (size_t) ; 
 int /*<<< orphan*/  ngx_log_stderr (int /*<<< orphan*/ ,char*,size_t,int,char*) ; 
 int /*<<< orphan*/  ngx_memcpy (int /*<<< orphan*/ *,char*,size_t) ; 
 size_t ngx_strlen (char*) ; 
 TYPE_1__* ngx_sys_errlist ; 
 char* strerror (int) ; 

ngx_int_t
ngx_strerror_init(void)
{
    char       *msg;
    u_char     *p;
    size_t      len;
    ngx_err_t   err;

    /*
     * ngx_strerror() is not ready to work at this stage, therefore,
     * malloc() is used and possible errors are logged using strerror().
     */

    len = NGX_SYS_NERR * sizeof(ngx_str_t);

    ngx_sys_errlist = malloc(len);
    if (ngx_sys_errlist == NULL) {
        goto failed;
    }

    for (err = 0; err < NGX_SYS_NERR; err++) {
        msg = strerror(err);
        len = ngx_strlen(msg);

        p = malloc(len);
        if (p == NULL) {
            goto failed;
        }

        ngx_memcpy(p, msg, len);
        ngx_sys_errlist[err].len = len;
        ngx_sys_errlist[err].data = p;
    }

    return NGX_OK;

failed:

    err = errno;
    ngx_log_stderr(0, "malloc(%uz) failed (%d: %s)", len, err, strerror(err));

    return NGX_ERROR;
}