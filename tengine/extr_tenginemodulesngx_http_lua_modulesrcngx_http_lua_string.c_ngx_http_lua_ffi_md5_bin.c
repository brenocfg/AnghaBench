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
typedef  int /*<<< orphan*/  ngx_md5_t ;

/* Variables and functions */
 int /*<<< orphan*/  ngx_md5_final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_md5_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_md5_update (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 

void
ngx_http_lua_ffi_md5_bin(const u_char *src, size_t len, u_char *dst)
{
    ngx_md5_t     md5;

    ngx_md5_init(&md5);
    ngx_md5_update(&md5, src, len);
    ngx_md5_final(dst, &md5);
}