#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  winxpW ;
typedef  int /*<<< orphan*/  winxp64W ;
typedef  int /*<<< orphan*/  windowsW ;
typedef  int /*<<< orphan*/  win8W ;
typedef  int /*<<< orphan*/  win81W ;
typedef  int /*<<< orphan*/  win7W ;
typedef  int /*<<< orphan*/  win2008r2W ;
typedef  int /*<<< orphan*/  win2008W ;
typedef  int /*<<< orphan*/  win2003W ;
typedef  int /*<<< orphan*/  win2000W ;
typedef  int /*<<< orphan*/  win10W ;
typedef  int /*<<< orphan*/  vistaW ;
typedef  char WCHAR ;
struct TYPE_3__ {int dwMajorVersion; int dwMinorVersion; scalar_t__ wProductType; } ;
typedef  TYPE_1__ OSVERSIONINFOEXW ;

/* Variables and functions */
 int ARRAY_SIZE (char const*) ; 
 scalar_t__ VER_NT_WORKSTATION ; 
 char* heap_alloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 

__attribute__((used)) static WCHAR *get_oscaption( OSVERSIONINFOEXW *ver )
{
    static const WCHAR windowsW[] =
        {'M','i','c','r','o','s','o','f','t',' ','W','i','n','d','o','w','s',' '};
    static const WCHAR win2000W[] =
        {'2','0','0','0',' ','P','r','o','f','e','s','s','i','o','n','a','l',0};
    static const WCHAR win2003W[] =
        {'S','e','r','v','e','r',' ','2','0','0','3',' ','S','t','a','n','d','a','r','d',' ','E','d','i','t','i','o','n',0};
    static const WCHAR winxpW[] =
        {'X','P',' ','P','r','o','f','e','s','s','i','o','n','a','l',0};
    static const WCHAR winxp64W[] =
        {'X','P',' ','P','r','o','f','e','s','s','i','o','n','a','l',' ','x','6','4',' ','E','d','i','t','i','o','n',0};
    static const WCHAR vistaW[] =
        {'V','i','s','t','a',' ','U','l','t','i','m','a','t','e',0};
    static const WCHAR win2008W[] =
        {'S','e','r','v','e','r',' ','2','0','0','8',' ','S','t','a','n','d','a','r','d',0};
    static const WCHAR win7W[] =
        {'7',' ','P','r','o','f','e','s','s','i','o','n','a','l',0};
    static const WCHAR win2008r2W[] =
        {'S','e','r','v','e','r',' ','2','0','0','8',' ','R','2',' ','S','t','a','n','d','a','r','d',0};
    static const WCHAR win8W[] =
        {'8',' ','P','r','o',0};
    static const WCHAR win81W[] =
        {'8','.','1',' ','P','r','o',0};
    static const WCHAR win10W[] =
        {'1','0',' ','P','r','o',0};
    int len = ARRAY_SIZE( windowsW );
    WCHAR *ret;

    if (!(ret = heap_alloc( len * sizeof(WCHAR) + sizeof(win2003W) ))) return NULL;
    memcpy( ret, windowsW, sizeof(windowsW) );
    if (ver->dwMajorVersion == 10 && ver->dwMinorVersion == 0) memcpy( ret + len, win10W, sizeof(win10W) );
    else if (ver->dwMajorVersion == 6 && ver->dwMinorVersion == 3) memcpy( ret + len, win8W, sizeof(win8W) );
    else if (ver->dwMajorVersion == 6 && ver->dwMinorVersion == 2) memcpy( ret + len, win81W, sizeof(win81W) );
    else if (ver->dwMajorVersion == 6 && ver->dwMinorVersion == 1)
    {
        if (ver->wProductType == VER_NT_WORKSTATION) memcpy( ret + len, win7W, sizeof(win7W) );
        else memcpy( ret + len, win2008r2W, sizeof(win2008r2W) );
    }
    else if (ver->dwMajorVersion == 6 && ver->dwMinorVersion == 0)
    {
        if (ver->wProductType == VER_NT_WORKSTATION) memcpy( ret + len, vistaW, sizeof(vistaW) );
        else memcpy( ret + len, win2008W, sizeof(win2008W) );
    }
    else if (ver->dwMajorVersion == 5 && ver->dwMinorVersion == 2)
    {
        if (ver->wProductType == VER_NT_WORKSTATION) memcpy( ret + len, winxp64W, sizeof(winxp64W) );
        else memcpy( ret + len, win2003W, sizeof(win2003W) );
    }
    else if (ver->dwMajorVersion == 5 && ver->dwMinorVersion == 1) memcpy( ret + len, winxpW, sizeof(winxpW) );
    else memcpy( ret + len, win2000W, sizeof(win2000W) );
    return ret;
}