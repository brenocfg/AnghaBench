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
typedef  int /*<<< orphan*/  HMODULE ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  GetModuleHandleA (char const*) ; 
 int /*<<< orphan*/  LoadLibraryW (char*) ; 
 char* __mingw_enum_import_library_names (int /*<<< orphan*/ ) ; 

HMODULE __mingw_get_msvcrt_handle(void)
{
    static HANDLE msvcrt_handle;

    if(!msvcrt_handle) {
        const char *lib_name;
        int i = 0;

        while ((lib_name = __mingw_enum_import_library_names (i++))) {
            if((lib_name[0] == 'm' || lib_name[0] == 'M')
               && (lib_name[1] == 's' || lib_name[1] == 'S')
               && (lib_name[2] == 'v' || lib_name[2] == 'V')
               && (lib_name[3] == 'c' || lib_name[3] == 'C')
               && (lib_name[4] == 'r' || lib_name[4] == 'R')
               && (lib_name[5] == 't' || lib_name[5] == 'T' || ('0' <= lib_name[5] && lib_name[5] <= '9')))
                break;
        }

       if(lib_name)
            msvcrt_handle = GetModuleHandleA(lib_name);
        if(!msvcrt_handle)
            msvcrt_handle = LoadLibraryW(L"msvcrt.dll");
    }

    return msvcrt_handle;
}