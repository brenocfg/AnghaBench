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
typedef  char wchar_t ;
typedef  char* HMODULE ;
typedef  long DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 long ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  FreeLibrary (char*) ; 
 char* LoadLibraryA (char*) ; 
 char* LoadLibraryW (char*) ; 
 long ReportLastError () ; 
 int /*<<< orphan*/  dprintf (char*,...) ; 
 int mbstowcs (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

DWORD LoadLibraryList(char** libnames, int counter, BOOL bUseAnsi)
{
    HMODULE hModule;

    dprintf("Attempting to LoadLibrary");
    if (bUseAnsi) {
        dprintf("A(%s) - ", *libnames);
        hModule = LoadLibraryA(*libnames);
    } else {
        int len;
        wchar_t libnameW[500];
        len = mbstowcs(libnameW, *libnames, strlen(*libnames));
        if (len) {
            libnameW[len] = L'\0';
            dprintf("W(%S) - ", libnameW);
            hModule = LoadLibraryW(libnameW);
        } else {
            return ERROR_INVALID_PARAMETER;
        }
    }
    if (hModule == NULL) {
        dprintf("\nERROR: failed to obtain handle to module %s - %x\n", *libnames, hModule);
        return ReportLastError();
    }
    dprintf("%x\n", hModule);

    if (counter--) {
        LoadLibraryList(++libnames, counter, bUseAnsi);
    }

    if (!FreeLibrary(hModule)) {
        dprintf("ERROR: failed to free module %s - %x\n", *libnames, hModule);
        return ReportLastError();
    } else {
        dprintf("FreeLibrary(%x) - successfull.\n", hModule);
    }
    return 0L;
}