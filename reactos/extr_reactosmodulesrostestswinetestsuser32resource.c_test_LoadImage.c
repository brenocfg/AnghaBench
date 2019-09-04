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
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int /*<<< orphan*/ * HRSRC ;
typedef  int /*<<< orphan*/ * HBITMAP ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * FindResourceA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetModuleHandleA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LoadBitmapA (int /*<<< orphan*/ ,char*) ; 
 char* MAKEINTRESOURCEA (int) ; 
 scalar_t__ RT_BITMAP ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void test_LoadImage(void)
{
    HBITMAP bmp;
    HRSRC hres;

    bmp = LoadBitmapA(GetModuleHandleA(NULL), MAKEINTRESOURCEA(100));
    ok(bmp != NULL, "Could not load a bitmap resource\n");
    if (bmp) DeleteObject(bmp);

    hres = FindResourceA(GetModuleHandleA(NULL), "#100", (LPCSTR)RT_BITMAP);
    ok(hres != NULL, "Could not find a bitmap resource with a numeric string\n");

    bmp = LoadBitmapA(GetModuleHandleA(NULL), "#100");
    ok(bmp != NULL, "Could not load a bitmap resource with a numeric string\n");
    if (bmp) DeleteObject(bmp);
}