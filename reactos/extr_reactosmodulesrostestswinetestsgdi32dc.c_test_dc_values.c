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
typedef  int /*<<< orphan*/ * HDC ;
typedef  int COLORREF ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateDCA (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ *) ; 
 int GetBkColor (int /*<<< orphan*/ *) ; 
 int GetTextCharacterExtra (int /*<<< orphan*/ *) ; 
 int GetTextColor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MM_LOMETRIC ; 
 int /*<<< orphan*/  MM_TEXT ; 
 int SetBkColor (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SetMapMode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetTextCharacterExtra (int /*<<< orphan*/ *,int) ; 
 int SetTextColor (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_dc_values(void)
{
    HDC hdc = CreateDCA("DISPLAY", NULL, NULL, NULL);
    COLORREF color;
    int extra;

    ok( hdc != NULL, "CreateDC failed\n" );
    color = SetBkColor( hdc, 0x12345678 );
    ok( color == 0xffffff, "initial color %08x\n", color );
    color = GetBkColor( hdc );
    ok( color == 0x12345678, "wrong color %08x\n", color );
    color = SetBkColor( hdc, 0xffffffff );
    ok( color == 0x12345678, "wrong color %08x\n", color );
    color = GetBkColor( hdc );
    ok( color == 0xffffffff, "wrong color %08x\n", color );
    color = SetBkColor( hdc, 0 );
    ok( color == 0xffffffff, "wrong color %08x\n", color );
    color = GetBkColor( hdc );
    ok( color == 0, "wrong color %08x\n", color );

    color = SetTextColor( hdc, 0xffeeddcc );
    ok( color == 0, "initial color %08x\n", color );
    color = GetTextColor( hdc );
    ok( color == 0xffeeddcc, "wrong color %08x\n", color );
    color = SetTextColor( hdc, 0xffffffff );
    ok( color == 0xffeeddcc, "wrong color %08x\n", color );
    color = GetTextColor( hdc );
    ok( color == 0xffffffff, "wrong color %08x\n", color );
    color = SetTextColor( hdc, 0 );
    ok( color == 0xffffffff, "wrong color %08x\n", color );
    color = GetTextColor( hdc );
    ok( color == 0, "wrong color %08x\n", color );

    extra = GetTextCharacterExtra( hdc );
    ok( extra == 0, "initial extra %d\n", extra );
    SetTextCharacterExtra( hdc, 123 );
    extra = GetTextCharacterExtra( hdc );
    ok( extra == 123, "initial extra %d\n", extra );
    SetMapMode( hdc, MM_LOMETRIC );
    extra = GetTextCharacterExtra( hdc );
    ok( extra == 123, "initial extra %d\n", extra );
    SetMapMode( hdc, MM_TEXT );
    extra = GetTextCharacterExtra( hdc );
    ok( extra == 123, "initial extra %d\n", extra );

    DeleteDC( hdc );
}