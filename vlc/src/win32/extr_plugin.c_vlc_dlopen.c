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
typedef  void* HMODULE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  LOAD_LIBRARY_SEARCH_SYSTEM32 ; 
 void* LoadLibraryExW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* LoadPackagedLibrary (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEM_FAILCRITICALERRORS ; 
 scalar_t__ SetThreadErrorMode (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ToWide (char const*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

void *vlc_dlopen(const char *psz_file, bool lazy)
{
    wchar_t *wfile = ToWide (psz_file);
    if (wfile == NULL)
        return NULL;

    HMODULE handle = NULL;
#if !VLC_WINSTORE_APP
    DWORD mode;
    if (SetThreadErrorMode (SEM_FAILCRITICALERRORS, &mode) != 0)
    {
        handle = LoadLibraryExW(wfile, NULL, LOAD_LIBRARY_SEARCH_SYSTEM32);
        SetThreadErrorMode (mode, NULL);
    }
#else
    handle = LoadPackagedLibrary( wfile, 0 );
#endif
    free (wfile);

    (void) lazy;
    return handle;
}