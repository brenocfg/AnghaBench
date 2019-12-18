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
typedef  scalar_t__ LRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HMENU ;

/* Variables and functions */
 int /*<<< orphan*/  CreateWindowExA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ ID_LISTBOX ; 
 int LBS_HASSTRINGS ; 
 int LBS_NOTIFY ; 
 int LBS_OWNERDRAWVARIABLE ; 
 int LBS_SORT ; 
 int /*<<< orphan*/  LB_ADDSTRING ; 
 int /*<<< orphan*/  LB_GETITEMDATA ; 
 int /*<<< orphan*/  NUM_MSG_SEQUENCES ; 
 int /*<<< orphan*/  PARENT_SEQ_INDEX ; 
 scalar_t__ SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WC_LISTBOXA ; 
 int WS_CHILD ; 
 int /*<<< orphan*/  WS_EX_NOPARENTNOTIFY ; 
 int WS_VISIBLE ; 
 int /*<<< orphan*/  create_listbox (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_parent () ; 
 int /*<<< orphan*/  empty_seq ; 
 int /*<<< orphan*/  flush_sequences (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lb_addstring_ownerdraw_parent_seq ; 
 int /*<<< orphan*/  lb_addstring_sort_parent_seq ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  ok_sequence (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sequences ; 
 scalar_t__* strings ; 

__attribute__((used)) static void test_WM_MEASUREITEM(void)
{
    HWND parent, listbox;
    LRESULT data, ret;

    parent = create_parent();
    listbox = create_listbox(WS_CHILD | LBS_OWNERDRAWVARIABLE, parent);

    data = SendMessageA(listbox, LB_GETITEMDATA, 0, 0);
    ok(data == (LRESULT)strings[0], "data = %08lx, expected %p\n", data, strings[0]);
    DestroyWindow(parent);

    parent = create_parent();
    listbox = create_listbox(WS_CHILD | LBS_OWNERDRAWVARIABLE | LBS_HASSTRINGS, parent);

    data = SendMessageA(listbox, LB_GETITEMDATA, 0, 0);
    ok(!data, "data = %08lx\n", data);

    /* LBS_HASSTRINGS */
    parent = create_parent();
    listbox = CreateWindowExA(WS_EX_NOPARENTNOTIFY, WC_LISTBOXA, NULL,
                              WS_CHILD | LBS_NOTIFY | LBS_OWNERDRAWVARIABLE | LBS_HASSTRINGS | WS_VISIBLE,
                              10, 10, 80, 80, parent, (HMENU)ID_LISTBOX, 0, NULL);

    flush_sequences(sequences, NUM_MSG_SEQUENCES);

    ret = SendMessageA(listbox, LB_ADDSTRING, 0, (LPARAM)"item 0");
    ok(ret == 0, "expected 0, got %ld\n", ret);
    ret = SendMessageA(listbox, LB_ADDSTRING, 0, (LPARAM)"item 1");
    ok(ret == 1, "expected 1, got %ld\n", ret);
    ret = SendMessageA(listbox, LB_ADDSTRING, 0, (LPARAM)"item 2");
    ok(ret == 2, "expected 2, got %ld\n", ret);

    ok_sequence(sequences, PARENT_SEQ_INDEX, lb_addstring_ownerdraw_parent_seq,
        "LB_ADDSTRING (LBS_HASSTRINGS, ownerdraw)", FALSE);
    DestroyWindow(listbox);

    /* LBS_SORT, no LBS_HASSTRINGS */
    listbox = CreateWindowExA(WS_EX_NOPARENTNOTIFY, WC_LISTBOXA, NULL,
                              WS_CHILD | LBS_NOTIFY | LBS_OWNERDRAWVARIABLE | LBS_SORT | WS_VISIBLE,
                              10, 10, 80, 80, parent, (HMENU)ID_LISTBOX, 0, NULL);

    flush_sequences(sequences, NUM_MSG_SEQUENCES);

    ret = SendMessageA(listbox, LB_ADDSTRING, 0, (LPARAM)"item 0");
    ok(ret == 0, "expected 0, got %ld\n", ret);
    ret = SendMessageA(listbox, LB_ADDSTRING, 0, (LPARAM)"item 1");
    ok(ret == 1, "expected 1, got %ld\n", ret);
    ret = SendMessageA(listbox, LB_ADDSTRING, 0, (LPARAM)"item 2");
    ok(ret == 2, "expected 2, got %ld\n", ret);

    ok_sequence(sequences, PARENT_SEQ_INDEX, lb_addstring_sort_parent_seq, "LB_ADDSTRING (LBS_SORT)", FALSE);
    DestroyWindow(listbox);

    /* LBS_HASSTRINGS */
    listbox = CreateWindowExA(WS_EX_NOPARENTNOTIFY, WC_LISTBOXA, NULL,
                              WS_CHILD | LBS_NOTIFY | LBS_HASSTRINGS | WS_VISIBLE,
                              10, 10, 80, 80, parent, (HMENU)ID_LISTBOX, 0, NULL);

    flush_sequences(sequences, NUM_MSG_SEQUENCES);

    ret = SendMessageA(listbox, LB_ADDSTRING, 0, (LPARAM)"item 2");
    ok(ret == 0, "expected 0, got %ld\n", ret);
    ret = SendMessageA(listbox, LB_ADDSTRING, 0, (LPARAM)"item 0");
    ok(ret == 1, "expected 1, got %ld\n", ret);
    ret = SendMessageA(listbox, LB_ADDSTRING, 0, (LPARAM)"item 1");
    ok(ret == 2, "expected 2, got %ld\n", ret);

    ok_sequence(sequences, PARENT_SEQ_INDEX, empty_seq, "LB_ADDSTRING (LBS_HASSTRINGS)", FALSE);
    DestroyWindow(listbox);

    /* LBS_HASSTRINGS, LBS_SORT */
    listbox = CreateWindowExA(WS_EX_NOPARENTNOTIFY, WC_LISTBOXA, NULL,
                              WS_CHILD | LBS_NOTIFY | LBS_HASSTRINGS | LBS_SORT | WS_VISIBLE,
                              10, 10, 80, 80, parent, (HMENU)ID_LISTBOX, 0, NULL);

    flush_sequences(sequences, NUM_MSG_SEQUENCES);

    ret = SendMessageA(listbox, LB_ADDSTRING, 0, (LPARAM)"item 2");
    ok(ret == 0, "expected 0, got %ld\n", ret);
    ret = SendMessageA(listbox, LB_ADDSTRING, 0, (LPARAM)"item 0");
    ok(ret == 0, "expected 0, got %ld\n", ret);
    ret = SendMessageA(listbox, LB_ADDSTRING, 0, (LPARAM)"item 1");
    ok(ret == 1, "expected 1, got %ld\n", ret);

    ok_sequence(sequences, PARENT_SEQ_INDEX, empty_seq, "LB_ADDSTRING (LBS_HASSTRINGS, LBS_SORT)", FALSE);
    DestroyWindow(listbox);

    DestroyWindow(parent);
}