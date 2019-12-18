#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  httpd_file_t ;
struct TYPE_3__ {int /*<<< orphan*/  password; int /*<<< orphan*/ * L; } ;
typedef  TYPE_1__ httpd_file_sys_t ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _ (int /*<<< orphan*/ ) ; 
 scalar_t__ asprintf (char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_pcall (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  no_password_body ; 
 int /*<<< orphan*/  no_password_fmt ; 
 int /*<<< orphan*/  no_password_title ; 
 int strlen (char*) ; 
 int /*<<< orphan*/ * vlclua_get_this (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlclua_todata (int /*<<< orphan*/ *,int,int*) ; 

__attribute__((used)) static int vlclua_httpd_file_callback(
    httpd_file_sys_t *p_sys, httpd_file_t *p_file, uint8_t *psz_request,
    uint8_t **pp_data, int *pi_data )
{
    VLC_UNUSED(p_file);
    lua_State *L = p_sys->L;

    /* function data */
    lua_pushvalue( L, 1 );
    lua_pushvalue( L, 2 );
    /* function data function data */
    lua_pushstring( L, (const char *)psz_request );
    /* function data function data request */
    if( lua_pcall( L, 2, 1, 0 ) )
    {
        /* function data err */
        vlc_object_t *p_this = vlclua_get_this( L );
        const char *psz_err = lua_tostring( L, -1 );
        msg_Err( p_this, "Error while running the lua HTTPd file callback: %s",
                 psz_err );
        lua_settop( L, 2 );
        /* function data */
        return VLC_EGENERIC;
    }
    /* function data outdata */
    *pp_data = vlclua_todata( L, -1, pi_data );
    if (!p_sys->password)
    {
        free(*pp_data);
        if (asprintf((char**)pp_data, no_password_fmt,
                _(no_password_title), _(no_password_body)) < 0) {
            *pi_data = 0;
        } else {
            *pi_data = strlen((char*)*pp_data);
        }
    }
    lua_pop( L, 1 );
    /* function data */
    return VLC_SUCCESS;
}