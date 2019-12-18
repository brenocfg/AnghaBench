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
typedef  int /*<<< orphan*/  buff ;
typedef  int /*<<< orphan*/ * LPVOID ;
typedef  int INT_PTR ;
typedef  int /*<<< orphan*/ * HPEN ;
typedef  int /*<<< orphan*/ * HDC ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BLACK_PEN ; 
 int DeleteObject (int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_INVALID_HANDLE ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_NOACCESS ; 
 int /*<<< orphan*/ * GetCurrentObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GetDC (int /*<<< orphan*/ *) ; 
 scalar_t__ GetLastError () ; 
 int GetObjectA (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int GetObjectType (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetStockObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OBJ_PEN ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SelectObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int UnrealizeObject (int /*<<< orphan*/ *) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,int,scalar_t__) ; 

__attribute__((used)) static void test_gdi_objects(void)
{
    BYTE buff[256];
    HDC hdc = GetDC(NULL);
    HPEN hp;
    int i;
    BOOL ret;

    /* SelectObject() with a NULL DC returns 0 and sets ERROR_INVALID_HANDLE.
     * Note: Under XP at least invalid ptrs can also be passed, not just NULL;
     *       Don't test that here in case it crashes earlier win versions.
     */
    SetLastError(0);
    hp = SelectObject(NULL, GetStockObject(BLACK_PEN));
    ok(!hp && (GetLastError() == ERROR_INVALID_HANDLE || broken(!GetLastError())),
       "SelectObject(NULL DC) expected 0, ERROR_INVALID_HANDLE, got %p, %u\n",
       hp, GetLastError());

    /* With a valid DC and a NULL object, the call returns 0 but does not SetLastError() */
    SetLastError(0);
    hp = SelectObject(hdc, NULL);
    ok(!hp && !GetLastError(),
       "SelectObject(NULL obj) expected 0, NO_ERROR, got %p, %u\n",
       hp, GetLastError());

    /* The DC is unaffected by the NULL SelectObject */
    SetLastError(0);
    hp = SelectObject(hdc, GetStockObject(BLACK_PEN));
    ok(hp && !GetLastError(),
       "SelectObject(post NULL) expected non-null, NO_ERROR, got %p, %u\n",
       hp, GetLastError());

    /* GetCurrentObject does not SetLastError() on a null object */
    SetLastError(0);
    hp = GetCurrentObject(NULL, OBJ_PEN);
    ok(!hp && !GetLastError(),
       "GetCurrentObject(NULL DC) expected 0, NO_ERROR, got %p, %u\n",
       hp, GetLastError());

    /* DeleteObject does not SetLastError() on a null object */
    ret = DeleteObject(NULL);
    ok( !ret && !GetLastError(),
       "DeleteObject(NULL obj), expected 0, NO_ERROR, got %d, %u\n",
       ret, GetLastError());

    /* GetObject does not SetLastError() on a null object */
    SetLastError(0);
    i = GetObjectA(NULL, sizeof(buff), buff);
    ok (!i && (GetLastError() == 0 || GetLastError() == ERROR_INVALID_PARAMETER),
        "GetObject(NULL obj), expected 0, NO_ERROR, got %d, %u\n",
	i, GetLastError());

    /* GetObject expects ERROR_NOACCESS when passed an invalid buffer */
    hp = SelectObject(hdc, GetStockObject(BLACK_PEN));
    SetLastError(0);
    i = GetObjectA(hp, (INT_PTR)buff, (LPVOID)sizeof(buff));
    ok (!i && (GetLastError() == 0 || GetLastError() == ERROR_NOACCESS),
        "GetObject(invalid buff), expected 0, ERROR_NOACCESS, got %d, %u\n",
    i, GetLastError());

    /* GetObjectType does SetLastError() on a null object */
    SetLastError(0);
    i = GetObjectType(NULL);
    ok (!i && GetLastError() == ERROR_INVALID_HANDLE,
        "GetObjectType(NULL obj), expected 0, ERROR_INVALID_HANDLE, got %d, %u\n",
        i, GetLastError());

    /* UnrealizeObject does not SetLastError() on a null object */
    SetLastError(0);
    i = UnrealizeObject(NULL);
    ok (!i && !GetLastError(),
        "UnrealizeObject(NULL obj), expected 0, NO_ERROR, got %d, %u\n",
        i, GetLastError());

    ReleaseDC(NULL, hdc);
}