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
typedef  int UINT ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int GetSystemDirectoryW (char*,int) ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcatW (char*,char const*) ; 
 int strlenW (char const*) ; 

__attribute__((used)) static const WCHAR *get_unknown_dirid(void)
{
    static WCHAR *unknown_dirid;
    static const WCHAR unknown_str[] = {'\\','u','n','k','n','o','w','n',0};

    if (!unknown_dirid)
    {
        UINT len = GetSystemDirectoryW( NULL, 0 ) + strlenW(unknown_str);
        if (!(unknown_dirid = HeapAlloc( GetProcessHeap(), 0, len * sizeof(WCHAR) ))) return NULL;
        GetSystemDirectoryW( unknown_dirid, len );
        strcatW( unknown_dirid, unknown_str );
    }
    return unknown_dirid;
}