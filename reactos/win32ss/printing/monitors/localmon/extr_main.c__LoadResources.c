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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  PWSTR ;
typedef  int /*<<< orphan*/  HINSTANCE ;

/* Variables and functions */
 int /*<<< orphan*/  IDS_LOCAL_MONITOR ; 
 int /*<<< orphan*/  IDS_LOCAL_PORT ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cbLocalMonitor ; 
 int cbLocalPort ; 
 int /*<<< orphan*/  pwszLocalMonitor ; 
 int /*<<< orphan*/  pwszLocalPort ; 
 int wcslen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_LoadResources(HINSTANCE hinstDLL)
{
    LoadStringW(hinstDLL, IDS_LOCAL_MONITOR, (PWSTR)&pwszLocalMonitor, 0);
    cbLocalMonitor = (wcslen(pwszLocalMonitor) + 1) * sizeof(WCHAR);

    LoadStringW(hinstDLL, IDS_LOCAL_PORT, (PWSTR)&pwszLocalPort, 0);
    cbLocalPort = (wcslen(pwszLocalPort) + 1) * sizeof(WCHAR);
}