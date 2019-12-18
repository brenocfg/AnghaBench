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
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  input_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  Actors ; 
 int /*<<< orphan*/  Album ; 
 int /*<<< orphan*/  ArtURL ; 
 int /*<<< orphan*/  Artist ; 
 int /*<<< orphan*/  Copyright ; 
 int /*<<< orphan*/  Date ; 
 int /*<<< orphan*/  Description ; 
 int /*<<< orphan*/  Director ; 
 int /*<<< orphan*/  EncodedBy ; 
 int /*<<< orphan*/  Episode ; 
 int /*<<< orphan*/  Genre ; 
 int /*<<< orphan*/  Language ; 
 int /*<<< orphan*/  NowPlaying ; 
 int /*<<< orphan*/  Publisher ; 
 int /*<<< orphan*/  Rating ; 
 int /*<<< orphan*/  Season ; 
 int /*<<< orphan*/  Setting ; 
 int /*<<< orphan*/  ShowName ; 
 int /*<<< orphan*/  TRY_META (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Title ; 
 int /*<<< orphan*/  TrackID ; 
 int /*<<< orphan*/  TrackNum ; 
 int /*<<< orphan*/  URL ; 

void vlclua_read_meta_data( vlc_object_t *p_this, lua_State *L,
                            input_item_t *p_input )
{
#define TRY_META( a, b )                                        \
    lua_getfield( L, -1, a );                                   \
    if( lua_isstring( L, -1 ) &&                                \
        strcmp( lua_tostring( L, -1 ), "" ) )                   \
    {                                                           \
        char *psz_value = strdup( lua_tostring( L, -1 ) );      \
        EnsureUTF8( psz_value );                                \
        msg_Dbg( p_this, #b ": %s", psz_value );                \
        input_item_Set ## b ( p_input, psz_value );             \
        free( psz_value );                                      \
    }                                                           \
    lua_pop( L, 1 ); /* pop a */
    TRY_META( "title", Title );
    TRY_META( "artist", Artist );
    TRY_META( "genre", Genre );
    TRY_META( "copyright", Copyright );
    TRY_META( "album", Album );
    TRY_META( "tracknum", TrackNum );
    TRY_META( "description", Description );
    TRY_META( "rating", Rating );
    TRY_META( "date", Date );
    TRY_META( "setting", Setting );
    TRY_META( "url", URL );
    TRY_META( "language",  Language );
    TRY_META( "nowplaying", NowPlaying );
    TRY_META( "publisher",  Publisher );
    TRY_META( "encodedby",  EncodedBy );
    TRY_META( "arturl",     ArtURL );
    TRY_META( "trackid",    TrackID );
    TRY_META( "director",   Director );
    TRY_META( "season",     Season );
    TRY_META( "episode",    Episode );
    TRY_META( "show_name",  ShowName );
    TRY_META( "actors",     Actors );
}