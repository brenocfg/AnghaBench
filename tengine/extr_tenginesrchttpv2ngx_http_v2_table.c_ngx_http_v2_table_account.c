#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_10__ {scalar_t__ len; } ;
struct TYPE_9__ {scalar_t__ len; } ;
struct TYPE_12__ {TYPE_3__ value; TYPE_2__ name; } ;
typedef  TYPE_5__ ngx_http_v2_header_t ;
struct TYPE_11__ {size_t free; size_t size; size_t allocated; int /*<<< orphan*/  deleted; TYPE_5__** entries; int /*<<< orphan*/  added; } ;
struct TYPE_13__ {TYPE_4__ hpack; TYPE_1__* connection; } ;
typedef  TYPE_6__ ngx_http_v2_connection_t ;
struct TYPE_8__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_DECLINED ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,size_t) ; 

__attribute__((used)) static ngx_int_t
ngx_http_v2_table_account(ngx_http_v2_connection_t *h2c, size_t size)
{
    ngx_http_v2_header_t  *entry;

    size += 32;

    ngx_log_debug2(NGX_LOG_DEBUG_HTTP, h2c->connection->log, 0,
                   "http2 table account: %uz free:%uz",
                   size, h2c->hpack.free);

    if (size <= h2c->hpack.free) {
        h2c->hpack.free -= size;
        return NGX_OK;
    }

    if (size > h2c->hpack.size) {
        h2c->hpack.deleted = h2c->hpack.added;
        h2c->hpack.free = h2c->hpack.size;
        return NGX_DECLINED;
    }

    do {
        entry = h2c->hpack.entries[h2c->hpack.deleted++ % h2c->hpack.allocated];
        h2c->hpack.free += 32 + entry->name.len + entry->value.len;
    } while (size > h2c->hpack.free);

    h2c->hpack.free -= size;

    return NGX_OK;
}