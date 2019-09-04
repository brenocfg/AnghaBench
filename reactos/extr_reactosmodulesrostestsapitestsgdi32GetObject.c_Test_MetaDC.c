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
typedef  int UINT_PTR ;
typedef  scalar_t__ HDC ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 scalar_t__ CreateMetaFile (int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int GDI_HANDLE_TYPE_MASK ; 
 int GDI_OBJECT_TYPE_METADC ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ GetObjectA (scalar_t__,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  SetLastError (scalar_t__) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

void
Test_MetaDC(void)
{
    /* Windows does not SetLastError() on a metadc, but it doesn't seem to do anything with it */
    HDC hMetaDC;
    BYTE buffer[1000];

    hMetaDC = CreateMetaFile(NULL);
    ok(hMetaDC != 0, "CreateMetaFile failed, skipping tests.\n");
    if(!hMetaDC) return;

    ok(((UINT_PTR)hMetaDC & GDI_HANDLE_TYPE_MASK) == GDI_OBJECT_TYPE_METADC, "\n");

    SetLastError(ERROR_SUCCESS);
    ok(GetObjectA((HANDLE)GDI_OBJECT_TYPE_METADC, 0, NULL) == 0, "\n");
    ok(GetObjectA((HANDLE)GDI_OBJECT_TYPE_METADC, 100, &buffer) == 0, "\n");
    ok(GetObjectA(hMetaDC, 0, NULL) == 0, "\n");
    ok(GetObjectA(hMetaDC, 1000, &buffer) == 0, "\n");
    ok(GetLastError() == ERROR_SUCCESS, "got %ld\n", GetLastError());
}