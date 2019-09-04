#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_7__ {scalar_t__ len; } ;
struct TYPE_5__ {TYPE_3__ profiles; } ;
typedef  TYPE_1__ ngx_google_perftools_conf_t ;
struct TYPE_6__ {int /*<<< orphan*/  log; int /*<<< orphan*/  conf_ctx; } ;
typedef  TYPE_2__ ngx_cycle_t ;

/* Variables and functions */
 scalar_t__ NGX_INT_T_LEN ; 
 int /*<<< orphan*/  NGX_LOG_CRIT ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ProfilerRegisterThread () ; 
 scalar_t__ ProfilerStart (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ProfilerStop () ; 
 scalar_t__ getenv (char*) ; 
 int /*<<< orphan*/ * ngx_alloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_errno ; 
 int /*<<< orphan*/  ngx_free (int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_get_conf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_google_perftools_module ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_pid ; 
 int /*<<< orphan*/  ngx_sprintf (int /*<<< orphan*/ *,char*,TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_google_perftools_worker(ngx_cycle_t *cycle)
{
    u_char                       *profile;
    ngx_google_perftools_conf_t  *gptcf;

    gptcf = (ngx_google_perftools_conf_t *)
                ngx_get_conf(cycle->conf_ctx, ngx_google_perftools_module);

    if (gptcf->profiles.len == 0) {
        return NGX_OK;
    }

    profile = ngx_alloc(gptcf->profiles.len + NGX_INT_T_LEN + 2, cycle->log);
    if (profile == NULL) {
        return NGX_OK;
    }

    if (getenv("CPUPROFILE")) {
        /* disable inherited Profiler enabled in master process */
        ProfilerStop();
    }

    ngx_sprintf(profile, "%V.%d%Z", &gptcf->profiles, ngx_pid);

    if (ProfilerStart(profile)) {
        /* start ITIMER_PROF timer */
        ProfilerRegisterThread();

    } else {
        ngx_log_error(NGX_LOG_CRIT, cycle->log, ngx_errno,
                      "ProfilerStart(%s) failed", profile);
    }

    ngx_free(profile);

    return NGX_OK;
}