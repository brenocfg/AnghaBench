#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  s; } ;
typedef  TYPE_1__ stream_t ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  vlc_stream_Read (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ vlclua_get_this (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_demux_read( lua_State *L )
{
    stream_t *s = (stream_t *)vlclua_get_this(L);
    int n = luaL_checkinteger( L, 1 );
    char *buf = malloc(n);

    if (buf != NULL)
    {
        ssize_t val = vlc_stream_Read(s->s, buf, n);
        if (val > 0)
            lua_pushlstring(L, buf, val);
        else
            lua_pushnil( L );
        free(buf);
    }
    else
        lua_pushnil( L );

    return 1;
}