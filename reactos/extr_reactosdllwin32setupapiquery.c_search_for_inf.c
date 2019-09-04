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
typedef  char const* LPCVOID ;
typedef  scalar_t__ HINF ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetWindowsDirectoryW (char*,int) ; 
 scalar_t__ INFINFO_REVERSE_DEFAULT_SEARCH ; 
 int INF_STYLE_OLDNT ; 
 int INF_STYLE_WIN4 ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 scalar_t__ SetupOpenInfFileW (char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcatW (char*,char const*) ; 
 int /*<<< orphan*/  lstrcpyW (char*,char const*) ; 

__attribute__((used)) static HINF search_for_inf(LPCVOID InfSpec, DWORD SearchControl)
{
    HINF hInf = INVALID_HANDLE_VALUE;
    WCHAR inf_path[MAX_PATH];

    static const WCHAR infW[] = {'\\','i','n','f','\\',0};
    static const WCHAR system32W[] = {'\\','s','y','s','t','e','m','3','2','\\',0};

    if (SearchControl == INFINFO_REVERSE_DEFAULT_SEARCH)
    {
        GetWindowsDirectoryW(inf_path, MAX_PATH);
        lstrcatW(inf_path, system32W);
        lstrcatW(inf_path, InfSpec);

        hInf = SetupOpenInfFileW(inf_path, NULL,
                                 INF_STYLE_OLDNT | INF_STYLE_WIN4, NULL);
        if (hInf != INVALID_HANDLE_VALUE)
            return hInf;

        GetWindowsDirectoryW(inf_path, MAX_PATH);
        lstrcpyW(inf_path, infW);
        lstrcatW(inf_path, InfSpec);

        return SetupOpenInfFileW(inf_path, NULL,
                                 INF_STYLE_OLDNT | INF_STYLE_WIN4, NULL);
    }

    return INVALID_HANDLE_VALUE;
}