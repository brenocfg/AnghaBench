#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_12__ {size_t len; int valid; int not_found; scalar_t__ no_cacheable; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ ngx_http_variable_value_t ;
struct TYPE_13__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_14__ {int /*<<< orphan*/ * org; scalar_t__ org_v6; } ;
typedef  TYPE_3__ ngx_http_geoip_conf_t ;

/* Variables and functions */
 char* GeoIP_name_by_ipnum (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* GeoIP_name_by_ipnum_v6 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_free (char*) ; 
 int /*<<< orphan*/  ngx_http_geoip_addr (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_http_geoip_addr_v6 (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_http_geoip_module ; 
 TYPE_3__* ngx_http_get_module_main_conf (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_memcpy (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/ * ngx_pnalloc (int /*<<< orphan*/ ,size_t) ; 
 size_t ngx_strlen (char*) ; 

__attribute__((used)) static ngx_int_t
ngx_http_geoip_org_variable(ngx_http_request_t *r,
    ngx_http_variable_value_t *v, uintptr_t data)
{
    size_t                  len;
    char                   *val;
    ngx_http_geoip_conf_t  *gcf;

    gcf = ngx_http_get_module_main_conf(r, ngx_http_geoip_module);

    if (gcf->org == NULL) {
        goto not_found;
    }

#if (NGX_HAVE_GEOIP_V6)
    val = gcf->org_v6
              ? GeoIP_name_by_ipnum_v6(gcf->org,
                                       ngx_http_geoip_addr_v6(r, gcf))
              : GeoIP_name_by_ipnum(gcf->org,
                                    ngx_http_geoip_addr(r, gcf));
#else
    val = GeoIP_name_by_ipnum(gcf->org, ngx_http_geoip_addr(r, gcf));
#endif

    if (val == NULL) {
        goto not_found;
    }

    len = ngx_strlen(val);
    v->data = ngx_pnalloc(r->pool, len);
    if (v->data == NULL) {
        ngx_free(val);
        return NGX_ERROR;
    }

    ngx_memcpy(v->data, val, len);

    v->len = len;
    v->valid = 1;
    v->no_cacheable = 0;
    v->not_found = 0;

    ngx_free(val);

    return NGX_OK;

not_found:

    v->not_found = 1;

    return NGX_OK;
}