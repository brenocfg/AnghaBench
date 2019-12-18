#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ fd; scalar_t__ min_uses; int /*<<< orphan*/  events; } ;
typedef  TYPE_1__ ngx_open_file_info_t ;
typedef  int /*<<< orphan*/  ngx_open_file_cache_t ;
struct TYPE_12__ {scalar_t__ fd; struct TYPE_12__* data; int /*<<< orphan*/  log; int /*<<< orphan*/  handler; int /*<<< orphan*/ * cache; TYPE_3__* file; } ;
typedef  TYPE_2__ ngx_open_file_cache_event_t ;
typedef  int /*<<< orphan*/  ngx_log_t ;
typedef  int /*<<< orphan*/  ngx_event_t ;
struct TYPE_13__ {scalar_t__ uses; TYPE_2__* event; scalar_t__ use_event; } ;
typedef  TYPE_3__ ngx_cached_open_file_t ;
struct TYPE_14__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ NGX_INVALID_FILE ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  NGX_ONESHOT_EVENT ; 
 int NGX_USE_VNODE_EVENT ; 
 int /*<<< orphan*/  NGX_VNODE_EVENT ; 
 scalar_t__ ngx_add_event (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* ngx_alloc (int,int /*<<< orphan*/ *) ; 
 TYPE_2__* ngx_calloc (int,int /*<<< orphan*/ *) ; 
 TYPE_7__* ngx_cycle ; 
 int ngx_event_flags ; 
 int /*<<< orphan*/  ngx_free (TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_open_file_cache_remove ; 

__attribute__((used)) static void
ngx_open_file_add_event(ngx_open_file_cache_t *cache,
    ngx_cached_open_file_t *file, ngx_open_file_info_t *of, ngx_log_t *log)
{
    ngx_open_file_cache_event_t  *fev;

    if (!(ngx_event_flags & NGX_USE_VNODE_EVENT)
        || !of->events
        || file->event
        || of->fd == NGX_INVALID_FILE
        || file->uses < of->min_uses)
    {
        return;
    }

    file->use_event = 0;

    file->event = ngx_calloc(sizeof(ngx_event_t), log);
    if (file->event== NULL) {
        return;
    }

    fev = ngx_alloc(sizeof(ngx_open_file_cache_event_t), log);
    if (fev == NULL) {
        ngx_free(file->event);
        file->event = NULL;
        return;
    }

    fev->fd = of->fd;
    fev->file = file;
    fev->cache = cache;

    file->event->handler = ngx_open_file_cache_remove;
    file->event->data = fev;

    /*
     * although vnode event may be called while ngx_cycle->poll
     * destruction, however, cleanup procedures are run before any
     * memory freeing and events will be canceled.
     */

    file->event->log = ngx_cycle->log;

    if (ngx_add_event(file->event, NGX_VNODE_EVENT, NGX_ONESHOT_EVENT)
        != NGX_OK)
    {
        ngx_free(file->event->data);
        ngx_free(file->event);
        file->event = NULL;
        return;
    }

    /*
     * we do not set file->use_event here because there may be a race
     * condition: a file may be deleted between opening the file and
     * adding event, so we rely upon event notification only after
     * one file revalidation on next file access
     */

    return;
}