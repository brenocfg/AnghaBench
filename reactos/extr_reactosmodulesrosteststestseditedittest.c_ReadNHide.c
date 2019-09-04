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
 int /*<<< orphan*/  BM_GETCHECK ; 
 scalar_t__ BST_CHECKED ; 
 int /*<<< orphan*/  Back1But ; 
 int /*<<< orphan*/ * Buttons ; 
 int /*<<< orphan*/  EditStyle ; 
 int /*<<< orphan*/ * EditStyles ; 
 int /*<<< orphan*/ * MessageButtons ; 
 int NUMBERBUTTONS ; 
 int /*<<< orphan*/  NextBut ; 
 int /*<<< orphan*/  SW_HIDE ; 
 int /*<<< orphan*/  SW_SHOW ; 
 scalar_t__ SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShowWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

VOID
ReadNHide()
    {
        int i;
        EditStyle = 0;
        for (i=0 ; i< 19 ; i++)
        {
        if(BST_CHECKED == SendMessage(Buttons[i],BM_GETCHECK,0,0))
        EditStyle |= EditStyles[i];
        ShowWindow(Buttons[i],SW_HIDE);
        }

        for (; i< NUMBERBUTTONS ; i++)ShowWindow(Buttons[i],SW_HIDE);
        for (i=0 ; i< 26 ; i++) ShowWindow(MessageButtons[i],SW_SHOW);

        ShowWindow(Back1But,SW_SHOW);
        ShowWindow(NextBut,SW_SHOW);
    }