#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ count; size_t size; scalar_t__ tail; scalar_t__ head; size_t data; } ;
typedef  TYPE_1__ ngx_http_lua_log_ringbuf_t ;

/* Variables and functions */

__attribute__((used)) static size_t
ngx_http_lua_log_ringbuf_free_spaces(ngx_http_lua_log_ringbuf_t *rb)
{
    if (rb->count == 0) {
        return rb->size;
    }

    if (rb->tail > rb->head) {
        return rb->data + rb->size - rb->tail;
    }

    return rb->head - rb->tail;
}