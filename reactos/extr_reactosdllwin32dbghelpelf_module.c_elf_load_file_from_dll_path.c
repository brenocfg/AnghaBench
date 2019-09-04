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
struct elf_info {int dummy; } ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CP_UNIXCP ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  const* S_SlashW ; 
 int /*<<< orphan*/  elf_load_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long,unsigned long,struct elf_info*) ; 
 unsigned int lstrlenW (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  strcatW (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 char* wine_dll_enum_load_path (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL elf_load_file_from_dll_path(HANDLE hProcess,
                                        const WCHAR* filename,
                                        unsigned long load_offset,
                                        unsigned long dyn_addr,
                                        struct elf_info* elf_info)
{
    BOOL ret = FALSE;
    unsigned int index = 0;
    const char *path;

    while (!ret && (path = wine_dll_enum_load_path( index++ )))
    {
        WCHAR *name;
        unsigned len;

        len = MultiByteToWideChar(CP_UNIXCP, 0, path, -1, NULL, 0);

        name = HeapAlloc( GetProcessHeap(), 0,
                          (len + lstrlenW(filename) + 2) * sizeof(WCHAR) );

        if (!name) break;
        MultiByteToWideChar(CP_UNIXCP, 0, path, -1, name, len);
        strcatW( name, S_SlashW );
        strcatW( name, filename );
        ret = elf_load_file(hProcess, name, load_offset, dyn_addr, elf_info);
        HeapFree( GetProcessHeap(), 0, name );
    }
    return ret;
}