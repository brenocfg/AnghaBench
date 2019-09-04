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
typedef  int UINT ;

/* Variables and functions */
 int SWP_ASYNCWINDOWPOS ; 
 int SWP_DEFERERASE ; 
 int SWP_FRAMECHANGED ; 
 int SWP_HIDEWINDOW ; 
 int SWP_NOACTIVATE ; 
 int SWP_NOCLIENTMOVE ; 
 int SWP_NOCLIENTSIZE ; 
 int SWP_NOCOPYBITS ; 
 int SWP_NOMOVE ; 
 int SWP_NOOWNERZORDER ; 
 int SWP_NOREDRAW ; 
 int SWP_NOSENDCHANGING ; 
 int SWP_NOSIZE ; 
 int SWP_NOZORDER ; 
 int SWP_SHOWWINDOW ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static const char *get_winpos_flags(UINT flags)
{
    static char buffer[300];

    buffer[0] = 0;
#define DUMP(flag) do { if (flags & flag) { strcat( buffer, "|" #flag ); flags &= ~flag; } } while(0)
    DUMP( SWP_SHOWWINDOW );
    DUMP( SWP_HIDEWINDOW );
    DUMP( SWP_NOACTIVATE );
    DUMP( SWP_FRAMECHANGED );
    DUMP( SWP_NOCOPYBITS );
    DUMP( SWP_NOOWNERZORDER );
    DUMP( SWP_NOSENDCHANGING );
    DUMP( SWP_DEFERERASE );
    DUMP( SWP_ASYNCWINDOWPOS );
    DUMP( SWP_NOZORDER );
    DUMP( SWP_NOREDRAW );
    DUMP( SWP_NOSIZE );
    DUMP( SWP_NOMOVE );
    DUMP( SWP_NOCLIENTSIZE );
    DUMP( SWP_NOCLIENTMOVE );
    if (flags) sprintf(buffer + strlen(buffer),"|0x%04x", flags);
    return buffer + 1;
#undef DUMP
}