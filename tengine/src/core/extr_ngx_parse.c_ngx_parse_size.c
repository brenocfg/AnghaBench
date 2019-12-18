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
typedef  int u_char ;
typedef  int ssize_t ;
struct TYPE_3__ {size_t len; int* data; } ;
typedef  TYPE_1__ ngx_str_t ;

/* Variables and functions */
 int NGX_ERROR ; 
 int NGX_MAX_SIZE_T_VALUE ; 
 int ngx_atosz (int*,size_t) ; 

ssize_t
ngx_parse_size(ngx_str_t *line)
{
    u_char   unit;
    size_t   len;
    ssize_t  size, scale, max;

    len = line->len;

    if (len == 0) {
        return NGX_ERROR;
    }

    unit = line->data[len - 1];

    switch (unit) {
    case 'K':
    case 'k':
        len--;
        max = NGX_MAX_SIZE_T_VALUE / 1024;
        scale = 1024;
        break;

    case 'M':
    case 'm':
        len--;
        max = NGX_MAX_SIZE_T_VALUE / (1024 * 1024);
        scale = 1024 * 1024;
        break;

#if (T_NGX_HTTP_SYSGUARD)
    case 'G':
    case 'g':
        len--;
        max = NGX_MAX_SIZE_T_VALUE / (1024 * 1024 * 1024);
        scale = 1024 * 1024 * 1024;
        break;
#endif

    default:
        max = NGX_MAX_SIZE_T_VALUE;
        scale = 1;
    }

    size = ngx_atosz(line->data, len);
    if (size == NGX_ERROR || size > max) {
        return NGX_ERROR;
    }

    size *= scale;

    return size;
}