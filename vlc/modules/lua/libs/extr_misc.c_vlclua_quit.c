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

/* Variables and functions */
 int /*<<< orphan*/  libvlc_Quit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_object_instance (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlclua_get_this (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_quit( lua_State *L )
{
    vlc_object_t *p_this = vlclua_get_this( L );
    /* The rc.c code also stops the playlist ... not sure if this is needed
     * though. */
    libvlc_Quit( vlc_object_instance(p_this) );
    return 0;
}