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
struct font_data {char* member_0; int member_1; int member_3; int member_4; int member_5; int member_6; int member_8; int /*<<< orphan*/  const member_9; int /*<<< orphan*/  member_7; int /*<<< orphan*/  const member_2; } ;
typedef  int /*<<< orphan*/ * HDC ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ *) ; 
#define  FALSE 130 
#define  FW_NORMAL 129 
#define  TRUE 128 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  test_height (int /*<<< orphan*/ *,struct font_data const*) ; 
 int /*<<< orphan*/  test_height_selection_vdmx (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_height_selection(void)
{
    static const struct font_data tahoma[] =
    {
        {"Tahoma", -12, FW_NORMAL, 14, 12, 2, 2, 0, 96, TRUE },
        {"Tahoma", -24, FW_NORMAL, 29, 24, 5, 5, 0, 96, TRUE },
        {"Tahoma", -48, FW_NORMAL, 58, 48, 10, 10, 0, 96, TRUE },
        {"Tahoma", -96, FW_NORMAL, 116, 96, 20, 20, 0, 96, TRUE },
        {"Tahoma", -192, FW_NORMAL, 232, 192, 40, 40, 0, 96, TRUE },
        {"Tahoma", 12, FW_NORMAL, 12, 10, 2, 2, 0, 96, TRUE },
        {"Tahoma", 24, FW_NORMAL, 24, 20, 4, 4, 0, 96, TRUE },
        {"Tahoma", 48, FW_NORMAL, 48, 40, 8, 8, 0, 96, TRUE },
        {"Tahoma", 96, FW_NORMAL, 96, 80, 16, 17, 0, 96, FALSE },
        {"Tahoma", 192, FW_NORMAL, 192, 159, 33, 33, 0, 96, TRUE },
        {"", 0, 0, 0, 0, 0, 0, 0, 0, 0 }
    };
    HDC hdc = CreateCompatibleDC(0);
    ok(hdc != NULL, "failed to create hdc\n");

    test_height( hdc, tahoma );
    test_height_selection_vdmx( hdc );

    DeleteDC(hdc);
}