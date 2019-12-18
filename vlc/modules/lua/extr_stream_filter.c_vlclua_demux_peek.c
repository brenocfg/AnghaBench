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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  s; } ;
typedef  TYPE_1__ stream_t ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_stream_Peek (int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int) ; 
 scalar_t__ vlclua_get_this (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_demux_peek( lua_State *L )
{
    stream_t *s = (stream_t *)vlclua_get_this(L);
    int n = luaL_checkinteger( L, 1 );
    const uint8_t *p_peek;

    ssize_t val = vlc_stream_Peek(s->s, &p_peek, n);
    if (val > 0)
        lua_pushlstring(L, (const char *)p_peek, val);
    else
        lua_pushnil( L );
    return 1;
}