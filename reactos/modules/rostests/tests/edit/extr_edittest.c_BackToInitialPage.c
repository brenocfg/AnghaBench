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
typedef  int /*<<< orphan*/  VOID ;

/* Variables and functions */
 int /*<<< orphan*/  Back1But ; 
 int /*<<< orphan*/ * Buttons ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * MessageButtons ; 
 int NUMBERBUTTONS ; 
 int /*<<< orphan*/  NextBut ; 
 int /*<<< orphan*/  SW_HIDE ; 
 int /*<<< orphan*/  SW_SHOW ; 
 int /*<<< orphan*/  ShowWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwndEdit ; 

VOID
BackToInitialPage()
    {
        int i;
        DestroyWindow(hwndEdit);
        for (i=0 ; i< NUMBERBUTTONS ; i++) {ShowWindow(Buttons[i],SW_SHOW);}
        for (i=0;i<26;i++)ShowWindow(MessageButtons[i],SW_HIDE);
        ShowWindow(Back1But,SW_HIDE);
        ShowWindow(NextBut,SW_HIDE);
    }