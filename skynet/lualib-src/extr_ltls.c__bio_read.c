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
struct tls_context {int /*<<< orphan*/  out_bio; } ;
typedef  int /*<<< orphan*/  outbuff ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  luaL_Buffer ;

/* Variables and functions */
 int BIO_ctrl_pending (int /*<<< orphan*/ ) ; 
 int BIO_read (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  luaL_addlstring (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  luaL_buffinit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  luaL_pushresult (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
_bio_read(lua_State* L, struct tls_context* tls_p) {
    char outbuff[4096];
    int all_read = 0;
    int read = 0;
    int pending = BIO_ctrl_pending(tls_p->out_bio);
    if(pending >0) {
        luaL_Buffer b;
        luaL_buffinit(L, &b);
        while(pending > 0) {
            read = BIO_read(tls_p->out_bio, outbuff, sizeof(outbuff));
            // printf("BIO_read read:%d pending:%d\n", read, pending);
            if(read <= 0) {
                luaL_error(L, "BIO_read error:%d", read);
            }else if(read <= sizeof(outbuff)) {
                all_read += read;
                luaL_addlstring(&b, (const char*)outbuff, read);
            }else {
                luaL_error(L, "invalid BIO_read:%d", read);
            }
            pending = BIO_ctrl_pending(tls_p->out_bio);
        }
        if(all_read>0) {
            luaL_pushresult(&b);
        }
    }
    return all_read;
}