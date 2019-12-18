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
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetStockObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ResultX ; 
 int /*<<< orphan*/  ResultY ; 
 int /*<<< orphan*/  SYSTEM_FIXED_FONT ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* TextBuffer ; 
 int /*<<< orphan*/  TextOut (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ValidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_hwnd ; 
 int /*<<< orphan*/  rect ; 

__attribute__((used)) static
VOID
HandlePrintPasswdChar(HWND handle,DWORD Msg,WPARAM wParam,LPARAM lParam)
    {
      HDC hdc;
      int ret = SendMessage(handle,Msg,wParam,lParam);

      int s;

      if (ret)
          {
            s = 1;
            TextBuffer[8] = (char)(ret);
          }
      else
          {
            TextBuffer[8]  = 'N';
            TextBuffer[9]  = 'U';
            TextBuffer[10] = 'L';
            TextBuffer[11] = 'L';
            s = 4;
          }

      hdc = GetDC (g_hwnd);
      SelectObject (hdc, GetStockObject (SYSTEM_FIXED_FONT));

      TextOut (hdc,ResultX ,ResultY,TextBuffer,8+s);
      ReleaseDC (g_hwnd, hdc);
      ValidateRect (g_hwnd, &rect);
    }