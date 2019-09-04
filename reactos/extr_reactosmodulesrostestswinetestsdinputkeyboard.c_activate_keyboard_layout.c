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
typedef  int LANGID ;
typedef  int /*<<< orphan*/  HKL ;

/* Variables and functions */
 int /*<<< orphan*/  ActivateKeyboardLayout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetKeyboardLayout (int /*<<< orphan*/ ) ; 
 int LOWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LoadKeyboardLayoutA (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,char*) ; 
 int /*<<< orphan*/  skip (char*,int,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  trace (char*,char*) ; 
 int /*<<< orphan*/  win_skip (char*,char*) ; 

__attribute__((used)) static HKL activate_keyboard_layout(LANGID langid, HKL *hkl_orig)
{
    HKL hkl, hkl_current;
    char hkl_name[64];

    sprintf(hkl_name, "%08x", langid);
    trace("Loading keyboard layout %s\n", hkl_name);
    hkl = LoadKeyboardLayoutA(hkl_name, 0);
    if (!hkl)
    {
        win_skip("Unable to load keyboard layout %s\n", hkl_name);
        return 0;
    }
    *hkl_orig = ActivateKeyboardLayout(hkl, 0);
    ok(*hkl_orig != 0, "Unable to activate keyboard layout %s\n", hkl_name);
    if (!*hkl_orig) return 0;

    hkl_current = GetKeyboardLayout(0);
    if (LOWORD(hkl_current) != langid)
    {
        /* FIXME: Wine can't activate different keyboard layouts.
         * for testing purposes use this workaround:
         * setxkbmap us && LANG=en_US.UTF-8 make test
         * setxkbmap fr && LANG=fr_FR.UTF-8 make test
         * setxkbmap de && LANG=de_DE.UTF-8 make test
         */
        skip("current %08x != langid %08x\n", LOWORD(hkl_current), langid);
        return 0;
    }

    return hkl;
}