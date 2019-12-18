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
typedef  int /*<<< orphan*/  SIZE ;
typedef  int INT ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int GetTextExtentExPointA (int /*<<< orphan*/ ,char*,int,int,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int GetTextExtentExPointW (int /*<<< orphan*/ ,char*,int,int,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok_err (int) ; 
 int /*<<< orphan*/  ok_int (int,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

void Test_GetTextExtentExPoint()
{
    INT nFit;
    SIZE size;
    BOOL result;

    SetLastError(0);

    result = GetTextExtentExPointA(GetDC(0), "test", 4, 1000, &nFit, NULL, &size);
    ok_int(result, 1);
    ok_int(nFit, 4);
    ok_err(0);
    printf("nFit = %d\n", nFit);

    result = GetTextExtentExPointA(GetDC(0), "test", 4, 1, &nFit, NULL, &size);
    ok_int(result, 1);
    ok_int(nFit, 0);
    ok_err(0);
    printf("nFit = %d\n", nFit);

    result = GetTextExtentExPointA(GetDC(0), "test", 4, 0, &nFit, NULL, &size);
    ok_int(result, 1);
    ok_int(nFit, 0);
    ok_err(0);

    result = GetTextExtentExPointA(GetDC(0), "test", 4, -1, &nFit, NULL, &size);
    ok_int(result, 1);
    ok_int(nFit, 4);
    ok_err(0);

    result = GetTextExtentExPointA(GetDC(0), "test", 4, -2, &nFit, NULL, &size);
    ok_int(result, 0);
    ok_err(87);

    result = GetTextExtentExPointW(GetDC(0), L"test", 4, -10, &nFit, NULL, &size);
    ok_int(result, 1);

    result = GetTextExtentExPointA(GetDC(0), "test", 4, -10, &nFit, NULL, &size);
    ok_int(result, 0);
}