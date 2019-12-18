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
struct TYPE_2__ {int /*<<< orphan*/  overflow_threshold; int /*<<< orphan*/  overflow_test; int /*<<< orphan*/  overflow_events; int /*<<< orphan*/  signo; } ;
typedef  TYPE_1__ ngx_rtsig_conf_t ;
typedef  int /*<<< orphan*/  ngx_cycle_t ;

/* Variables and functions */
 char* NGX_CONF_OK ; 
 int SIGRTMIN ; 
 int /*<<< orphan*/  ngx_conf_init_uint_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static char *
ngx_rtsig_init_conf(ngx_cycle_t *cycle, void *conf)
{
    ngx_rtsig_conf_t  *rtscf = conf;

    /* LinuxThreads use the first 3 RT signals */
    ngx_conf_init_uint_value(rtscf->signo, SIGRTMIN + 10);

    ngx_conf_init_uint_value(rtscf->overflow_events, 16);
    ngx_conf_init_uint_value(rtscf->overflow_test, 32);
    ngx_conf_init_uint_value(rtscf->overflow_threshold, 10);

    return NGX_CONF_OK;
}