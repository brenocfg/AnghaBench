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
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  PrintTextXY (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ResultX ; 
 int /*<<< orphan*/  ResultY ; 
 int SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * TextBuffer ; 
 int /*<<< orphan*/  htoa (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
VOID
HandlePrintReturnHex(HWND handle,DWORD Msg,WPARAM wParam,LPARAM lParam)
    {
      int ret;
      ret = SendMessage(handle,Msg,wParam,lParam);
      htoa(ret,&TextBuffer[8]);
      PrintTextXY(TextBuffer,ResultX,ResultY,16);
    }