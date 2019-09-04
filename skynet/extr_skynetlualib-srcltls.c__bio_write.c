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
struct tls_context {int /*<<< orphan*/  in_bio; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int BIO_write (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
_bio_write(lua_State* L, struct tls_context* tls_p, const char* s, size_t len) {
    char* p = (char*)s;
    size_t sz = len;
    while(sz > 0) {
        int written = BIO_write(tls_p->in_bio, p, sz);
        if(written > sz) {
            luaL_error(L, "invalid BIO_write");
        }else if(written > 0) {
            p += written;
            sz -= written;
        }else if (written == -2) {
            luaL_error(L, "BIO_write not implemented in the specific BIO type");
        }
    }
}