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
typedef  int /*<<< orphan*/  libvlc_int_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_OBJECT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_object_instance (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlclua_get_this (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlclua_push_vlc_object (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_get_libvlc( lua_State *L )
{
    libvlc_int_t *p_libvlc = vlc_object_instance(vlclua_get_this( L ));
    vlclua_push_vlc_object(L, VLC_OBJECT(p_libvlc), NULL);
    return 1;
}