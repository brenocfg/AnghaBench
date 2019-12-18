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
struct TYPE_8__ {TYPE_2__* data; int /*<<< orphan*/  handler; } ;
typedef  TYPE_1__ ngx_pool_cleanup_t ;
struct TYPE_9__ {TYPE_3__* connection; int /*<<< orphan*/  waiting_list; int /*<<< orphan*/  leak_list; int /*<<< orphan*/  send_list; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ ngx_multi_connection_t ;
struct TYPE_10__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_3__ ngx_connection_t ;

/* Variables and functions */
 int /*<<< orphan*/  ngx_multi_cleanup ; 
 TYPE_2__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* ngx_pool_cleanup_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_queue_init (int /*<<< orphan*/ *) ; 

ngx_multi_connection_t*
ngx_create_multi_connection(ngx_connection_t *c)
{
    ngx_multi_connection_t      *multi_c;
    ngx_pool_cleanup_t          *cln;

    //init multi connection
    multi_c = ngx_pcalloc(c->pool, sizeof(ngx_multi_connection_t));
    if (multi_c == NULL) {
        return NULL;
    }

    ngx_queue_init(&multi_c->data);
    ngx_queue_init(&multi_c->send_list);
    ngx_queue_init(&multi_c->leak_list);
    ngx_queue_init(&multi_c->waiting_list);
    
    multi_c->connection = c;

    cln = ngx_pool_cleanup_add(c->pool, 0);
    if (cln == NULL) {
        return NULL;
    }

    cln->handler = ngx_multi_cleanup;
    cln->data = multi_c;

    return multi_c;
}