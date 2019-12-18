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
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 char* vlc_stream_ReadLine (int /*<<< orphan*/ ) ; 
 scalar_t__ vlclua_get_this (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_demux_readline( lua_State *L )
{
    stream_t *s = (stream_t *)vlclua_get_this(L);
    char *line = vlc_stream_ReadLine(s->s);

    if (line != NULL)
    {
        lua_pushstring(L, line);
        free(line);
    }
    else
        lua_pushnil( L );

    return 1;
}