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
 int /*<<< orphan*/  DUMP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SWP_ASYNCWINDOWPOS ; 
 int /*<<< orphan*/  SWP_DEFERERASE ; 
 int /*<<< orphan*/  SWP_FRAMECHANGED ; 
 int /*<<< orphan*/  SWP_HIDEWINDOW ; 
 int /*<<< orphan*/  SWP_NOACTIVATE ; 
 int /*<<< orphan*/  SWP_NOCLIENTMOVE ; 
 int /*<<< orphan*/  SWP_NOCLIENTSIZE ; 
 int /*<<< orphan*/  SWP_NOCOPYBITS ; 
 int /*<<< orphan*/  SWP_NOMOVE ; 
 int /*<<< orphan*/  SWP_NOOWNERZORDER ; 
 int /*<<< orphan*/  SWP_NOREDRAW ; 
 int /*<<< orphan*/  SWP_NOSENDCHANGING ; 
 int /*<<< orphan*/  SWP_NOSIZE ; 
 int /*<<< orphan*/  SWP_NOZORDER ; 
 int /*<<< orphan*/  SWP_SHOWWINDOW ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
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