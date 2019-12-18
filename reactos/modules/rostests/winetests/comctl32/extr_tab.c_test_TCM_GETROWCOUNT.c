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
typedef  int INT ;
typedef  int /*<<< orphan*/ * HWND ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NUM_MSG_SEQUENCES ; 
 int /*<<< orphan*/  PARENT_SEQ_INDEX ; 
 int SendMessageA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAB_SEQ_INDEX ; 
 int TCIF_IMAGE ; 
 int TCIF_TEXT ; 
 int /*<<< orphan*/  TCM_GETROWCOUNT ; 
 int /*<<< orphan*/  TCS_FIXEDWIDTH ; 
 int /*<<< orphan*/ * createFilledTabControl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int const) ; 
 int /*<<< orphan*/  empty_sequence ; 
 int /*<<< orphan*/  flush_sequences (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_row_count_seq ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  ok_sequence (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parent_wnd ; 
 int /*<<< orphan*/  sequences ; 

__attribute__((used)) static void test_TCM_GETROWCOUNT(void)
{
    const INT nTabs = 5;
    HWND hTab;
    INT count;

    flush_sequences(sequences, NUM_MSG_SEQUENCES);

    hTab = createFilledTabControl(parent_wnd, TCS_FIXEDWIDTH, TCIF_TEXT|TCIF_IMAGE, nTabs);
    ok(hTab != NULL, "Failed to create tab control\n");

    flush_sequences(sequences, NUM_MSG_SEQUENCES);

    count = SendMessageA(hTab, TCM_GETROWCOUNT, 0, 0);
    ok(count == 1, "Unexpected row count %d.\n", count);

    ok_sequence(sequences, TAB_SEQ_INDEX, get_row_count_seq, "Get rowCount test sequence", FALSE);
    ok_sequence(sequences, PARENT_SEQ_INDEX, empty_sequence, "Get rowCount test parent sequence", FALSE);

    DestroyWindow(hTab);
}