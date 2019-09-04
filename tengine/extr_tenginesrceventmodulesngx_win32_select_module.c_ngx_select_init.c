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
typedef  int /*<<< orphan*/  ngx_msec_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_event_t ;
struct TYPE_6__ {int connection_n; int /*<<< orphan*/  log; TYPE_1__* old_cycle; } ;
typedef  TYPE_2__ ngx_cycle_t ;
struct TYPE_7__ {int /*<<< orphan*/  actions; } ;
struct TYPE_5__ {int connection_n; } ;

/* Variables and functions */
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 scalar_t__ NGX_PROCESS_WORKER ; 
 int /*<<< orphan*/  NGX_USE_LEVEL_EVENT ; 
 int /*<<< orphan*/ ** event_index ; 
 int /*<<< orphan*/  master_read_fd_set ; 
 int /*<<< orphan*/  master_write_fd_set ; 
 scalar_t__ max_read ; 
 scalar_t__ max_write ; 
 int nevents ; 
 int /*<<< orphan*/ ** ngx_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_event_actions ; 
 int /*<<< orphan*/  ngx_event_flags ; 
 int /*<<< orphan*/  ngx_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ngx_io ; 
 int /*<<< orphan*/  ngx_memcpy (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  ngx_os_io ; 
 scalar_t__ ngx_process ; 
 TYPE_3__ ngx_select_module_ctx ; 

__attribute__((used)) static ngx_int_t
ngx_select_init(ngx_cycle_t *cycle, ngx_msec_t timer)
{
    ngx_event_t  **index;

    if (event_index == NULL) {
        FD_ZERO(&master_read_fd_set);
        FD_ZERO(&master_write_fd_set);
        nevents = 0;
    }

    if (ngx_process >= NGX_PROCESS_WORKER
        || cycle->old_cycle == NULL
        || cycle->old_cycle->connection_n < cycle->connection_n)
    {
        index = ngx_alloc(sizeof(ngx_event_t *) * 2 * cycle->connection_n,
                          cycle->log);
        if (index == NULL) {
            return NGX_ERROR;
        }

        if (event_index) {
            ngx_memcpy(index, event_index, sizeof(ngx_event_t *) * nevents);
            ngx_free(event_index);
        }

        event_index = index;
    }

    ngx_io = ngx_os_io;

    ngx_event_actions = ngx_select_module_ctx.actions;

    ngx_event_flags = NGX_USE_LEVEL_EVENT;

    max_read = 0;
    max_write = 0;

    return NGX_OK;
}