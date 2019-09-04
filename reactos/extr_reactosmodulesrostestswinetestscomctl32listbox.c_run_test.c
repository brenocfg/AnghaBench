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
struct message {int member_1; int /*<<< orphan*/  const member_0; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; } ;
struct listbox_test {int dummy; } ;
struct listbox_stat {int dummy; } ;
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_2__ {scalar_t__ top; scalar_t__ left; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int LBS_NODATA ; 
#define  LB_DELETESTRING 133 
 int LB_ERR ; 
 int /*<<< orphan*/  const LB_GETCOUNT ; 
 int /*<<< orphan*/  const LB_GETITEMRECT ; 
 int /*<<< orphan*/  const LB_GETTEXT ; 
 int /*<<< orphan*/  const LB_GETTEXTLEN ; 
#define  LB_RESETCONTENT 132 
 int /*<<< orphan*/  const LB_SELITEMRANGE ; 
 int /*<<< orphan*/  LB_SEQ_INDEX ; 
 int /*<<< orphan*/  MAKELPARAM (int,int) ; 
 int SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/  const,int,int /*<<< orphan*/ ) ; 
 int SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/  const,int,int /*<<< orphan*/ ) ; 
 int TRUE ; 
 int /*<<< orphan*/  VK_DOWN ; 
 int /*<<< orphan*/  WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  buttonpress (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  click ; 
 int /*<<< orphan*/  create_listbox (int,int /*<<< orphan*/ ) ; 
#define  defwinproc 131 
 int /*<<< orphan*/  flush_sequence (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * heap_alloc_zero (int) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init ; 
 int /*<<< orphan*/  keypress (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  listbox_ok (struct listbox_test const,int /*<<< orphan*/ ,struct listbox_stat) ; 
 int /*<<< orphan*/  listbox_query (int /*<<< orphan*/ ,struct listbox_stat*) ; 
#define  lparam 130 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  ok_sequence (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct message const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sel ; 
#define  sent 129 
 int /*<<< orphan*/  sequences ; 
 int /*<<< orphan*/  step ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strings ; 
#define  wparam 128 

__attribute__((used)) static void run_test(DWORD style, const struct listbox_test test)
{
    static const struct message delete_seq[] =
    {
        { LB_DELETESTRING, sent|wparam|lparam, 0, 0 },
        { LB_DELETESTRING, sent|wparam|lparam, 0, 0 },
        { LB_DELETESTRING, sent|wparam|lparam, 0, 0 },
        { LB_DELETESTRING, sent|wparam|lparam, 0, 0 },
        { LB_RESETCONTENT, sent|wparam|lparam|defwinproc, 0, 0 },
        { 0 }
    };
    struct listbox_stat answer;
    int i, res, count;
    RECT second_item;
    HWND hLB;

    hLB = create_listbox (style, 0);

    listbox_query (hLB, &answer);
    listbox_ok (test, init, answer);

    SendMessageA(hLB, LB_GETITEMRECT, 1, (LPARAM) &second_item);
    buttonpress(hLB, (WORD)second_item.left, (WORD)second_item.top);

    listbox_query(hLB, &answer);
    listbox_ok(test, click, answer);

    keypress(hLB, VK_DOWN, 0x50, TRUE);

    listbox_query(hLB, &answer);
    listbox_ok(test, step, answer);

    DestroyWindow(hLB);

    hLB = create_listbox(style, 0);

    SendMessageA(hLB, LB_SELITEMRANGE, TRUE, MAKELPARAM(1, 2));
    listbox_query(hLB, &answer);
    listbox_ok(test, sel, answer);

    for (i = 0; i < 4 && !(style & LBS_NODATA); i++)
    {
        DWORD size = SendMessageA(hLB, LB_GETTEXTLEN, i, 0);
        int resA, resW;
        WCHAR *txtw;
        CHAR *txt;

        txt = heap_alloc_zero(size + 1);
        resA = SendMessageA(hLB, LB_GETTEXT, i, (LPARAM)txt);
        ok(!strcmp(txt, strings[i]), "returned string for item %d does not match %s vs %s\n", i, txt, strings[i]);

        txtw = heap_alloc_zero((size + 1) * sizeof(*txtw));
        resW = SendMessageW(hLB, LB_GETTEXT, i, (LPARAM)txtw);
        ok(resA == resW, "Unexpected text length.\n");
        WideCharToMultiByte(CP_ACP, 0, txtw, -1, txt, size, NULL, NULL);
        ok(!strcmp (txt, strings[i]), "Unexpected string for item %d, %s vs %s.\n", i, txt, strings[i]);

        heap_free(txtw);
        heap_free(txt);
    }

    /* Confirm the count of items, and that an invalid delete does not remove anything */
    res = SendMessageA(hLB, LB_GETCOUNT, 0, 0);
    ok(res == 4, "Expected 4 items, got %d\n", res);
    res = SendMessageA(hLB, LB_DELETESTRING, -1, 0);
    ok(res == LB_ERR, "Expected LB_ERR items, got %d\n", res);
    res = SendMessageA(hLB, LB_DELETESTRING, 4, 0);
    ok(res == LB_ERR, "Expected LB_ERR items, got %d\n", res);
    count = SendMessageA(hLB, LB_GETCOUNT, 0, 0);
    ok(count == 4, "Unexpected item count %d.\n", count);

    /* Emptying listbox sends a LB_RESETCONTENT to itself. */
    flush_sequence(sequences, LB_SEQ_INDEX);
    for (i = count; i--;)
    {
        res = SendMessageA(hLB, LB_DELETESTRING, 0, 0);
        ok(res == i, "Unexpected return value %d.\n", res);
    }
    ok_sequence(sequences, LB_SEQ_INDEX, delete_seq, "Emptying listbox", FALSE);

    DestroyWindow(hLB);
}