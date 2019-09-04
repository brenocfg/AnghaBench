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
struct TYPE_3__ {char* member_9; int /*<<< orphan*/ * member_8; int /*<<< orphan*/  member_7; int /*<<< orphan*/  member_6; int /*<<< orphan*/ * member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ WNDCLASSA ;
typedef  int /*<<< orphan*/  LPSTR ;
typedef  int /*<<< orphan*/  HBRUSH ;
typedef  int /*<<< orphan*/  ATOM ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_BTNFACE ; 
 int /*<<< orphan*/  DefWindowProcA ; 
 int /*<<< orphan*/  GetModuleHandleA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDC_ARROW ; 
 int /*<<< orphan*/  LoadCursorA (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegisterClassA (TYPE_1__*) ; 

__attribute__((used)) static ATOM register_dummy_class(void)
{
    WNDCLASSA wc =
    {
        0,
        DefWindowProcA,
        0,
        0,
        GetModuleHandleA(NULL),
        NULL,
        LoadCursorA(NULL, (LPSTR)IDC_ARROW),
        (HBRUSH)(COLOR_BTNFACE+1),
        NULL,
        "WineOleTestClass",
    };

    return RegisterClassA(&wc);
}