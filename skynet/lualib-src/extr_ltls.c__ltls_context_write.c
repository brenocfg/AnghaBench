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
struct tls_context {int /*<<< orphan*/  ssl; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int SSL_get_error (int /*<<< orphan*/ ,int) ; 
 int SSL_write (int /*<<< orphan*/ ,char*,size_t) ; 
 int _bio_read (int /*<<< orphan*/ *,struct tls_context*) ; 
 struct tls_context* _check_context (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ lua_tolstring (int /*<<< orphan*/ *,int,size_t*) ; 

__attribute__((used)) static int
_ltls_context_write(lua_State* L) {
    struct tls_context* tls_p = _check_context(L, 1);
    size_t slen = 0;
    char* unencrypted_data = (char*)lua_tolstring(L, 2, &slen);

    while(slen > 0) {
        int written = SSL_write(tls_p->ssl, unencrypted_data,  slen);
        if(written <= 0) {
            int err = SSL_get_error(tls_p->ssl, written);
            luaL_error(L, "SSL_write error:%d", err);
        }else if(written <= slen) {
            unencrypted_data += written;
            slen -= written;
        }else {
            luaL_error(L, "invalid SSL_write:%d", written);
        }
    }

    int all_read = _bio_read(L, tls_p);
    if(all_read <= 0) {
        lua_pushstring(L, "");
    }
    return 1;
}