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
typedef  scalar_t__ UINT_PTR ;

/* Variables and functions */
 int ANSI_FIXED_FONT ; 
 int ANSI_VAR_FONT ; 
 int BLACK_BRUSH ; 
 int BLACK_PEN ; 
 int DC_BRUSH ; 
 int DC_PEN ; 
 int DEFAULT_GUI_FONT ; 
 int DEFAULT_PALETTE ; 
 int DEVICE_DEFAULT_FONT ; 
 int DKGRAY_BRUSH ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ GDI_HANDLE_GET_TYPE (int /*<<< orphan*/ *) ; 
 scalar_t__ GDI_HANDLE_STOCK_MASK ; 
 scalar_t__ GDI_OBJECT_TYPE_BITMAP ; 
 scalar_t__ GDI_OBJECT_TYPE_BRUSH ; 
 scalar_t__ GDI_OBJECT_TYPE_COLORSPACE ; 
 scalar_t__ GDI_OBJECT_TYPE_FONT ; 
 scalar_t__ GDI_OBJECT_TYPE_PALETTE ; 
 scalar_t__ GDI_OBJECT_TYPE_PEN ; 
 int GRAY_BRUSH ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/ * GetStockObject (int) ; 
 int LTGRAY_BRUSH ; 
 int NULL_BRUSH ; 
 int NULL_PEN ; 
 int OEM_FIXED_FONT ; 
 int /*<<< orphan*/  RTEST (int) ; 
 int SYSTEM_FIXED_FONT ; 
 int SYSTEM_FONT ; 
 int /*<<< orphan*/  SetLastError (scalar_t__) ; 
 int /*<<< orphan*/  TEST (int) ; 
 int WHITE_BRUSH ; 
 int WHITE_PEN ; 

void Test_GetStockObject()
{
	/* Test limits and error */
	SetLastError(ERROR_SUCCESS);
	RTEST(GetStockObject(0) != NULL);
	TEST(GetStockObject(20) != NULL);
	RTEST(GetStockObject(21) != NULL);
	RTEST(GetStockObject(-1) == NULL);
	RTEST(GetStockObject(9) == NULL);
	RTEST(GetStockObject(22) == NULL);
	RTEST(GetLastError() == ERROR_SUCCESS);

	/* Test for the stock bit */
	RTEST((UINT_PTR)GetStockObject(WHITE_BRUSH) && GDI_HANDLE_STOCK_MASK);

	/* Test for correct types */
	RTEST(GDI_HANDLE_GET_TYPE(GetStockObject(WHITE_BRUSH)) == GDI_OBJECT_TYPE_BRUSH); /* 0 */
	RTEST(GDI_HANDLE_GET_TYPE(GetStockObject(LTGRAY_BRUSH)) == GDI_OBJECT_TYPE_BRUSH); /* 1 */
	RTEST(GDI_HANDLE_GET_TYPE(GetStockObject(GRAY_BRUSH)) == GDI_OBJECT_TYPE_BRUSH); /* 1 */
	RTEST(GDI_HANDLE_GET_TYPE(GetStockObject(DKGRAY_BRUSH)) == GDI_OBJECT_TYPE_BRUSH); /* 1 */
	RTEST(GDI_HANDLE_GET_TYPE(GetStockObject(BLACK_BRUSH)) == GDI_OBJECT_TYPE_BRUSH); /* 1 */
	RTEST(GDI_HANDLE_GET_TYPE(GetStockObject(NULL_BRUSH)) == GDI_OBJECT_TYPE_BRUSH); /* 1 */
	RTEST(GDI_HANDLE_GET_TYPE(GetStockObject(WHITE_PEN)) == GDI_OBJECT_TYPE_PEN); /* 6 */
	RTEST(GDI_HANDLE_GET_TYPE(GetStockObject(BLACK_PEN)) == GDI_OBJECT_TYPE_PEN); /* 7 */
	RTEST(GDI_HANDLE_GET_TYPE(GetStockObject(NULL_PEN)) == GDI_OBJECT_TYPE_PEN); /* 8 */
	RTEST(GDI_HANDLE_GET_TYPE(GetStockObject(OEM_FIXED_FONT)) == GDI_OBJECT_TYPE_FONT); /* 10 */
	RTEST(GDI_HANDLE_GET_TYPE(GetStockObject(ANSI_FIXED_FONT)) == GDI_OBJECT_TYPE_FONT); /* 11 */
	TEST(GDI_HANDLE_GET_TYPE(GetStockObject(ANSI_VAR_FONT)) == GDI_OBJECT_TYPE_FONT); /* 12 */
	RTEST(GDI_HANDLE_GET_TYPE(GetStockObject(SYSTEM_FONT)) == GDI_OBJECT_TYPE_FONT); /* 13 */
	RTEST(GDI_HANDLE_GET_TYPE(GetStockObject(DEVICE_DEFAULT_FONT)) == GDI_OBJECT_TYPE_FONT); /* 14 */
	RTEST(GDI_HANDLE_GET_TYPE(GetStockObject(DEFAULT_PALETTE)) == GDI_OBJECT_TYPE_PALETTE); /* 15 */
	RTEST(GDI_HANDLE_GET_TYPE(GetStockObject(SYSTEM_FIXED_FONT)) == GDI_OBJECT_TYPE_FONT); /* 16 */
	RTEST(GDI_HANDLE_GET_TYPE(GetStockObject(DEFAULT_GUI_FONT)) == GDI_OBJECT_TYPE_FONT); /* 17 */
	RTEST(GDI_HANDLE_GET_TYPE(GetStockObject(DC_BRUSH)) == GDI_OBJECT_TYPE_BRUSH); /* 18 */
	RTEST(GDI_HANDLE_GET_TYPE(GetStockObject(DC_PEN)) == GDI_OBJECT_TYPE_PEN); /* 19 */
	TEST(GDI_HANDLE_GET_TYPE(GetStockObject(20)) == GDI_OBJECT_TYPE_COLORSPACE); /* 20 */
	RTEST(GDI_HANDLE_GET_TYPE(GetStockObject(21)) == GDI_OBJECT_TYPE_BITMAP); /* 21 */
}