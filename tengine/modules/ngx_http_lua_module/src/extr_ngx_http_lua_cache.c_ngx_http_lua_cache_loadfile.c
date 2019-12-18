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
typedef  char u_char ;
typedef  int /*<<< orphan*/  ngx_log_t ;
typedef  int ngx_int_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
#define  LUA_ERRFILE 129 
#define  LUA_ERRMEM 128 
 int NGX_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_LUA_FILE_KEY_LEN ; 
 int /*<<< orphan*/  NGX_HTTP_LUA_FILE_TAG ; 
 int /*<<< orphan*/  NGX_HTTP_LUA_FILE_TAG_LEN ; 
 int NGX_HTTP_NOT_FOUND ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int NGX_OK ; 
 int /*<<< orphan*/  dd (char*,...) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_isstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 char* ngx_copy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ngx_http_lua_cache_load_code (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int ngx_http_lua_cache_store_code (int /*<<< orphan*/ *,char*) ; 
 int ngx_http_lua_clfactory_loadfile (int /*<<< orphan*/ *,char*) ; 
 char* ngx_http_lua_digest_hex (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*,char const*) ; 
 int /*<<< orphan*/  ngx_strlen (char const*) ; 

ngx_int_t
ngx_http_lua_cache_loadfile(ngx_log_t *log, lua_State *L,
    const u_char *script, const u_char *cache_key)
{
    int              n;
    ngx_int_t        rc, errcode = NGX_ERROR;
    u_char          *p;
    u_char           buf[NGX_HTTP_LUA_FILE_KEY_LEN + 1];
    const char      *err = NULL;

    n = lua_gettop(L);

    /*  calculate digest of script file path */
    if (cache_key == NULL) {
        dd("CACHE file key not pre-calculated...calculating");
        p = ngx_copy(buf, NGX_HTTP_LUA_FILE_TAG, NGX_HTTP_LUA_FILE_TAG_LEN);

        p = ngx_http_lua_digest_hex(p, script, ngx_strlen(script));

        *p = '\0';
        cache_key = buf;

    } else {
        dd("CACHE file key already pre-calculated");
    }

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, log, 0,
                   "looking up Lua code cache with key '%s'", cache_key);

    rc = ngx_http_lua_cache_load_code(log, L, (char *) cache_key);
    if (rc == NGX_OK) {
        /*  code chunk loaded from cache, sp++ */
        dd("Code cache hit! cache key='%s', stack top=%d, file path='%s'",
           cache_key, lua_gettop(L), script);
        return NGX_OK;
    }

    if (rc == NGX_ERROR) {
        return NGX_ERROR;
    }

    /* rc == NGX_DECLINED */

    dd("Code cache missed! cache key='%s', stack top=%d, file path='%s'",
       cache_key, lua_gettop(L), script);

    /*  load closure factory of script file to the top of lua stack, sp++ */
    rc = ngx_http_lua_clfactory_loadfile(L, (char *) script);

    dd("loadfile returns %d (%d)", (int) rc, LUA_ERRFILE);

    if (rc != 0) {
        /*  Oops! error occurred when loading Lua script */
        switch (rc) {
        case LUA_ERRMEM:
            err = "memory allocation error";
            break;

        case LUA_ERRFILE:
            errcode = NGX_HTTP_NOT_FOUND;
            /* fall through */

        default:
            if (lua_isstring(L, -1)) {
                err = lua_tostring(L, -1);

            } else {
                err = "unknown error";
            }
        }

        goto error;
    }

    /*  store closure factory and gen new closure at the top of lua stack
     *  to code cache */
    rc = ngx_http_lua_cache_store_code(L, (char *) cache_key);
    if (rc != NGX_OK) {
        err = "fail to generate new closure from the closure factory";
        goto error;
    }

    return NGX_OK;

error:

    ngx_log_error(NGX_LOG_ERR, log, 0,
                  "failed to load external Lua file \"%s\": %s", script, err);

    lua_settop(L, n);
    return errcode;
}