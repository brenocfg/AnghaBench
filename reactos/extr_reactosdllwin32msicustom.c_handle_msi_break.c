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
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  LPCWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  DebugBreak () ; 
 int /*<<< orphan*/  GetCurrentProcessId () ; 
 int /*<<< orphan*/  GetEnvironmentVariableW (char const*,char*,int) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MB_OK ; 
 int /*<<< orphan*/  MessageBoxW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int lstrlenW (char const*) ; 
 int /*<<< orphan*/  msi_alloc (int) ; 
 int /*<<< orphan*/  msi_free (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmpiW (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wsprintfW (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_msi_break( LPCWSTR target )
{
    LPWSTR msg;
    WCHAR val[MAX_PATH];

    static const WCHAR MsiBreak[] = { 'M','s','i','B','r','e','a','k',0 };
    static const WCHAR WindowsInstaller[] = {
        'W','i','n','d','o','w','s',' ','I','n','s','t','a','l','l','e','r',0
    };

    static const WCHAR format[] = {
        'T','o',' ','d','e','b','u','g',' ','y','o','u','r',' ',
        'c','u','s','t','o','m',' ','a','c','t','i','o','n',',',' ',
        'a','t','t','a','c','h',' ','y','o','u','r',' ','d','e','b','u','g','g','e','r',' ',
        't','o',' ','p','r','o','c','e','s','s',' ','%','i',' ','(','0','x','%','X',')',' ',
        'a','n','d',' ','p','r','e','s','s',' ','O','K',0
    };

    if( !GetEnvironmentVariableW( MsiBreak, val, MAX_PATH ))
        return;

    if( strcmpiW( val, target ))
        return;

    msg = msi_alloc( (lstrlenW(format) + 10) * sizeof(WCHAR) );
    if (!msg)
        return;

    wsprintfW( msg, format, GetCurrentProcessId(), GetCurrentProcessId());
    MessageBoxW( NULL, msg, WindowsInstaller, MB_OK);
    msi_free(msg);
    DebugBreak();
}