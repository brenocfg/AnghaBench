#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
struct TYPE_7__ {int totalswap; int freeswap; scalar_t__ bufferram; scalar_t__ cachedram; scalar_t__ freeram; } ;
typedef  TYPE_2__ ngx_meminfo_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_8__ {TYPE_1__* connection; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_6__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ NGX_CONF_UNSET_SIZE ; 
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_getmeminfo (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_sysguard_cached_free ; 
 scalar_t__ ngx_http_sysguard_cached_mem_exptime ; 
 int ngx_http_sysguard_cached_swapstat ; 
 scalar_t__ ngx_time () ; 

__attribute__((used)) static ngx_int_t
ngx_http_sysguard_update_mem(ngx_http_request_t *r, time_t exptime)
{
    ngx_int_t      rc;
    ngx_meminfo_t  m;

    ngx_http_sysguard_cached_mem_exptime = ngx_time() + exptime;

    rc = ngx_getmeminfo(&m, r->connection->log);
    if (rc == NGX_ERROR) {

        ngx_http_sysguard_cached_swapstat = 0;
        ngx_http_sysguard_cached_free = NGX_CONF_UNSET_SIZE;

        return NGX_ERROR;
    }

    ngx_http_sysguard_cached_swapstat = m.totalswap == 0
        ? 0 : (m.totalswap - m.freeswap) * 100 / m.totalswap;
    ngx_http_sysguard_cached_free = m.freeram + m.cachedram + m.bufferram;

    return NGX_OK;
}