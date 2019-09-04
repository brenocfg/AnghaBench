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
typedef  int /*<<< orphan*/  RECT ;
typedef  scalar_t__ LRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int BUFFERLEN ; 
 int /*<<< orphan*/  GetWindowRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PrintTextXY (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ResultX ; 
 int /*<<< orphan*/  ResultY ; 
 scalar_t__ SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* TextBuffer ; 
 int /*<<< orphan*/  g_hwnd ; 

__attribute__((used)) static
VOID
HandlePrintReturnStr(HWND handle,DWORD Msg,WPARAM wParam,LPARAM lParam)
    {
    LRESULT ret;
    RECT rect;

    TextBuffer[8] = (char)(BUFFERLEN - 8); /* Setting the max size to put chars in first byte */
    ret = SendMessage(handle,Msg,wParam,lParam);
    GetWindowRect(g_hwnd,&rect);
    PrintTextXY(TextBuffer,ResultX,ResultY,8+(int)ret,rect);
    }