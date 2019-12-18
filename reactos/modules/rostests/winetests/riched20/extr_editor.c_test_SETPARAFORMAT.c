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
struct TYPE_2__ {int cbSize; int dwMask; int wNumbering; int wNumberingStart; int wNumberingStyle; int wNumberingTab; int /*<<< orphan*/  wAlignment; } ;
typedef  TYPE_1__ PARAFORMAT2 ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EM_GETPARAFORMAT ; 
 int /*<<< orphan*/  EM_SETPARAFORMAT ; 
 int /*<<< orphan*/  PFA_LEFT ; 
 int PFM_ALIGNMENT ; 
 int PFM_ALL2 ; 
 int PFM_TABLEROWDELIMITER ; 
 int SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  new_richedit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 

__attribute__((used)) static void test_SETPARAFORMAT(void)
{
  HWND hwndRichEdit = new_richedit(NULL);
  PARAFORMAT2 fmt;
  HRESULT ret;
  LONG expectedMask = PFM_ALL2 & ~PFM_TABLEROWDELIMITER;
  fmt.cbSize = sizeof(PARAFORMAT2);
  fmt.dwMask = PFM_ALIGNMENT;
  fmt.wAlignment = PFA_LEFT;

  ret = SendMessageA(hwndRichEdit, EM_SETPARAFORMAT, 0, (LPARAM)&fmt);
  ok(ret != 0, "expected non-zero got %d\n", ret);

  fmt.cbSize = sizeof(PARAFORMAT2);
  fmt.dwMask = -1;
  ret = SendMessageA(hwndRichEdit, EM_GETPARAFORMAT, 0, (LPARAM)&fmt);
  /* Ignore the PFM_TABLEROWDELIMITER bit because it changes
   * between richedit different native builds of riched20.dll
   * used on different Windows versions. */
  ret &= ~PFM_TABLEROWDELIMITER;
  fmt.dwMask &= ~PFM_TABLEROWDELIMITER;

  ok(ret == expectedMask, "expected %x got %x\n", expectedMask, ret);
  ok(fmt.dwMask == expectedMask, "expected %x got %x\n", expectedMask, fmt.dwMask);

  /* Test some other paraformat field defaults */
  ok( fmt.wNumbering == 0, "got %d\n", fmt.wNumbering );
  ok( fmt.wNumberingStart == 0, "got %d\n", fmt.wNumberingStart );
  ok( fmt.wNumberingStyle == 0, "got %04x\n", fmt.wNumberingStyle );
  ok( fmt.wNumberingTab == 0, "got %d\n", fmt.wNumberingTab );

  DestroyWindow(hwndRichEdit);
}