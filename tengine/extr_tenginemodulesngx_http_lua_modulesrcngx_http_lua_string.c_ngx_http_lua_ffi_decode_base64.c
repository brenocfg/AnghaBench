#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_4__ {size_t len; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;

/* Variables and functions */
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_decode_base64 (TYPE_1__*,TYPE_1__*) ; 

int
ngx_http_lua_ffi_decode_base64(const u_char *src, size_t slen, u_char *dst,
    size_t *dlen)
{
    ngx_int_t      rc;
    ngx_str_t      in, out;

    in.data = (u_char *) src;
    in.len = slen;

    out.data = dst;

    rc = ngx_decode_base64(&out, &in);

    *dlen = out.len;

    return rc == NGX_OK;
}