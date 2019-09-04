#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_6__ {scalar_t__ count; void* head; void* sentinel; } ;
typedef  TYPE_1__ ngx_http_lua_log_ringbuf_t ;
struct TYPE_7__ {int log_level; size_t len; double time; } ;
typedef  TYPE_2__ ngx_http_lua_log_ringbuf_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  HEADER_LEN ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 void* ngx_http_lua_log_ringbuf_next_header (TYPE_1__*) ; 
 int /*<<< orphan*/  ngx_http_lua_log_ringbuf_reset (TYPE_1__*) ; 

ngx_int_t
ngx_http_lua_log_ringbuf_read(ngx_http_lua_log_ringbuf_t *rb, int *log_level,
    void **buf, size_t *n, double *log_time)
{
    ngx_http_lua_log_ringbuf_header_t       *head;

    if (rb->count == 0) {
        return NGX_ERROR;
    }

    head = (ngx_http_lua_log_ringbuf_header_t *) rb->head;

    if (rb->head >= rb->sentinel) {
        return NGX_ERROR;
    }

    *log_level = head->log_level;
    *n = head->len;
    rb->head += HEADER_LEN;
    *buf = rb->head;
    rb->head += head->len;

    if (log_time) {
        *log_time = head->time;
    }

    rb->count--;

    if (rb->count == 0) {
        ngx_http_lua_log_ringbuf_reset(rb);
    }

    rb->head = ngx_http_lua_log_ringbuf_next_header(rb);

    return NGX_OK;
}