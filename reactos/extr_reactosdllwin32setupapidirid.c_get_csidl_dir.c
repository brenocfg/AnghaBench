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
typedef  int /*<<< orphan*/  const WCHAR ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  const* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  SHGetSpecialFolderPathW (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  const* get_unknown_dirid () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 int strlenW (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static const WCHAR *get_csidl_dir( DWORD csidl )
{
    WCHAR buffer[MAX_PATH], *str;
    int len;

    if (!SHGetSpecialFolderPathW( NULL, buffer, csidl, TRUE ))
    {
        FIXME( "CSIDL %x not found\n", csidl );
        return get_unknown_dirid();
    }
    len = (strlenW(buffer) + 1) * sizeof(WCHAR);
    if ((str = HeapAlloc( GetProcessHeap(), 0, len ))) memcpy( str, buffer, len );
    return str;
}