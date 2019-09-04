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
typedef  int /*<<< orphan*/  PCWSTR ;
typedef  int /*<<< orphan*/  HWINSTA ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CreateWindowStationW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  WINSTA_ALL_ACCESS ; 

__attribute__((used)) static HWINSTA create_winsta(PCWSTR winstaName, DWORD *error)
{
    HWINSTA hwinsta;
    SetLastError(0xfeedf00d);
    hwinsta = CreateWindowStationW(winstaName, 0, WINSTA_ALL_ACCESS, NULL);
    *error = GetLastError();
    return hwinsta;
}