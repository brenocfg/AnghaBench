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
 int NGX_HTTP_ACCEPTED ; 
 int NGX_HTTP_BAD_GATEWAY ; 
 int NGX_HTTP_BAD_REQUEST ; 
 int NGX_HTTP_CLOSE ; 
 int NGX_HTTP_CONFLICT ; 
 int NGX_HTTP_CONTINUE ; 
 int NGX_HTTP_COPY ; 
 int NGX_HTTP_CREATED ; 
 int NGX_HTTP_DELETE ; 
 int NGX_HTTP_FORBIDDEN ; 
 int NGX_HTTP_GATEWAY_TIME_OUT ; 
 int NGX_HTTP_GET ; 
 int NGX_HTTP_HEAD ; 
 int NGX_HTTP_INSUFFICIENT_STORAGE ; 
 int NGX_HTTP_INTERNAL_SERVER_ERROR ; 
 int NGX_HTTP_LOCK ; 
 int NGX_HTTP_MKCOL ; 
 int NGX_HTTP_MOVE ; 
 int NGX_HTTP_MOVED_PERMANENTLY ; 
 int NGX_HTTP_MOVED_TEMPORARILY ; 
 int NGX_HTTP_NOT_ALLOWED ; 
 int NGX_HTTP_NOT_FOUND ; 
 int NGX_HTTP_NOT_IMPLEMENTED ; 
 int NGX_HTTP_NOT_MODIFIED ; 
 int NGX_HTTP_NO_CONTENT ; 
 int NGX_HTTP_OK ; 
 int NGX_HTTP_OPTIONS ; 
 int NGX_HTTP_PARTIAL_CONTENT ; 
 int NGX_HTTP_PATCH ; 
 int NGX_HTTP_PERMANENT_REDIRECT ; 
 int NGX_HTTP_POST ; 
 int NGX_HTTP_PROPFIND ; 
 int NGX_HTTP_PROPPATCH ; 
 int NGX_HTTP_PUT ; 
 int NGX_HTTP_REQUEST_TIME_OUT ; 
 int NGX_HTTP_SEE_OTHER ; 
 int NGX_HTTP_SERVICE_UNAVAILABLE ; 
 int NGX_HTTP_SPECIAL_RESPONSE ; 
 int NGX_HTTP_SWITCHING_PROTOCOLS ; 
 int NGX_HTTP_TEMPORARY_REDIRECT ; 
 int NGX_HTTP_TRACE ; 
 int NGX_HTTP_UNAUTHORIZED ; 
 int NGX_HTTP_UNLOCK ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 

