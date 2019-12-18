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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetStockObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYSTEM_FIXED_FONT ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TextOut (int /*<<< orphan*/ ,int,int,char*,int) ; 
 int /*<<< orphan*/  ValidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_hwnd ; 
 int /*<<< orphan*/  rect ; 

VOID
PrintTextXY(char* Text,int x,int y,int len)
{
      HDC hdc;
      hdc = GetDC (g_hwnd);
      SelectObject (hdc, GetStockObject (SYSTEM_FIXED_FONT));

      TextOut (hdc, x,y,Text,len);
      ReleaseDC (g_hwnd, hdc);
      ValidateRect (g_hwnd, &rect);
}