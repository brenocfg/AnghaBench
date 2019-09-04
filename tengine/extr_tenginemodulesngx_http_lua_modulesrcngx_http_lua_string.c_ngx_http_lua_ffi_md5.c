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
typedef  int /*<<< orphan*/  md5_buf ;

/* Variables and functions */
 int MD5_DIGEST_LENGTH ; 
 int /*<<< orphan*/  ngx_hex_dump (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_md5_final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_md5_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_md5_update (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 

void
ngx_http_lua_ffi_md5(const u_char *src, size_t len, u_char *dst)
{
    ngx_md5_t           md5;
    u_char              md5_buf[MD5_DIGEST_LENGTH];

    ngx_md5_init(&md5);
    ngx_md5_update(&md5, src, len);
    ngx_md5_final(md5_buf, &md5);

    ngx_hex_dump(dst, md5_buf, sizeof(md5_buf));
}