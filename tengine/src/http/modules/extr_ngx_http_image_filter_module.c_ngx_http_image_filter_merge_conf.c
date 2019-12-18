#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ filter; scalar_t__ angle; scalar_t__ jpeg_quality; scalar_t__ webp_quality; scalar_t__ sharpen; scalar_t__ offset_x; scalar_t__ offset_y; int /*<<< orphan*/ * oycv; int /*<<< orphan*/ * oxcv; int /*<<< orphan*/  buffer_size; int /*<<< orphan*/  interlace; int /*<<< orphan*/  transparency; int /*<<< orphan*/ * acv; int /*<<< orphan*/ * shcv; int /*<<< orphan*/ * wqcv; int /*<<< orphan*/ * jqcv; int /*<<< orphan*/  hcv; int /*<<< orphan*/  wcv; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_1__ ngx_http_image_filter_conf_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;

/* Variables and functions */
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_CONF_UNSET_UINT ; 
 scalar_t__ NGX_HTTP_IMAGE_OFF ; 
 int NGX_HTTP_IMAGE_OFFSET_CENTER ; 
 int /*<<< orphan*/  ngx_conf_merge_size_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_conf_merge_uint_value (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  ngx_conf_merge_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static char *
ngx_http_image_filter_merge_conf(ngx_conf_t *cf, void *parent, void *child)
{
    ngx_http_image_filter_conf_t *prev = parent;
    ngx_http_image_filter_conf_t *conf = child;

    if (conf->filter == NGX_CONF_UNSET_UINT) {

        if (prev->filter == NGX_CONF_UNSET_UINT) {
            conf->filter = NGX_HTTP_IMAGE_OFF;

        } else {
            conf->filter = prev->filter;
            conf->width = prev->width;
            conf->height = prev->height;
            conf->angle = prev->angle;
            conf->wcv = prev->wcv;
            conf->hcv = prev->hcv;
            conf->acv = prev->acv;
        }
    }

    if (conf->jpeg_quality == NGX_CONF_UNSET_UINT) {

        /* 75 is libjpeg default quality */
        ngx_conf_merge_uint_value(conf->jpeg_quality, prev->jpeg_quality, 75);

        if (conf->jqcv == NULL) {
            conf->jqcv = prev->jqcv;
        }
    }

    if (conf->webp_quality == NGX_CONF_UNSET_UINT) {

        /* 80 is libwebp default quality */
        ngx_conf_merge_uint_value(conf->webp_quality, prev->webp_quality, 80);

        if (conf->wqcv == NULL) {
            conf->wqcv = prev->wqcv;
        }
    }

    if (conf->sharpen == NGX_CONF_UNSET_UINT) {
        ngx_conf_merge_uint_value(conf->sharpen, prev->sharpen, 0);

        if (conf->shcv == NULL) {
            conf->shcv = prev->shcv;
        }
    }

#if (T_NGX_HTTP_IMAGE_FILTER)
    if (conf->angle == NGX_CONF_UNSET_UINT) {
        ngx_conf_merge_uint_value(conf->angle, prev->angle, 0);

        if (conf->acv == NULL) {
            conf->acv = prev->acv;
        }
    }
#endif

    ngx_conf_merge_value(conf->transparency, prev->transparency, 1);

    ngx_conf_merge_value(conf->interlace, prev->interlace, 0);

    ngx_conf_merge_size_value(conf->buffer_size, prev->buffer_size,
                              1 * 1024 * 1024);

#if (T_NGX_HTTP_IMAGE_FILTER)
    if (conf->offset_x == NGX_CONF_UNSET_UINT) {
        ngx_conf_merge_uint_value(conf->offset_x, prev->offset_x,
                                  NGX_HTTP_IMAGE_OFFSET_CENTER);

        if (conf->oxcv == NULL) {
            conf->oxcv = prev->oxcv;
        }
    }

    if (conf->offset_y == NGX_CONF_UNSET_UINT) {
        ngx_conf_merge_uint_value(conf->offset_y, prev->offset_y,
                                  NGX_HTTP_IMAGE_OFFSET_CENTER);

        if (conf->oycv == NULL) {
            conf->oycv = prev->oycv;
        }
    }
#endif

    return NGX_CONF_OK;
}