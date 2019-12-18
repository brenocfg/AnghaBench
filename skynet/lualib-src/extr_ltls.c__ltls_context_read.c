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
typedef  int /*<<< orphan*/  outbuff ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  luaL_Buffer ;

/* Variables and functions */
 int SSL_ERROR_WANT_READ ; 
 int SSL_ERROR_WANT_WRITE ; 
 int SSL_get_error (int /*<<< orphan*/ ,int) ; 
 int SSL_read (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  _bio_write (int /*<<< orphan*/ *,struct tls_context*,char const*,size_t) ; 
 struct tls_context* _check_context (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_addlstring (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  luaL_buffinit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  luaL_pushresult (int /*<<< orphan*/ *) ; 
 char* lua_tolstring (int /*<<< orphan*/ *,int,size_t*) ; 

__attribute__((used)) static int
_ltls_context_read(lua_State* L) {
    struct tls_context* tls_p = _check_context(L, 1);
    size_t slen = 0;
    const char* encrypted_data = lua_tolstring(L, 2, &slen);

    // write encrypted data
    if(slen>0 && encrypted_data) {
        _bio_write(L, tls_p, encrypted_data, slen);
    }

    char outbuff[4096];
    int read = 0;
    luaL_Buffer b;
    luaL_buffinit(L, &b);

    do {
        read = SSL_read(tls_p->ssl, outbuff, sizeof(outbuff));
        if(read <= 0) {
            int err = SSL_get_error(tls_p->ssl, read);
            if(err == SSL_ERROR_WANT_READ || err == SSL_ERROR_WANT_WRITE) {
                break;
            }
            luaL_error(L, "SSL_read error:%d", err);
        }else if(read <= sizeof(outbuff)) {
            luaL_addlstring(&b, outbuff, read);
        }else {
            luaL_error(L, "invalid SSL_read:%d", read);
        }
    }while(true);
    luaL_pushresult(&b);
    return 1;
}