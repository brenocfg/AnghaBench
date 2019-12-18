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
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  stream_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/ * vlc_stream_MemoryNew (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * vlclua_get_this (int /*<<< orphan*/ *) ; 
 int vlclua_stream_new_inner (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_memory_stream_new( lua_State *L )
{
    vlc_object_t * p_this = vlclua_get_this( L );
    /* FIXME: duplicating the whole buffer is suboptimal. Keeping a reference to the string so that it doesn't get garbage collected would be better */
    char * psz_content = strdup( luaL_checkstring( L, 1 ) );
    stream_t *p_stream = vlc_stream_MemoryNew( p_this, (uint8_t *)psz_content, strlen( psz_content ), false );
    return vlclua_stream_new_inner( L, p_stream );
}