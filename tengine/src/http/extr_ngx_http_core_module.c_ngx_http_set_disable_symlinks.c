#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  char u_char ;
struct TYPE_8__ {scalar_t__ len; char* data; } ;
typedef  TYPE_1__ ngx_str_t ;
struct TYPE_9__ {int disable_symlinks_from; int /*<<< orphan*/  disable_symlinks; } ;
typedef  TYPE_2__ ngx_open_file_info_t ;
typedef  scalar_t__ ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_http_request_t ;
struct TYPE_10__ {int /*<<< orphan*/ * disable_symlinks_from; int /*<<< orphan*/  disable_symlinks; } ;
typedef  TYPE_3__ ngx_http_core_loc_conf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_DISABLE_SYMLINKS_OFF ; 
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_http_complex_value (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ ngx_memcmp (char*,char*,scalar_t__) ; 

ngx_int_t
ngx_http_set_disable_symlinks(ngx_http_request_t *r,
    ngx_http_core_loc_conf_t *clcf, ngx_str_t *path, ngx_open_file_info_t *of)
{
#if (NGX_HAVE_OPENAT)
    u_char     *p;
    ngx_str_t   from;

    of->disable_symlinks = clcf->disable_symlinks;

    if (clcf->disable_symlinks_from == NULL) {
        return NGX_OK;
    }

    if (ngx_http_complex_value(r, clcf->disable_symlinks_from, &from)
        != NGX_OK)
    {
        return NGX_ERROR;
    }

    if (from.len == 0
        || from.len > path->len
        || ngx_memcmp(path->data, from.data, from.len) != 0)
    {
        return NGX_OK;
    }

    if (from.len == path->len) {
        of->disable_symlinks = NGX_DISABLE_SYMLINKS_OFF;
        return NGX_OK;
    }

    p = path->data + from.len;

    if (*p == '/') {
        of->disable_symlinks_from = from.len;
        return NGX_OK;
    }

    p--;

    if (*p == '/') {
        of->disable_symlinks_from = from.len - 1;
    }
#endif

    return NGX_OK;
}