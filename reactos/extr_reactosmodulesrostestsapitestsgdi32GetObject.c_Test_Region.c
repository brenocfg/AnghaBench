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
typedef  int /*<<< orphan*/  HRGN ;

/* Variables and functions */
 int /*<<< orphan*/  CreateRectRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 scalar_t__ ERROR_INVALID_HANDLE ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ GetObjectW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*) ; 

void
Test_Region(void)
{
    HRGN hRgn;
    hRgn = CreateRectRgn(0,0,5,5);
    SetLastError(ERROR_SUCCESS);
    ok(GetObjectW(hRgn, 0, NULL) == 0, "\n");
    ok(GetLastError() == ERROR_INVALID_HANDLE, "\n");
    DeleteObject(hRgn);
}