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
typedef  int /*<<< orphan*/  wineW ;
typedef  char WCHAR ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CP_UNIXCP ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,char*,int) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (char*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  strcatW (char*,char const*) ; 
 int /*<<< orphan*/  strcmpW (char*,char const*) ; 
 int /*<<< orphan*/  strcpyW (char*,char const*) ; 
 int strlenW (char const*) ; 

const WCHAR *get_wine_loader_name(void)
{
    static const BOOL is_win64 = sizeof(void *) > sizeof(int); /* FIXME: should depend on target process */
    static const WCHAR wineW[] = {'w','i','n','e',0};
    static const WCHAR suffixW[] = {'6','4',0};
    static const WCHAR *loader;

    if (!loader)
    {
        WCHAR *p, *buffer;
        const char *ptr;

        /* All binaries are loaded with WINELOADER (if run from tree) or by the
         * main executable
         */
        if ((ptr = getenv("WINELOADER")))
        {
            DWORD len = 2 + MultiByteToWideChar( CP_UNIXCP, 0, ptr, -1, NULL, 0 );
            buffer = HeapAlloc( GetProcessHeap(), 0, len * sizeof(WCHAR) );
            MultiByteToWideChar( CP_UNIXCP, 0, ptr, -1, buffer, len );
        }
        else
        {
            buffer = HeapAlloc( GetProcessHeap(), 0, sizeof(wineW) + 2 * sizeof(WCHAR) );
            strcpyW( buffer, wineW );
        }
        p = buffer + strlenW( buffer ) - strlenW( suffixW );
        if (p > buffer && !strcmpW( p, suffixW ))
        {
            if (!is_win64) *p = 0;
        }
        else if (is_win64) strcatW( buffer, suffixW );

        TRACE( "returning %s\n", debugstr_w(buffer) );
        loader = buffer;
    }
    return loader;
}