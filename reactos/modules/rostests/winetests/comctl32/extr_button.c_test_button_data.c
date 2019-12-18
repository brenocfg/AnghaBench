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
typedef  int const LONG ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  int DWORD ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int const*) ; 
#define  BS_3STATE 142 
#define  BS_AUTO3STATE 141 
#define  BS_AUTOCHECKBOX 140 
#define  BS_AUTORADIOBUTTON 139 
#define  BS_CHECKBOX 138 
#define  BS_COMMANDLINK 137 
#define  BS_DEFCOMMANDLINK 136 
#define  BS_DEFPUSHBUTTON 135 
#define  BS_DEFSPLITBUTTON 134 
#define  BS_GROUPBOX 133 
 int const BS_NOTIFY ; 
#define  BS_OWNERDRAW 132 
#define  BS_PUSHBUTTON 131 
#define  BS_RADIOBUTTON 130 
#define  BS_SPLITBUTTON 129 
#define  BS_USERBUTTON 128 
 int /*<<< orphan*/ * CreateWindowExA (int /*<<< orphan*/ ,char*,char*,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ *) ; 
 scalar_t__ GetWindowLongPtrA (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int const WS_CHILD ; 
 int WS_OVERLAPPEDWINDOW ; 
 int WS_VISIBLE ; 
 int /*<<< orphan*/ * create_button (int const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  test_bcm_splitinfo (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_button_data(void)
{
    static const DWORD styles[] =
    {
        BS_PUSHBUTTON,
        BS_DEFPUSHBUTTON,
        BS_CHECKBOX,
        BS_AUTOCHECKBOX,
        BS_RADIOBUTTON,
        BS_3STATE,
        BS_AUTO3STATE,
        BS_GROUPBOX,
        BS_USERBUTTON,
        BS_AUTORADIOBUTTON,
        BS_OWNERDRAW,
        BS_SPLITBUTTON,
        BS_DEFSPLITBUTTON,
        BS_COMMANDLINK,
        BS_DEFCOMMANDLINK,
    };

    struct button_desc
    {
        HWND self;
        HWND parent;
        LONG style;
    };
    unsigned int i;
    HWND parent;

    parent = CreateWindowExA(0, "TestParentClass", "Test parent", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                             100, 100, 200, 200, 0, 0, 0, NULL);
    ok(parent != 0, "Failed to create parent window\n");

    for (i = 0; i < ARRAY_SIZE(styles); i++)
    {
        struct button_desc *desc;
        HWND hwnd;

        hwnd = create_button(styles[i], parent);
        ok(hwnd != NULL, "Failed to create a button.\n");

        desc = (void *)GetWindowLongPtrA(hwnd, 0);
        ok(desc != NULL, "Expected window data.\n");

        if (desc)
        {
            ok(desc->self == hwnd, "Unexpected 'self' field.\n");
            ok(desc->parent == parent, "Unexpected 'parent' field.\n");
            ok(desc->style == (WS_CHILD | BS_NOTIFY | styles[i]), "Unexpected 'style' field.\n");
        }

        /* Data set and retrieved by these messages is valid for all buttons */
        test_bcm_splitinfo(hwnd);

        DestroyWindow(hwnd);
    }

    DestroyWindow(parent);
}