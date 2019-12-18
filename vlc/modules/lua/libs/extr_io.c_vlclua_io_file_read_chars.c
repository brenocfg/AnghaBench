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
typedef  int /*<<< orphan*/  luaL_Buffer ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t LUAL_BUFFERSIZE ; 
 size_t fread (char*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_addsize (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  luaL_buffinit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* luaL_prepbuffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_pushresult (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_objlen (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int vlclua_io_file_read_chars( lua_State *L, size_t i_len, FILE* p_file )
{
    size_t i_toread = LUAL_BUFFERSIZE;
    size_t i_read;
    luaL_Buffer b;
    luaL_buffinit( L, &b );
    do {
        char *p = luaL_prepbuffer(&b);
        if (i_toread > i_len)
            i_toread = i_len;
        i_read = fread(p, sizeof(char), i_toread, p_file);
        luaL_addsize(&b, i_read);
        i_len -= i_read;
    } while (i_len > 0 && i_read == i_toread);
    luaL_pushresult(&b);
    return (i_len == 0 || lua_objlen(L, -1) > 0);
}