#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_2__ {int /*<<< orphan*/  right; int /*<<< orphan*/  left; int /*<<< orphan*/  bottom; int /*<<< orphan*/  top; } ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int BUFFERLEN ; 
 int /*<<< orphan*/  PrintTextXY (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ResultX ; 
 int /*<<< orphan*/  ResultY ; 
 int /*<<< orphan*/  SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* TextBuffer ; 
 int /*<<< orphan*/  htoa (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__ rect ; 

__attribute__((used)) static
VOID
HandlePrintRect(HWND handle,DWORD Msg,WPARAM wParam,LPARAM lParam)
    {
      TextBuffer[8] = (char)(BUFFERLEN - 8); /* Setting the max size to put chars in first byte */
      SendMessage(handle,Msg,wParam,lParam);

      htoa(rect.top,&TextBuffer[8]);
      TextBuffer[8+8] = ' ';
      htoa(rect.bottom,&TextBuffer[8+8+1]);
      TextBuffer[8+8+8+1] = ' ';
      htoa(rect.left,&TextBuffer[8+8+8+1+1]);
      TextBuffer[8+8+8+8+1+1] = ' ';
      htoa(rect.right,&TextBuffer[8+8+8+8+1+1+1]);

      PrintTextXY(TextBuffer,ResultX,ResultY,8+4*9-1);
    }