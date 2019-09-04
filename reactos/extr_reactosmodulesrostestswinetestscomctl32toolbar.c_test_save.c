#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  expect ;
typedef  int /*<<< orphan*/  data ;
typedef  char WCHAR ;
struct TYPE_5__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_7__ {int member_1; int member_5; int member_6; scalar_t__ iBitmap; int idCommand; scalar_t__ fsState; scalar_t__ fsStyle; scalar_t__ dwData; scalar_t__ iString; TYPE_1__ member_4; int /*<<< orphan*/  const member_3; int /*<<< orphan*/  const member_2; int /*<<< orphan*/  member_0; } ;
struct TYPE_6__ {char const* pszSubKey; char const* pszValueName; int /*<<< orphan*/  hkr; } ;
typedef  TYPE_2__ TBSAVEPARAMSW ;
typedef  TYPE_3__ TBBUTTON ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int LONG ;
typedef  scalar_t__ INT_PTR ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_3__ const*) ; 
#define  BTNS_BUTTON 130 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ *) ; 
 int FALSE ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 scalar_t__ IS_INTRESOURCE (scalar_t__) ; 
 int /*<<< orphan*/  NUM_MSG_SEQUENCES ; 
 int /*<<< orphan*/  PARENT_SEQ_INDEX ; 
 int REG_BINARY ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegDeleteValueW (int /*<<< orphan*/ ,char const*) ; 
 int RegOpenKeyW (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int RegQueryValueExW (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int*) ; 
 int SendMessageW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
#define  TBSTATE_ENABLED 129 
#define  TBSTATE_HIDDEN 128 
 int /*<<< orphan*/  TB_ADDBUTTONSW ; 
 int /*<<< orphan*/  TB_BUTTONCOUNT ; 
 int /*<<< orphan*/  TB_GETBUTTON ; 
 int /*<<< orphan*/  TB_SAVERESTOREW ; 
 int TRUE ; 
 scalar_t__ alloced_str ; 
 int /*<<< orphan*/  flush_sequences (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int const*,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  ok_sequence (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  rebuild_toolbar (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  rebuild_toolbar_with_buttons (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  restore_parent_seq ; 
 int /*<<< orphan*/  save_parent_seq ; 
 int /*<<< orphan*/  sequences ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static void test_save(void)
{
    HWND wnd = NULL;
    TBSAVEPARAMSW params;
    static const WCHAR subkey[] = {'S','o','f','t','w','a','r','e','\\','W','i','n','e','\\',
                                   'W','i','n','e','T','e','s','t',0};
    static const WCHAR value[] = {'t','o','o','l','b','a','r','t','e','s','t',0};
    LONG res;
    HKEY key;
    BYTE data[100];
    DWORD size = sizeof(data), type, i, count;
    TBBUTTON tb;
    static const TBBUTTON more_btns[2] =
        {
            {0, 11, TBSTATE_HIDDEN, BTNS_BUTTON, {0}, 0, -1},
            {0, 13, TBSTATE_ENABLED, BTNS_BUTTON, {0}, 0, -1}
        };
    static const DWORD expect[] = {0xcafe, 1, 0xcafe0000, 3, 0xcafe0001, 5, 0xcafe0002, 7, 0xcafe0003,
                                   9, 0xcafe0004, 11, 0xcafe0005, 13, 0xcafe0006, 0xffffffff, 0xcafe0007,
                                   0xfffffffe, 0xcafe0008, 0x80000000, 0xcafe0009, 0x7fffffff, 0xcafe000a,
                                   0x100, 0xcafe000b};
    static const TBBUTTON expect_btns[] =
    {
        {0, 1, TBSTATE_ENABLED, BTNS_BUTTON, {0}, 0, 0},
        {0, 3, TBSTATE_ENABLED, BTNS_BUTTON, {0}, 1, 2},
        {0, 5, TBSTATE_ENABLED, BTNS_BUTTON, {0}, 2, 0},
        {0, 7, 0, BTNS_BUTTON, {0}, 0, (INT_PTR)"foo"},
        {0, 9, 0, BTNS_BUTTON, {0}, 0, 0},
        {0, 11, 0, BTNS_BUTTON, {0}, 0, 3},
        {0, 13, TBSTATE_ENABLED, BTNS_BUTTON, {0}, 6, 0},
        {0, 0, TBSTATE_ENABLED, BTNS_BUTTON, {0}, 7, 0},
        {0, 0, TBSTATE_ENABLED, BTNS_BUTTON, {0}, 8, 0},
        {0, 0, TBSTATE_ENABLED, BTNS_BUTTON, {0}, 9, 0},
        {0, 0x7fffffff, TBSTATE_ENABLED, BTNS_BUTTON, {0}, 0xa, 0},
    };

    params.hkr = HKEY_CURRENT_USER;
    params.pszSubKey = subkey;
    params.pszValueName = value;

    rebuild_toolbar_with_buttons( &wnd );
    SendMessageW(wnd, TB_ADDBUTTONSW, ARRAY_SIZE(more_btns), (LPARAM)more_btns);

    flush_sequences(sequences, NUM_MSG_SEQUENCES);
    res = SendMessageW( wnd, TB_SAVERESTOREW, TRUE, (LPARAM)&params );
    ok( res, "saving failed\n" );
    ok_sequence(sequences, PARENT_SEQ_INDEX, save_parent_seq, "save", FALSE);
    DestroyWindow( wnd );

    res = RegOpenKeyW( HKEY_CURRENT_USER, subkey, &key );
    ok( !res, "got %08x\n", res );
    res = RegQueryValueExW( key, value, NULL, &type, data, &size );
    ok( !res, "got %08x\n", res );
    ok( type == REG_BINARY, "got %08x\n", type );
    ok( size == sizeof(expect), "got %08x\n", size );
    ok( !memcmp( data, expect, size ), "mismatch\n" );

    RegCloseKey( key );

    wnd = NULL;
    rebuild_toolbar( &wnd );

    flush_sequences(sequences, NUM_MSG_SEQUENCES);
    res = SendMessageW( wnd, TB_SAVERESTOREW, FALSE, (LPARAM)&params );
    ok( res, "restoring failed\n" );
    ok_sequence(sequences, PARENT_SEQ_INDEX, restore_parent_seq, "restore", FALSE);
    count = SendMessageW( wnd, TB_BUTTONCOUNT, 0, 0 );
    ok( count == ARRAY_SIZE(expect_btns), "got %d\n", count );

    for (i = 0; i < count; i++)
    {
        res = SendMessageW( wnd, TB_GETBUTTON, i, (LPARAM)&tb );
        ok( res, "got %d\n", res );

        ok( tb.iBitmap == expect_btns[i].iBitmap, "%d: got %d\n", i, tb.iBitmap );
        ok( tb.idCommand == expect_btns[i].idCommand, "%d: got %d\n", i, tb.idCommand );
        ok( tb.fsState == expect_btns[i].fsState, "%d: got %02x\n", i, tb.fsState );
        ok( tb.fsStyle == expect_btns[i].fsStyle, "%d: got %02x\n", i, tb.fsStyle );
        ok( tb.dwData == expect_btns[i].dwData, "%d: got %lx\n", i, tb.dwData );
        if (IS_INTRESOURCE(expect_btns[i].iString))
            ok( tb.iString == expect_btns[i].iString, "%d: got %lx\n", i, tb.iString );
        else
            ok( !strcmp( (char *)tb.iString, (char *)expect_btns[i].iString ),
                "%d: got %s\n", i, (char *)tb.iString );

        /* In fact the ptr value set in TBN_GETBUTTONINFOA is simply copied */
        if (tb.idCommand == 7)
            ok( tb.iString == (INT_PTR)alloced_str, "string not set\n");
    }

    DestroyWindow( wnd );
    RegOpenKeyW( HKEY_CURRENT_USER, subkey, &key );
    RegDeleteValueW( key, value );
    RegCloseKey( key );
}