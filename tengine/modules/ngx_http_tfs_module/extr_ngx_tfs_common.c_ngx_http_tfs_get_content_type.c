#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_AGAIN ; 
 int /*<<< orphan*/  NGX_OK ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ngx_str_set (int /*<<< orphan*/ *,char*) ; 

ngx_int_t
ngx_http_tfs_get_content_type(u_char *data, ngx_str_t *type)
{
    if (memcmp(data, "GIF", 3) == 0) {
        ngx_str_set(type, "image/gif");
        return NGX_OK;
    }

    if (memcmp(data, "\xff\xd8\xff", 3) == 0) {
        ngx_str_set(type, "image/jpeg");
        return NGX_OK;
    }

    if (memcmp(data, "\x89\x50\x4e\x47\x0d\x0a\x1a\x0a", 8) == 0) {
        ngx_str_set(type, "image/png");
        return NGX_OK;
    }

    if ((memcmp(data, "CWS", 3) == 0)
              ||(memcmp(data, "FWS", 3) == 0))
    {
        ngx_str_set(type, "application/x-shockwave-flash");
        return NGX_OK;
    }

    if ((memcmp(data, "BM", 2) == 0)
              ||(memcmp(data, "BA", 2) == 0)
              ||(memcmp(data, "CI", 2) == 0)
              ||(memcmp(data, "CP", 2) == 0)
              ||(memcmp(data, "IC", 2) == 0)
              ||(memcmp(data, "PI", 2) == 0))
    {
        ngx_str_set(type, "image/bmp");
        return NGX_OK;
    }

    if ((memcmp(data, "\115\115\000\052", 4) == 0)
            ||(memcmp(data, "\111\111\052\000", 4) == 0)
            ||(memcmp(data, "\115\115\000\053\000\010\000\000", 8) == 0)
            ||(memcmp(data, "\111\111\053\000\010\000\000\000", 8) == 0))
    {
        ngx_str_set(type, "image/tiff");
        return NGX_OK;
    }

    return NGX_AGAIN;
}