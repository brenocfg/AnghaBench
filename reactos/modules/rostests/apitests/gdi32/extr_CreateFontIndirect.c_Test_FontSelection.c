#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_4__ {int /*<<< orphan*/  CharSetBefore; } ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Test_FontSelectionEntry (int /*<<< orphan*/ ,size_t,TYPE_1__*) ; 
 size_t _countof (TYPE_1__*) ; 
 TYPE_1__* g_Entries ; 
 int /*<<< orphan*/  is_charset_font_installed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
Test_FontSelection(void)
{
    UINT nIndex;
    HDC hDC;

    hDC = CreateCompatibleDC(NULL);
    for (nIndex = 0; nIndex < _countof(g_Entries); ++nIndex)
    {
        if (!is_charset_font_installed(hDC, g_Entries[nIndex].CharSetBefore))
            skip("charset not available: 0x%x\n", g_Entries[nIndex].CharSetBefore);
        else
            Test_FontSelectionEntry(hDC, nIndex, g_Entries + nIndex);
    }
    DeleteDC(hDC);
}