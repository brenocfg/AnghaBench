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
typedef  int /*<<< orphan*/  ngx_uint_t ;
struct TYPE_3__ {int len; char* data; } ;
typedef  TYPE_1__ ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_IMAGE_OFFSET_BOTTOM ; 
 int /*<<< orphan*/  NGX_HTTP_IMAGE_OFFSET_LEFT ; 
 int /*<<< orphan*/  NGX_HTTP_IMAGE_OFFSET_RIGHT ; 
 int /*<<< orphan*/  NGX_HTTP_IMAGE_OFFSET_TOP ; 
 scalar_t__ ngx_atoi (char*,int) ; 
 scalar_t__ ngx_strncmp (char*,char*,int) ; 

__attribute__((used)) static ngx_uint_t
ngx_http_image_filter_value(ngx_str_t *value)
{
    ngx_int_t  n;

    if (value->len == 1 && value->data[0] == '-') {
        return (ngx_uint_t) -1;
    }

    n = ngx_atoi(value->data, value->len);

    if (n > 0) {
        return (ngx_uint_t) n;
    }

#if (T_NGX_HTTP_IMAGE_FILTER)
    if (n == NGX_ERROR) {
        if (value->len == sizeof("left") - 1
            && ngx_strncmp(value->data, "left", value->len) == 0)
        {
            return NGX_HTTP_IMAGE_OFFSET_LEFT;
        } else if (value->len == sizeof("right") - 1
                   && ngx_strncmp(value->data, "right", sizeof("right") - 1) == 0)
        {
            return NGX_HTTP_IMAGE_OFFSET_RIGHT;
        } else if (value->len == sizeof("top") - 1
                   && ngx_strncmp(value->data, "top", sizeof("top") - 1) == 0)
        {
            return NGX_HTTP_IMAGE_OFFSET_TOP;
        } else if (value->len == sizeof("bottom") - 1
                   && ngx_strncmp(value->data, "bottom", sizeof("bottom") - 1) == 0)
        {
            return NGX_HTTP_IMAGE_OFFSET_BOTTOM;
        }
    }
#endif

    return 0;
}