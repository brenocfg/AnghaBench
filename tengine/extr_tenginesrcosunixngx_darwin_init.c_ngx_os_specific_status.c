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
typedef  int u_long ;
typedef  size_t ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_log_t ;
struct TYPE_2__ {int size; scalar_t__* name; scalar_t__ value; scalar_t__ exists; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_NOTICE ; 
 int ngx_darwin_kern_osrelease ; 
 scalar_t__* ngx_darwin_kern_ostype ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,scalar_t__*,int) ; 
 TYPE_1__* sysctls ; 

void
ngx_os_specific_status(ngx_log_t *log)
{
    u_long      value;
    ngx_uint_t  i;

    if (ngx_darwin_kern_ostype[0]) {
        ngx_log_error(NGX_LOG_NOTICE, log, 0, "OS: %s %s",
                      ngx_darwin_kern_ostype, ngx_darwin_kern_osrelease);
    }

    for (i = 0; sysctls[i].name; i++) {
        if (sysctls[i].exists) {
            if (sysctls[i].size == sizeof(long)) {
                value = *(long *) sysctls[i].value;

            } else {
                value = *(int *) sysctls[i].value;
            }

            ngx_log_error(NGX_LOG_NOTICE, log, 0, "%s: %l",
                          sysctls[i].name, value);
        }
    }
}