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
typedef  int /*<<< orphan*/  wchar_t ;

/* Variables and functions */
 int FORMAT_MESSAGE_FROM_SYSTEM ; 
 int FORMAT_MESSAGE_IGNORE_INSERTS ; 
 int /*<<< orphan*/  FormatMessageW (int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 char* FromWide (int /*<<< orphan*/ *) ; 
 int GetLastError () ; 
 int /*<<< orphan*/  LANG_NEUTRAL ; 
 int /*<<< orphan*/  MAKELANGID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUBLANG_DEFAULT ; 
 int /*<<< orphan*/  snwprintf (int /*<<< orphan*/ *,int,char*,int) ; 
 int /*<<< orphan*/  wmemchr (char*,int /*<<< orphan*/ ,int) ; 

char *vlc_dlerror(void)
{
    wchar_t wmsg[256];
    int i = 0, i_error = GetLastError();

    FormatMessageW( FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                    NULL, i_error, MAKELANGID (LANG_NEUTRAL, SUBLANG_DEFAULT),
                    wmsg, 256, NULL );

    /* Go to the end of the string */
    while( !wmemchr( L"\r\n\0", wmsg[i], 3 ) )
        i++;

    snwprintf( wmsg + i, 256 - i, L" (error %i)", i_error );
    return FromWide( wmsg );
}