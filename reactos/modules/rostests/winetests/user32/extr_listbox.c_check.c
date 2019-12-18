#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  add_style; } ;
struct listbox_test {TYPE_1__ prop; } ;
struct listbox_stat {int dummy; } ;
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_4__ {scalar_t__ top; scalar_t__ left; } ;
typedef  TYPE_2__ RECT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LB_DELETESTRING ; 
 int LB_ERR ; 
 int /*<<< orphan*/  LB_GETCOUNT ; 
 int /*<<< orphan*/  LB_GETITEMRECT ; 
 int /*<<< orphan*/  LB_GETTEXT ; 
 int /*<<< orphan*/  LB_GETTEXTLEN ; 
 int /*<<< orphan*/  LB_SELITEMRANGE ; 
 int /*<<< orphan*/  MAKELPARAM (int,int) ; 
 int SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int TRUE ; 
 int /*<<< orphan*/  VK_DOWN ; 
 int /*<<< orphan*/  WAIT ; 
 int /*<<< orphan*/  WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  buttonpress (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  click ; 
 int /*<<< orphan*/  create_listbox (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init ; 
 int /*<<< orphan*/  keypress (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  listbox_ok (struct listbox_test const,int /*<<< orphan*/ ,struct listbox_stat) ; 
 int /*<<< orphan*/  listbox_query (int /*<<< orphan*/ ,struct listbox_stat*) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int /*<<< orphan*/  sel ; 
 int /*<<< orphan*/  step ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strings ; 
 int /*<<< orphan*/  trace (char*,int,int) ; 

__attribute__((used)) static void
check (const struct listbox_test test)
{
  struct listbox_stat answer;
  HWND hLB=create_listbox (test.prop.add_style, 0);
  RECT second_item;
  int i;
  int res;

  listbox_query (hLB, &answer);
  listbox_ok (test, init, answer);

  SendMessageA(hLB, LB_GETITEMRECT, 1, (LPARAM) &second_item);
  buttonpress(hLB, (WORD)second_item.left, (WORD)second_item.top);

  listbox_query (hLB, &answer);
  listbox_ok (test, click, answer);

  keypress (hLB, VK_DOWN, 0x50, TRUE);

  listbox_query (hLB, &answer);
  listbox_ok (test, step, answer);

  DestroyWindow (hLB);
  hLB=create_listbox (test.prop.add_style, 0);

  SendMessageA(hLB, LB_SELITEMRANGE, TRUE, MAKELPARAM(1, 2));
  listbox_query (hLB, &answer);
  listbox_ok (test, sel, answer);

  for (i=0;i<4;i++) {
	DWORD size = SendMessageA(hLB, LB_GETTEXTLEN, i, 0);
	CHAR *txt;
	WCHAR *txtw;
	int resA, resW;

	txt = HeapAlloc (GetProcessHeap(), HEAP_ZERO_MEMORY, size+1);
	resA=SendMessageA(hLB, LB_GETTEXT, i, (LPARAM)txt);
        ok(!strcmp (txt, strings[i]), "returned string for item %d does not match %s vs %s\n", i, txt, strings[i]);

	txtw = HeapAlloc (GetProcessHeap(), HEAP_ZERO_MEMORY, 2*size+2);
	resW=SendMessageW(hLB, LB_GETTEXT, i, (LPARAM)txtw);
	if (resA != resW) {
            trace("SendMessageW(LB_GETTEXT) not supported on this platform (resA=%d resW=%d), skipping...\n",
                resA, resW);
	} else {
	    WideCharToMultiByte( CP_ACP, 0, txtw, -1, txt, size, NULL, NULL );
            ok(!strcmp (txt, strings[i]), "returned string for item %d does not match %s vs %s\n", i, txt, strings[i]);
	}

	HeapFree (GetProcessHeap(), 0, txtw);
	HeapFree (GetProcessHeap(), 0, txt);
  }
  
  /* Confirm the count of items, and that an invalid delete does not remove anything */
  res = SendMessageA(hLB, LB_GETCOUNT, 0, 0);
  ok((res==4), "Expected 4 items, got %d\n", res);
  res = SendMessageA(hLB, LB_DELETESTRING, -1, 0);
  ok((res==LB_ERR), "Expected LB_ERR items, got %d\n", res);
  res = SendMessageA(hLB, LB_DELETESTRING, 4, 0);
  ok((res==LB_ERR), "Expected LB_ERR items, got %d\n", res);
  res = SendMessageA(hLB, LB_GETCOUNT, 0, 0);
  ok((res==4), "Expected 4 items, got %d\n", res);

  WAIT;
  DestroyWindow (hLB);
}