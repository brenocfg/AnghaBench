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
typedef  int ULONG_PTR ;
typedef  int ULONG ;
typedef  int* PVOID ;
typedef  int POINT ;
typedef  int /*<<< orphan*/ * HDC ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateCompatibleDC (int /*<<< orphan*/ *) ; 
 int ERROR_INVALID_HANDLE ; 
 int ERROR_INVALID_PARAMETER ; 
 int GDI_HANDLE_BASETYPE_MASK ; 
 int GDI_OBJECT_TYPE_REGION ; 
 int GetLastError () ; 
 int NtGdiPolyPolyDraw (int /*<<< orphan*/ *,int*,int*,int,int) ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST (int) ; 

__attribute__((used)) static
void
Test_Params(void)
{
    ULONG_PTR ret;
    ULONG Count1[4] = {3, 2, 4, 3};
    ULONG Count2[2] = {0, 3};
    ULONG Count3[2] = {0, 0};
    ULONG Count4[2] = {1, 3};
    ULONG Count5[2] = {0x80000001, 0x80000001};
    POINT Points[6] = {{0,0}, {1,1}, {3,-3}, {-2,2}, {4,2}, {2,4}};
    HDC hDC;

    SetLastError(0);
    ret = NtGdiPolyPolyDraw(NULL, NULL, NULL, 0, 0);
    TEST(ret == 0);
    TEST(GetLastError() == 0);

    SetLastError(0);
    ret = NtGdiPolyPolyDraw(NULL, NULL, NULL, 0, 1);
    TEST(ret == 0);
    TEST(GetLastError() == 0);

    SetLastError(0);
    ret = NtGdiPolyPolyDraw(NULL, NULL, NULL, 0, 2);
    TEST(ret == 0);
    TEST(GetLastError() == 0);

    SetLastError(0);
    ret = NtGdiPolyPolyDraw(NULL, NULL, NULL, 0, 3);
    TEST(ret == 0);
    TEST(GetLastError() == 0);

    SetLastError(0);
    ret = NtGdiPolyPolyDraw(NULL, NULL, NULL, 0, 4);
    TEST(ret == 0);
    TEST(GetLastError() == 0);

    SetLastError(0);
    ret = NtGdiPolyPolyDraw(NULL, NULL, NULL, 0, 5);
    TEST(ret == 0);
    TEST(GetLastError() == 0);

    SetLastError(0);
    ret = NtGdiPolyPolyDraw(NULL, NULL, NULL, 0, 6);
    TEST(ret == 0);
    TEST(GetLastError() == 0);

////////////////////////////////////////////////////////////////////////////////

    /* Test with an invalid DC */

    SetLastError(0);
    ret = NtGdiPolyPolyDraw(0, Points, Count1, 2, 1);
    TEST(ret == 0);
    TEST(GetLastError() == ERROR_INVALID_HANDLE);

    hDC = (HDC)0x12345;

    SetLastError(0);
    ret = NtGdiPolyPolyDraw(hDC, Points, Count1, 2, 0);
    TEST(ret == 0);
    TEST(GetLastError() == 0);

    SetLastError(0);
    ret = NtGdiPolyPolyDraw(hDC, Points, Count1, 2, 1);
    TEST(ret == 0);
    TEST(GetLastError() == ERROR_INVALID_HANDLE);

    SetLastError(0);
    ret = NtGdiPolyPolyDraw(hDC, Points, Count1, 2, 2);
    TEST(ret == 0);
    TEST(GetLastError() == ERROR_INVALID_HANDLE);

    SetLastError(0);
    ret = NtGdiPolyPolyDraw(hDC, Points, Count1, 2, 3);
    TEST(ret == 0);
    TEST(GetLastError() == ERROR_INVALID_HANDLE);

    SetLastError(0);
    ret = NtGdiPolyPolyDraw(hDC, Points, Count1, 2, 4);
    TEST(ret == 0);
    TEST(GetLastError() == ERROR_INVALID_HANDLE);

    SetLastError(0);
    ret = NtGdiPolyPolyDraw(hDC, Points, Count1, 2, 5);
    TEST(ret == 0);
    TEST(GetLastError() == ERROR_INVALID_HANDLE);

    SetLastError(0);
    ret = NtGdiPolyPolyDraw(hDC, Points, Count1, 2, 6);
    TEST(ret == 0);
    TEST(GetLastError() == 0);

    SetLastError(0);
    ret = NtGdiPolyPolyDraw((HDC)1, Points, Count1, 1, 6);
    TEST((ret & GDI_HANDLE_BASETYPE_MASK) == GDI_OBJECT_TYPE_REGION);
    TEST(GetLastError() == 0);

    SetLastError(0);
    ret = NtGdiPolyPolyDraw((HDC)0, Points, Count1, 1, 6);
    TEST(ret == 0);
    TEST(GetLastError() == 0);

    SetLastError(0);
    ret = NtGdiPolyPolyDraw(hDC, Points, Count1, 0, 1);
    TEST(ret == 0);
    TEST(GetLastError() == 0);

    SetLastError(0);
    ret = NtGdiPolyPolyDraw(hDC, Points, Count2, 2, 1);
    TEST(ret == 0);
    TEST(GetLastError() == ERROR_INVALID_HANDLE);

    SetLastError(0);
    ret = NtGdiPolyPolyDraw(hDC, Points, NULL, 2, 1);
    TEST(ret == 0);
    TEST(GetLastError() == 0);

    SetLastError(0);
    ret = NtGdiPolyPolyDraw(hDC, Points, (PVOID)0x81000000, 2, 1);
    TEST(ret == 0);
    TEST(GetLastError() == 0);

    SetLastError(0);
    ret = NtGdiPolyPolyDraw(hDC, NULL, Count1, 2, 1);
    TEST(ret == 0);
    TEST(GetLastError() == 0);

    SetLastError(0);
    ret = NtGdiPolyPolyDraw(hDC, (PVOID)0x81000000, Count1, 2, 1);
    TEST(ret == 0);
    TEST(GetLastError() == 0);


////////////////////////////////////////////////////////////////////////////////

    /* Test with a valid DC */

    hDC = CreateCompatibleDC(NULL);
    ASSERT(hDC);

    SetLastError(0);
    ret = NtGdiPolyPolyDraw(hDC, Points, Count1, 2, 0);
    TEST(ret == 0);
    TEST(GetLastError() == 0);

    SetLastError(0);
    ret = NtGdiPolyPolyDraw(hDC, Points, Count1, 2, 1);
    TEST(ret == 1);
    TEST(GetLastError() == 0);

    SetLastError(0);
    ret = NtGdiPolyPolyDraw(hDC, Points, Count1, 2, 2);
    TEST(ret == 1);
    TEST(GetLastError() == 0);

#if 0
    SetLastError(0);
    // better don't do this on win xp!!! (random crashes)
//    ret = NtGdiPolyPolyDraw(hDC, Points, Count1, 2, 3);
    TEST(ret == 0);
    TEST(GetLastError() == ERROR_INVALID_PARAMETER);

    SetLastError(0);
    // better don't do this on win xp!!! (random crashes)
//    ret = NtGdiPolyPolyDraw(hDC, Points, Count1, 2, 4);
    TEST(ret == 0);
    TEST(GetLastError() == ERROR_INVALID_PARAMETER);

#endif

    SetLastError(0);
    ret = NtGdiPolyPolyDraw(hDC, Points, Count2, 2, 1);
    TEST(ret == 0);
    TEST(GetLastError() == ERROR_INVALID_PARAMETER);

    SetLastError(0);
    ret = NtGdiPolyPolyDraw(hDC, Points, Count3, 2, 1);
    TEST(ret == 0);
    TEST(GetLastError() == 0);

    SetLastError(0);
    ret = NtGdiPolyPolyDraw(hDC, Points, Count4, 2, 1);
    TEST(ret == 0);
    TEST(GetLastError() == ERROR_INVALID_PARAMETER);

    SetLastError(0);
    ret = NtGdiPolyPolyDraw(hDC, Points, Count5, 2, 1);
    TEST(ret == 0);
    TEST(GetLastError() == 87);

}