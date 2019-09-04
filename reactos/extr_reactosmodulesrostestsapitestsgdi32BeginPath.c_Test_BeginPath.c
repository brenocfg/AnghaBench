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
typedef  int /*<<< orphan*/  HDC ;
typedef  int BOOL ;

/* Variables and functions */
 int BeginPath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int ERROR_INVALID_HANDLE ; 
 int GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

void Test_BeginPath()
{
    HDC hdc;
    BOOL ret;

    SetLastError(0);
    ret = BeginPath(0);
    ok(ret == 0, "BeginPath(0) succeeded, ret == %d\n", ret);
    ok(GetLastError() == ERROR_INVALID_HANDLE, "GetLastError() == %ld\n", GetLastError());

    hdc = CreateCompatibleDC(NULL);

    SetLastError(0);
    ret = BeginPath(hdc);
    ok(ret == 1, "BeginPath(hdc) failed, ret == %d\n", ret);
    ok(GetLastError() == 0, "GetLastError() == %ld\n", GetLastError());

    DeleteDC(hdc);

}