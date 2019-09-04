#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int not_found; int valid; scalar_t__ no_cacheable; int /*<<< orphan*/ * data; int /*<<< orphan*/ * len; } ;
typedef  TYPE_2__ ngx_stream_variable_value_t ;
struct TYPE_9__ {TYPE_1__* connection; } ;
typedef  TYPE_3__ ngx_stream_session_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_7__ {int /*<<< orphan*/  pool; } ;
typedef  int /*<<< orphan*/  GeoIPRecord ;

/* Variables and functions */
 int /*<<< orphan*/  GeoIPRecord_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 scalar_t__ NGX_INT64_LEN ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/ * ngx_pnalloc (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * ngx_sprintf (int /*<<< orphan*/ *,char*,float) ; 
 int /*<<< orphan*/ * ngx_stream_geoip_get_city_record (TYPE_3__*) ; 

__attribute__((used)) static ngx_int_t
ngx_stream_geoip_city_float_variable(ngx_stream_session_t *s,
    ngx_stream_variable_value_t *v, uintptr_t data)
{
    float         val;
    GeoIPRecord  *gr;

    gr = ngx_stream_geoip_get_city_record(s);
    if (gr == NULL) {
        v->not_found = 1;
        return NGX_OK;
    }

    v->data = ngx_pnalloc(s->connection->pool, NGX_INT64_LEN + 5);
    if (v->data == NULL) {
        GeoIPRecord_delete(gr);
        return NGX_ERROR;
    }

    val = *(float *) ((char *) gr + data);

    v->len = ngx_sprintf(v->data, "%.4f", val) - v->data;
    v->valid = 1;
    v->no_cacheable = 0;
    v->not_found = 0;

    GeoIPRecord_delete(gr);

    return NGX_OK;
}