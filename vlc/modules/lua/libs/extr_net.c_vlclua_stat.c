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
struct stat {int /*<<< orphan*/  st_ctime; int /*<<< orphan*/  st_mtime; int /*<<< orphan*/  st_atime; int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_gid; int /*<<< orphan*/  st_uid; int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISFIFO (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISSOCK (int /*<<< orphan*/ ) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushliteral (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 scalar_t__ vlc_stat (char const*,struct stat*) ; 

__attribute__((used)) static int vlclua_stat( lua_State *L )
{
    const char *psz_path = luaL_checkstring( L, 1 );
    struct stat s;
    if( vlc_stat( psz_path, &s ) )
        return 0;
        //return luaL_error( L, "Couldn't stat %s.", psz_path );
    lua_newtable( L );
    if( S_ISREG( s.st_mode ) )
        lua_pushliteral( L, "file" );
    else if( S_ISDIR( s.st_mode ) )
        lua_pushliteral( L, "dir" );
#ifdef S_ISCHR
    else if( S_ISCHR( s.st_mode ) )
        lua_pushliteral( L, "character device" );
#endif
#ifdef S_ISBLK
    else if( S_ISBLK( s.st_mode ) )
        lua_pushliteral( L, "block device" );
#endif
#ifdef S_ISFIFO
    else if( S_ISFIFO( s.st_mode ) )
        lua_pushliteral( L, "fifo" );
#endif
#ifdef S_ISLNK
    else if( S_ISLNK( s.st_mode ) )
        lua_pushliteral( L, "symbolic link" );
#endif
#ifdef S_ISSOCK
    else if( S_ISSOCK( s.st_mode ) )
        lua_pushliteral( L, "socket" );
#endif
    else
        lua_pushliteral( L, "unknown" );
    lua_setfield( L, -2, "type" );
    lua_pushinteger( L, s.st_mode );
    lua_setfield( L, -2, "mode" );
    lua_pushinteger( L, s.st_uid );
    lua_setfield( L, -2, "uid" );
    lua_pushinteger( L, s.st_gid );
    lua_setfield( L, -2, "gid" );
    lua_pushinteger( L, s.st_size );
    lua_setfield( L, -2, "size" );
    lua_pushinteger( L, s.st_atime );
    lua_setfield( L, -2, "access_time" );
    lua_pushinteger( L, s.st_mtime );
    lua_setfield( L, -2, "modification_time" );
    lua_pushinteger( L, s.st_ctime );
    lua_setfield( L, -2, "creation_time" );
    return 1;
}