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
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  ngx_http_lua_ngx_crc32_long ; 
 int /*<<< orphan*/  ngx_http_lua_ngx_crc32_short ; 
 int /*<<< orphan*/  ngx_http_lua_ngx_decode_args ; 
 int /*<<< orphan*/  ngx_http_lua_ngx_decode_base64 ; 
 int /*<<< orphan*/  ngx_http_lua_ngx_encode_args ; 
 int /*<<< orphan*/  ngx_http_lua_ngx_encode_base64 ; 
 int /*<<< orphan*/  ngx_http_lua_ngx_escape_uri ; 
 int /*<<< orphan*/  ngx_http_lua_ngx_hmac_sha1 ; 
 int /*<<< orphan*/  ngx_http_lua_ngx_md5 ; 
 int /*<<< orphan*/  ngx_http_lua_ngx_md5_bin ; 
 int /*<<< orphan*/  ngx_http_lua_ngx_quote_sql_str ; 
 int /*<<< orphan*/  ngx_http_lua_ngx_sha1_bin ; 
 int /*<<< orphan*/  ngx_http_lua_ngx_unescape_uri ; 

void
ngx_http_lua_inject_string_api(lua_State *L)
{
    lua_pushcfunction(L, ngx_http_lua_ngx_escape_uri);
    lua_setfield(L, -2, "escape_uri");

    lua_pushcfunction(L, ngx_http_lua_ngx_unescape_uri);
    lua_setfield(L, -2, "unescape_uri");

    lua_pushcfunction(L, ngx_http_lua_ngx_encode_args);
    lua_setfield(L, -2, "encode_args");

    lua_pushcfunction(L, ngx_http_lua_ngx_decode_args);
    lua_setfield(L, -2, "decode_args");

    lua_pushcfunction(L, ngx_http_lua_ngx_quote_sql_str);
    lua_setfield(L, -2, "quote_sql_str");

    lua_pushcfunction(L, ngx_http_lua_ngx_decode_base64);
    lua_setfield(L, -2, "decode_base64");

    lua_pushcfunction(L, ngx_http_lua_ngx_encode_base64);
    lua_setfield(L, -2, "encode_base64");

    lua_pushcfunction(L, ngx_http_lua_ngx_md5_bin);
    lua_setfield(L, -2, "md5_bin");

    lua_pushcfunction(L, ngx_http_lua_ngx_md5);
    lua_setfield(L, -2, "md5");

#if (NGX_HAVE_SHA1)
    lua_pushcfunction(L, ngx_http_lua_ngx_sha1_bin);
    lua_setfield(L, -2, "sha1_bin");
#endif

    lua_pushcfunction(L, ngx_http_lua_ngx_crc32_short);
    lua_setfield(L, -2, "crc32_short");

    lua_pushcfunction(L, ngx_http_lua_ngx_crc32_long);
    lua_setfield(L, -2, "crc32_long");

#if (NGX_OPENSSL)
    lua_pushcfunction(L, ngx_http_lua_ngx_hmac_sha1);
    lua_setfield(L, -2, "hmac_sha1");
#endif
}