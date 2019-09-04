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
typedef  char WCHAR ;
typedef  int SYSKIND ;
typedef  int /*<<< orphan*/  LCID ;

/* Variables and functions */
#define  SYS_WIN16 130 
#define  SYS_WIN32 129 
#define  SYS_WIN64 128 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 int /*<<< orphan*/  sprintfW (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcatW (char*,char const*) ; 

__attribute__((used)) static WCHAR *get_lcid_subkey( LCID lcid, SYSKIND syskind, WCHAR *buffer )
{
    static const WCHAR LcidFormatW[] = {'%','l','x','\\',0};
    static const WCHAR win16W[] = {'w','i','n','1','6',0};
    static const WCHAR win32W[] = {'w','i','n','3','2',0};
    static const WCHAR win64W[] = {'w','i','n','6','4',0};

    sprintfW( buffer, LcidFormatW, lcid );
    switch(syskind)
    {
    case SYS_WIN16: strcatW( buffer, win16W ); break;
    case SYS_WIN32: strcatW( buffer, win32W ); break;
    case SYS_WIN64: strcatW( buffer, win64W ); break;
    default:
        TRACE("Typelib is for unsupported syskind %i\n", syskind);
        return NULL;
    }
    return buffer;
}