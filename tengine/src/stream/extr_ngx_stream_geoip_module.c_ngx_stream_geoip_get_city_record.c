#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_stream_session_t ;
struct TYPE_5__ {scalar_t__ city; scalar_t__ city_v6; } ;
typedef  TYPE_1__ ngx_stream_geoip_conf_t ;
typedef  int /*<<< orphan*/  GeoIPRecord ;

/* Variables and functions */
 int /*<<< orphan*/ * GeoIP_record_by_ipnum (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GeoIP_record_by_ipnum_v6 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_stream_geoip_addr (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ngx_stream_geoip_addr_v6 (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ngx_stream_geoip_module ; 
 TYPE_1__* ngx_stream_get_module_main_conf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static GeoIPRecord *
ngx_stream_geoip_get_city_record(ngx_stream_session_t *s)
{
    ngx_stream_geoip_conf_t  *gcf;

    gcf = ngx_stream_get_module_main_conf(s, ngx_stream_geoip_module);

    if (gcf->city) {
#if (NGX_HAVE_GEOIP_V6)
        return gcf->city_v6
                   ? GeoIP_record_by_ipnum_v6(gcf->city,
                                              ngx_stream_geoip_addr_v6(s, gcf))
                   : GeoIP_record_by_ipnum(gcf->city,
                                           ngx_stream_geoip_addr(s, gcf));
#else
        return GeoIP_record_by_ipnum(gcf->city, ngx_stream_geoip_addr(s, gcf));
#endif
    }

    return NULL;
}