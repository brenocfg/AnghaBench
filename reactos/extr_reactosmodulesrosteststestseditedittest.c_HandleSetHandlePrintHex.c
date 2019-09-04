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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  VOID ;
typedef  scalar_t__ LPVOID ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HLOCAL ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  EM_GETHANDLE ; 
 int /*<<< orphan*/  EM_SETHANDLE ; 
 int LMEM_MOVEABLE ; 
 int LMEM_ZEROINIT ; 
 scalar_t__ LocalAlloc (int,int) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ ) ; 
 scalar_t__ LocalHandle (scalar_t__) ; 
 scalar_t__ LocalLock (scalar_t__) ; 
 int /*<<< orphan*/  LocalUnlock (scalar_t__) ; 
 int /*<<< orphan*/  NewText ; 
 int /*<<< orphan*/  NewTextW ; 
 int /*<<< orphan*/  PrintTextXY (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ResultX ; 
 int /*<<< orphan*/  ResultY ; 
 int SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/ * TextBuffer ; 
 scalar_t__ UnicodeUsed ; 
 int /*<<< orphan*/  htoa (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy_ (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpyw_ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
VOID
HandleSetHandlePrintHex(HWND handle,DWORD Msg,WPARAM wParam,LPARAM lParam)
    {
      LPVOID pMem;
      HANDLE hNewBuffer;
      int ret;

      LocalFree((HLOCAL)SendMessage(handle, EM_GETHANDLE, 0, 0L));
      if (UnicodeUsed)
          {
            hNewBuffer = LocalAlloc(LMEM_MOVEABLE | LMEM_ZEROINIT, 100);
            pMem = LocalLock(hNewBuffer);
            strcpyw_((wchar_t*)pMem,NewTextW);
          }
      else
          {
            hNewBuffer = LocalAlloc(LMEM_MOVEABLE | LMEM_ZEROINIT,50);
            pMem = LocalLock(hNewBuffer);
            strcpy_((char*)pMem,NewText);
          }

      LocalUnlock(pMem);
      hNewBuffer = LocalHandle(pMem);

	  /* Updates the buffer and displays new buffer */
      ret =  SendMessage(handle, EM_SETHANDLE, (WPARAM)hNewBuffer, 0L);

      htoa(ret,&TextBuffer[8]);
      PrintTextXY(TextBuffer,ResultX,ResultY,16);
    }