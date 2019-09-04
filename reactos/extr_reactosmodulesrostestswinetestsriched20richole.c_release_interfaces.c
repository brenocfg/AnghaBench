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
typedef  int /*<<< orphan*/  ITextSelection ;
typedef  int /*<<< orphan*/  ITextDocument ;
typedef  int /*<<< orphan*/  IRichEditOle ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRichEditOle_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITextDocument_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITextSelection_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void release_interfaces(HWND *w, IRichEditOle **reOle, ITextDocument **txtDoc,
                               ITextSelection **txtSel)
{
  if(txtSel)
    ITextSelection_Release(*txtSel);
  ITextDocument_Release(*txtDoc);
  IRichEditOle_Release(*reOle);
  DestroyWindow(*w);
}