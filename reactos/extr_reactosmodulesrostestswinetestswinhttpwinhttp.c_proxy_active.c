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
struct TYPE_3__ {int /*<<< orphan*/ * lpszProxyBypass; int /*<<< orphan*/ * lpszProxy; } ;
typedef  TYPE_1__ WINHTTP_PROXY_INFO ;
typedef  int BOOL ;

/* Variables and functions */
 int ERROR_SUCCESS ; 
 int FALSE ; 
 int GetLastError () ; 
 int /*<<< orphan*/  GlobalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 scalar_t__ WinHttpGetDefaultProxyConfiguration (TYPE_1__*) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static BOOL proxy_active(void)
{
    WINHTTP_PROXY_INFO proxy_info;
    BOOL active = FALSE;

    SetLastError(0xdeadbeef);
    if (WinHttpGetDefaultProxyConfiguration(&proxy_info))
    {
        ok(GetLastError() == ERROR_SUCCESS || broken(GetLastError() == 0xdeadbeef) /* < win7 */,
           "got %u\n", GetLastError());
        active = (proxy_info.lpszProxy != NULL);
        if (active)
            GlobalFree(proxy_info.lpszProxy);
        if (proxy_info.lpszProxyBypass != NULL)
            GlobalFree(proxy_info.lpszProxyBypass);
    }
    else
       active = FALSE;

    return active;
}