void
ngx_http_lua_inject_http_consts(lua_State *L)
{
    /* {{{ HTTP status constants */
    lua_pushinteger(L, NGX_HTTP_GET);
    lua_setfield(L, -2, "HTTP_GET");

    lua_pushinteger(L, NGX_HTTP_POST);
    lua_setfield(L, -2, "HTTP_POST");

    lua_pushinteger(L, NGX_HTTP_PUT);
    lua_setfield(L, -2, "HTTP_PUT");

    lua_pushinteger(L, NGX_HTTP_HEAD);
    lua_setfield(L, -2, "HTTP_HEAD");

    lua_pushinteger(L, NGX_HTTP_DELETE);
    lua_setfield(L, -2, "HTTP_DELETE");

    lua_pushinteger(L, NGX_HTTP_OPTIONS);
    lua_setfield(L, -2, "HTTP_OPTIONS");

    lua_pushinteger(L, NGX_HTTP_MKCOL);
    lua_setfield(L, -2, "HTTP_MKCOL");

    lua_pushinteger(L, NGX_HTTP_COPY);
    lua_setfield(L, -2, "HTTP_COPY");

    lua_pushinteger(L, NGX_HTTP_MOVE);
    lua_setfield(L, -2, "HTTP_MOVE");

    lua_pushinteger(L, NGX_HTTP_PROPFIND);
    lua_setfield(L, -2, "HTTP_PROPFIND");

    lua_pushinteger(L, NGX_HTTP_PROPPATCH);
    lua_setfield(L, -2, "HTTP_PROPPATCH");

    lua_pushinteger(L, NGX_HTTP_LOCK);
    lua_setfield(L, -2, "HTTP_LOCK");

    lua_pushinteger(L, NGX_HTTP_UNLOCK);
    lua_setfield(L, -2, "HTTP_UNLOCK");

    lua_pushinteger(L, NGX_HTTP_PATCH);
    lua_setfield(L, -2, "HTTP_PATCH");

    lua_pushinteger(L, NGX_HTTP_TRACE);
    lua_setfield(L, -2, "HTTP_TRACE");
    /* }}} */

    lua_pushinteger(L, NGX_HTTP_CONTINUE);
    lua_setfield(L, -2, "HTTP_CONTINUE");

    lua_pushinteger(L, NGX_HTTP_SWITCHING_PROTOCOLS);
    lua_setfield(L, -2, "HTTP_SWITCHING_PROTOCOLS");

    lua_pushinteger(L, NGX_HTTP_OK);
    lua_setfield(L, -2, "HTTP_OK");

    lua_pushinteger(L, NGX_HTTP_CREATED);
    lua_setfield(L, -2, "HTTP_CREATED");

    lua_pushinteger(L, NGX_HTTP_ACCEPTED);
    lua_setfield(L, -2, "HTTP_ACCEPTED");

    lua_pushinteger(L, NGX_HTTP_NO_CONTENT);
    lua_setfield(L, -2, "HTTP_NO_CONTENT");

    lua_pushinteger(L, NGX_HTTP_PARTIAL_CONTENT);
    lua_setfield(L, -2, "HTTP_PARTIAL_CONTENT");

    lua_pushinteger(L, NGX_HTTP_SPECIAL_RESPONSE);
    lua_setfield(L, -2, "HTTP_SPECIAL_RESPONSE");

    lua_pushinteger(L, NGX_HTTP_MOVED_PERMANENTLY);
    lua_setfield(L, -2, "HTTP_MOVED_PERMANENTLY");

    lua_pushinteger(L, NGX_HTTP_MOVED_TEMPORARILY);
    lua_setfield(L, -2, "HTTP_MOVED_TEMPORARILY");

#if defined(nginx_version) && nginx_version >= 8042
    lua_pushinteger(L, NGX_HTTP_SEE_OTHER);
    lua_setfield(L, -2, "HTTP_SEE_OTHER");
#endif

    lua_pushinteger(L, NGX_HTTP_PERMANENT_REDIRECT);
    lua_setfield(L, -2, "HTTP_PERMANENT_REDIRECT");

    lua_pushinteger(L, NGX_HTTP_NOT_MODIFIED);
    lua_setfield(L, -2, "HTTP_NOT_MODIFIED");

    lua_pushinteger(L, NGX_HTTP_TEMPORARY_REDIRECT);
    lua_setfield(L, -2, "HTTP_TEMPORARY_REDIRECT");

    lua_pushinteger(L, NGX_HTTP_BAD_REQUEST);
    lua_setfield(L, -2, "HTTP_BAD_REQUEST");

    lua_pushinteger(L, NGX_HTTP_UNAUTHORIZED);
    lua_setfield(L, -2, "HTTP_UNAUTHORIZED");

    lua_pushinteger(L, 402);
    lua_setfield(L, -2, "HTTP_PAYMENT_REQUIRED");

    lua_pushinteger(L, NGX_HTTP_FORBIDDEN);
    lua_setfield(L, -2, "HTTP_FORBIDDEN");

    lua_pushinteger(L, NGX_HTTP_NOT_FOUND);
    lua_setfield(L, -2, "HTTP_NOT_FOUND");

    lua_pushinteger(L, NGX_HTTP_NOT_ALLOWED);
    lua_setfield(L, -2, "HTTP_NOT_ALLOWED");

    lua_pushinteger(L, 406);
    lua_setfield(L, -2, "HTTP_NOT_ACCEPTABLE");

    lua_pushinteger(L, NGX_HTTP_REQUEST_TIME_OUT);
    lua_setfield(L, -2, "HTTP_REQUEST_TIMEOUT");

    lua_pushinteger(L, NGX_HTTP_CONFLICT);
    lua_setfield(L, -2, "HTTP_CONFLICT");

    lua_pushinteger(L, 410);
    lua_setfield(L, -2, "HTTP_GONE");

    lua_pushinteger(L, 426);
    lua_setfield(L, -2, "HTTP_UPGRADE_REQUIRED");

    lua_pushinteger(L, 429);
    lua_setfield(L, -2, "HTTP_TOO_MANY_REQUESTS");

    lua_pushinteger(L, 451);
    lua_setfield(L, -2, "HTTP_ILLEGAL");

    lua_pushinteger(L, NGX_HTTP_CLOSE);
    lua_setfield(L, -2, "HTTP_CLOSE");

    lua_pushinteger(L, NGX_HTTP_INTERNAL_SERVER_ERROR);
    lua_setfield(L, -2, "HTTP_INTERNAL_SERVER_ERROR");

    lua_pushinteger(L, NGX_HTTP_NOT_IMPLEMENTED);
    lua_setfield(L, -2, "HTTP_METHOD_NOT_IMPLEMENTED");

    lua_pushinteger(L, NGX_HTTP_BAD_GATEWAY);
    lua_setfield(L, -2, "HTTP_BAD_GATEWAY");

    lua_pushinteger(L, NGX_HTTP_SERVICE_UNAVAILABLE);
    lua_setfield(L, -2, "HTTP_SERVICE_UNAVAILABLE");

    lua_pushinteger(L, NGX_HTTP_GATEWAY_TIME_OUT);
    lua_setfield(L, -2, "HTTP_GATEWAY_TIMEOUT");

    lua_pushinteger(L, 505);
    lua_setfield(L, -2, "HTTP_VERSION_NOT_SUPPORTED");

    lua_pushinteger(L, NGX_HTTP_INSUFFICIENT_STORAGE);
    lua_setfield(L, -2, "HTTP_INSUFFICIENT_STORAGE");

    /* }}} */
}