#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  item ;
struct TYPE_3__ {char* pszText; int iItem; int lParam; int /*<<< orphan*/  mask; } ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_1__ COMBOBOXEXITEMA ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CBEIF_LPARAM ; 
 int /*<<< orphan*/  CBEIF_TEXT ; 
 int /*<<< orphan*/  CBEM_GETITEMA ; 
 int /*<<< orphan*/  CBEM_SETITEMA ; 
 int CBS_DROPDOWN ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EDITBOX_SEQ_INDEX ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NUM_MSG_SEQUENCES ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int WS_BORDER ; 
 int WS_CHILD ; 
 int WS_VISIBLE ; 
 int /*<<< orphan*/  createComboEx (int) ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_sequences (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  ok_sequence (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sequences ; 
 int /*<<< orphan*/  subclass_editbox (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_setitem_edit_seq ; 

__attribute__((used)) static void test_comboex_get_set_item(void)
{
    char textA[] = "test";
    HWND hComboEx;
    COMBOBOXEXITEMA item;
    BOOL ret;

    hComboEx = createComboEx(WS_BORDER | WS_VISIBLE | WS_CHILD | CBS_DROPDOWN);

    subclass_editbox(hComboEx);

    flush_sequences(sequences, NUM_MSG_SEQUENCES);

    memset(&item, 0, sizeof(item));
    item.mask = CBEIF_TEXT;
    item.pszText = textA;
    item.iItem = -1;
    ret = SendMessageA(hComboEx, CBEM_SETITEMA, 0, (LPARAM)&item);
    expect(TRUE, ret);

    ok_sequence(sequences, EDITBOX_SEQ_INDEX, test_setitem_edit_seq, "set item data for edit", FALSE);

    /* get/set lParam */
    item.mask = CBEIF_LPARAM;
    item.iItem = -1;
    item.lParam = 0xdeadbeef;
    ret = SendMessageA(hComboEx, CBEM_GETITEMA, 0, (LPARAM)&item);
    expect(TRUE, ret);
    ok(item.lParam == 0, "Expected zero, got %lx\n", item.lParam);

    item.lParam = 0x1abe11ed;
    ret = SendMessageA(hComboEx, CBEM_SETITEMA, 0, (LPARAM)&item);
    expect(TRUE, ret);

    item.lParam = 0;
    ret = SendMessageA(hComboEx, CBEM_GETITEMA, 0, (LPARAM)&item);
    expect(TRUE, ret);
    ok(item.lParam == 0x1abe11ed, "Expected 0x1abe11ed, got %lx\n", item.lParam);

    DestroyWindow(hComboEx);
}