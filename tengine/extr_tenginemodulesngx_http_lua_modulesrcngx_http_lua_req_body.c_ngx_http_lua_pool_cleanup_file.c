#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* cleanup; } ;
typedef  TYPE_1__ ngx_pool_t ;
struct TYPE_9__ {int /*<<< orphan*/  (* handler ) (TYPE_3__*) ;TYPE_3__* data; struct TYPE_9__* next; } ;
typedef  TYPE_2__ ngx_pool_cleanup_t ;
struct TYPE_10__ {scalar_t__ fd; } ;
typedef  TYPE_3__ ngx_pool_cleanup_file_t ;
typedef  scalar_t__ ngx_fd_t ;

/* Variables and functions */
 int /*<<< orphan*/  ngx_pool_cleanup_file (TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_pool_delete_file (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

__attribute__((used)) static void
ngx_http_lua_pool_cleanup_file(ngx_pool_t *p, ngx_fd_t fd)
{
    ngx_pool_cleanup_t       *c;
    ngx_pool_cleanup_file_t  *cf;

    for (c = p->cleanup; c; c = c->next) {
        if (c->handler == ngx_pool_cleanup_file
            || c->handler == ngx_pool_delete_file)
        {
            cf = c->data;

            if (cf->fd == fd) {
                c->handler(cf);
                c->handler = NULL;
                return;
            }
        }
    }
}