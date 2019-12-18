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
typedef  int /*<<< orphan*/  xcb_key_symbols_t ;
typedef  int /*<<< orphan*/  xcb_connection_t ;

/* Variables and functions */
 unsigned int GetModifier (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int KEY_MODIFIER_ALT ; 
 unsigned int KEY_MODIFIER_CTRL ; 
 unsigned int KEY_MODIFIER_META ; 
 unsigned int KEY_MODIFIER_SHIFT ; 
 int /*<<< orphan*/  XK_Alt_L ; 
 int /*<<< orphan*/  XK_Alt_R ; 
 int /*<<< orphan*/  XK_Control_L ; 
 int /*<<< orphan*/  XK_Control_R ; 
 int /*<<< orphan*/  XK_Meta_L ; 
 int /*<<< orphan*/  XK_Meta_R ; 
 int /*<<< orphan*/  XK_Shift_L ; 
 int /*<<< orphan*/  XK_Shift_R ; 
 int /*<<< orphan*/  XK_Super_L ; 
 int /*<<< orphan*/  XK_Super_R ; 

__attribute__((used)) static unsigned GetX11Modifier( xcb_connection_t *p_connection,
        xcb_key_symbols_t *p_symbols, unsigned i_vlc )
{
    unsigned i_mask = 0;

    if( i_vlc & KEY_MODIFIER_ALT )
        i_mask |= GetModifier( p_connection, p_symbols, XK_Alt_L ) |
                  GetModifier( p_connection, p_symbols, XK_Alt_R );
    if( i_vlc & KEY_MODIFIER_SHIFT )
        i_mask |= GetModifier( p_connection, p_symbols, XK_Shift_L ) |
                  GetModifier( p_connection, p_symbols, XK_Shift_R );
    if( i_vlc & KEY_MODIFIER_CTRL )
        i_mask |= GetModifier( p_connection, p_symbols, XK_Control_L ) |
                  GetModifier( p_connection, p_symbols, XK_Control_R );
    if( i_vlc & KEY_MODIFIER_META )
        i_mask |= GetModifier( p_connection, p_symbols, XK_Meta_L ) |
                  GetModifier( p_connection, p_symbols, XK_Meta_R ) |
                  GetModifier( p_connection, p_symbols, XK_Super_L ) |
                  GetModifier( p_connection, p_symbols, XK_Super_R );
    return i_mask;
}