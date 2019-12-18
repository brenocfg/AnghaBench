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
typedef  int /*<<< orphan*/  XtPointer ;
typedef  int /*<<< orphan*/  XtEventHandler ;
typedef  int /*<<< orphan*/  Widget ;

/* Variables and functions */
 int /*<<< orphan*/  AnyKey ; 
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  KeyPressMask ; 
 int /*<<< orphan*/  Mod1Mask ; 
 int /*<<< orphan*/  XtRemoveEventHandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XtUngrabKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mnemonic_event ; 

__attribute__((used)) static void
suppress_dialog_mnemonics(Widget dialog)
{
    if (!dialog)
	return;

    XtUngrabKey(dialog, AnyKey, Mod1Mask);
    XtRemoveEventHandler(dialog, KeyPressMask, False,
			   (XtEventHandler) mnemonic_event, (XtPointer) NULL);
}