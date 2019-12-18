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
typedef  unsigned int xcb_keysym_t ;
struct TYPE_2__ {unsigned int i_vlc; unsigned int i_x11; } ;

/* Variables and functions */
 unsigned int XK_VoidSymbol ; 
 TYPE_1__* x11keys_to_vlckeys ; 

__attribute__((used)) static xcb_keysym_t GetX11Key( unsigned i_vlc )
{
    /* X11 and VLC use ASCII for printable ASCII characters */
    if( i_vlc >= 32 && i_vlc <= 127 )
        return i_vlc;

    for( int i = 0; x11keys_to_vlckeys[i].i_vlc != 0; i++ )
    {
        if( x11keys_to_vlckeys[i].i_vlc == i_vlc )
            return x11keys_to_vlckeys[i].i_x11;
    }

    return XK_VoidSymbol;
}