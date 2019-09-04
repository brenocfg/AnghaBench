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
typedef  int /*<<< orphan*/  ngx_conf_t ;

/* Variables and functions */
 char* NGX_CONF_OK ; 

__attribute__((used)) static char *
ngx_http_gzip_hash(ngx_conf_t *cf, void *post, void *data)
{
    size_t *np = data;

    size_t  memlevel, hsize;

    memlevel = 9;

    for (hsize = 128 * 1024; hsize > 256; hsize >>= 1) {

        if (hsize == *np) {
            *np = memlevel;

            return NGX_CONF_OK;
        }

        memlevel--;
    }

    return "must be 512, 1k, 2k, 4k, 8k, 16k, 32k, 64k, or 128k";
}