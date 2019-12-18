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

/* Variables and functions */
 int Start_LuaIntf (int /*<<< orphan*/ *,char*) ; 
 int VLC_EGENERIC ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msg_Info (int /*<<< orphan*/ *,char*) ; 
 char* var_CreateGetNonEmptyString (int /*<<< orphan*/ *,char*) ; 

int Open_LuaTelnet( vlc_object_t *p_this )
{
    char *pw = var_CreateGetNonEmptyString( p_this, "telnet-password" );
    if( pw == NULL )
    {
        msg_Err( p_this, "password not configured" );
        msg_Info( p_this, "Please specify the password in the preferences." );
        return VLC_EGENERIC;
    }
    free( pw );
    return Start_LuaIntf( p_this, "telnet" );
}