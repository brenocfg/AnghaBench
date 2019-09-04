#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ use_event; TYPE_3__* event; scalar_t__ count; } ;
typedef  TYPE_1__ ngx_cached_open_file_t ;
struct TYPE_6__ {struct TYPE_6__* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_CLOSE_EVENT ; 
 int /*<<< orphan*/  NGX_FLUSH_EVENT ; 
 int /*<<< orphan*/  NGX_VNODE_EVENT ; 
 int /*<<< orphan*/  ngx_del_event (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_free (TYPE_3__*) ; 

__attribute__((used)) static void
ngx_open_file_del_event(ngx_cached_open_file_t *file)
{
    if (file->event == NULL) {
        return;
    }

    (void) ngx_del_event(file->event, NGX_VNODE_EVENT,
                         file->count ? NGX_FLUSH_EVENT : NGX_CLOSE_EVENT);

    ngx_free(file->event->data);
    ngx_free(file->event);
    file->event = NULL;
    file->use_event = 0;
}